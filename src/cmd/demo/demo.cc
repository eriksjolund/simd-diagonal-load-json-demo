#include <cstdlib>
#include <cstring>
#include <iostream>
#include <fstream>
#include <cassert>
#include <unistd.h>
#include <QCoreApplication>
#include <QDebug>
#include <QDir>
#include <QtPlugin>
#include <QString>
#include <stdexcept>
#include <simd-diagonal-load/array-helper/two_to_the_power_of.h>
#include <simd-diagonal-load-json-demo/defines-from-cmake-variables/config.h>
#include <simd-diagonal-load-json-demo/demo-plugin-interface/demo_plugin_interface.h>
#include <simd-diagonal-load-json-demo/demo-pluginloader/demo_pluginloader.h>
#include <simd-diagonal-load-json-demo/capnproto-helper-funcs/parsejsonfile.h>
#include <simd-diagonal-load-json-demo/demo-run-options/demo-run-options.capnp.h>

// TODO add static_assert check types are the same   std::result_of<
// decltype(&DemoRunOptions::Reader::getNumVerticalMixing)(DemoRunOptions::Reader)>::type
// num_vertical_mixing_t std::result_of<
// decltype(&InputSpec::Reader::getNumMatrices)(InputSpec::Reader)>::type
// num_vertical_subdivisions, std::result_of<
// decltype(&InputSpec::Reader::getMatrixWidth)(InputSpec::Reader)>::type

namespace {
const char* command_line_usage_string() {
  return "Usage: demo --help\n"
         "       demo --options-file JSONFILE\n\n"
         "OPTIONS\n"
         "    -h, --help    show help\n"
         "    -c, --conf FILE   file path to run options in JSON format\n";
}

void run_demo(const DemoRunOptions::Reader& run_options,
              const InputMatricesRoot::Reader& input_matrices,
              const QDir& plugin_dir) {
  if (!plugin_dir.exists()) {
    throw std::runtime_error("The plugin dir does not exist");
  }
  bool found_plugin = false;
  for (const auto& fileinfo : plugin_dir.entryInfoList(
           QStringList{} << "lib*.so", QDir::NoDotAndDotDot | QDir::Files)) {
    DemoPluginLoader loader(fileinfo.absoluteFilePath());

    if (loader.demo_plugin().simd_arch().toStdString() ==
            run_options.getSimdArch().cStr() &&
        loader.demo_plugin().num_loads() == run_options.getNumLoads() &&
        loader.demo_plugin().num_vertical_mixing() ==
            run_options.getNumVerticalMixing() &&
        two_to_the_power_of_impl<unsigned>(
            loader.demo_plugin().num_vertical_subdivisions()) ==
            input_matrices.getSpec().getNumMatrices() &&
        loader.demo_plugin().simdvector_bitlength() ==
            (input_matrices.getSpec().getNumMatrices() *
             input_matrices.getSpec().getMatrixHeight() *
             loader.demo_plugin().integertype_num_bits()) &&
        loader.demo_plugin().integertype() ==
            run_options.getIntegerChoice().cStr() &&
        loader.demo_plugin().matrix_width() ==
            input_matrices.getSpec().getMatrixWidth()) {
      loader.demo_plugin().iterate_diagonals(input_matrices);

      found_plugin = true;
      break;
    }
  }
  if (!found_plugin) {
    throw std::runtime_error("Could not find any plugin supporting the input");
  }
}

}  // namespace

int main(int argc, char** argv) {
  QCoreApplication app(argc, argv);
  const char* plugin_dir_path = PLUGIN_INSTALL_DIR;
  int return_value = EXIT_SUCCESS;

  switch (argc) {
    case 2: {
      if ((strcmp(argv[1], "--help") == 0) || (strcmp(argv[1], "-h") == 0)) {
        std::cout << command_line_usage_string() << std::endl;
      }
      break;
    }
    case 3: {
      if ((strcmp(argv[1], "--conf") == 0) || (strcmp(argv[1], "-c") == 0)) {
        try {
          capnp::MallocMessageBuilder message;
          auto root = message.initRoot<DemoRunOptions>();
          parseJsonFile(argv[2], root);
          auto options_reader = root.asReader();
          capnp::MallocMessageBuilder message2;
          auto root2 = message2.initRoot<InputMatricesRoot>();
          parseJsonFileDescriptor(STDIN_FILENO, root2);
          auto input_matrices_reader = root2.asReader();
          run_demo(options_reader, input_matrices_reader,
                   QDir(plugin_dir_path));
        } catch (const std::ifstream::failure& e) {
          std::cerr << "std::ifstream::failure=" << e.what() << std::endl;
          return_value = EXIT_FAILURE;
        } catch (const std::runtime_error& e) {
          std::cerr << "std::runtime_error = " << e.what() << std::endl;
          return_value = EXIT_FAILURE;
        } catch (const std::exception& e) {
          std::cerr << "error: std::exception :" << e.what() << std::endl;
          return_value = EXIT_FAILURE;
        } catch (...) {
          std::cerr << "error: unknown exception thrown" << std::endl;
          return_value = EXIT_FAILURE;
        }
        break;
      }
    }
    default: {
      std::cerr << "Wrong number of arguments. To see command line usage, "
                   "execute with --help flag\n";
      return_value = EXIT_FAILURE;
    }
  }
  return return_value;
}
