#include <cstdlib>
#include <cstring>
#include <iostream>

#include <QCoreApplication>
#include <QDebug>
#include <QDir>
#include <QtPlugin>

#include <simd-diagonal-load-json-demo/defines-from-cmake-variables/config.h>
#include <simd-diagonal-load-json-demo/demo-plugin-interface/demo_plugin_interface.h>
#include <simd-diagonal-load-json-demo/demo-pluginloader/demo_pluginloader.h>
#include <simd-diagonal-load-json-demo/protobuf-helper-funcs/json_input_from_stdin.h>

const char* command_line_usage_string() {
  return "Usage: demo num_loads num_vertical_mixing\n\n"
         "num_vertical    an integer number greater than or equal to 1.\n"
         "                 1 means no mixing. To get \"full mixing\" specify \n"
         "the number of matrices in the JSON input.\n\n"
         "The JSON input is read from stdin";
}

int main(int argc, char** argv) {
  QCoreApplication app(argc, argv);
  switch (argc) {
    case 2: {
      if ((strcmp(argv[1], "--help") == 0) || (strcmp(argv[1], "-h") == 0)) {
        std::cout << command_line_usage_string() << std::endl;
        return EXIT_SUCCESS;
      }
      std::cerr << "Incorrect usage. To see command line usage, "
                   "execute with --help flag\n";
      return EXIT_FAILURE;
    }
    case 3: {
      unsigned num_loads = atoi(argv[1]);
      unsigned num_vertical_mixing = atoi(argv[2]);
      QDir plugin_dir(PLUGIN_INSTALL_DIR);
      if (!plugin_dir.exists()) {
        throw std::runtime_error("The plugin dir does not exist");
      }
      input::Root input_root = json_input_from_stdin<input::Root>();
      bool found_plugin = false;
      for (const auto& fileinfo :
           plugin_dir.entryInfoList(QStringList{} << "lib*.so",
                                    QDir::NoDotAndDotDot | QDir::Files)) {
        DemoPluginLoader loader(fileinfo.absoluteFilePath());
        if (loader.demo_plugin().num_loads() == num_loads &&
            loader.demo_plugin().num_vertical_mixing() == num_vertical_mixing &&
            loader.demo_plugin().num_vertical_subdivisions() ==
                input_root.spec().num_vertical_subdivisions() &&
            loader.demo_plugin().simdvector_bitlength() ==
                input_root.spec().simdvector_bitlength() &&
            loader.demo_plugin().integertype() ==
                input_root.spec().integertype_to_use() &&
            loader.demo_plugin().matrix_width() ==
                input_root.spec().matrix_width()) {
          loader.demo_plugin().iterate_diagonals(input_root);
          found_plugin = true;
          break;
        }
      }
      if (!found_plugin) {
        std::cerr << "Could not find any plugin supporting:\n";
        std::cerr << "num_loads = " << num_loads << "\n";
        std::cerr << "num_vertical_mixing  = " << num_vertical_mixing << "\n";
        std::cerr << "num_vertical_subdivions = "
                  << input_root.spec().num_vertical_subdivisions() << "\n";
        std::cerr << "simdvector_bitlength = "
                  << input_root.spec().simdvector_bitlength() << "\n";
        //        std::cerr << "num_bits_per_element = " <<
        //        input_root.spec().num_bits_per_element() << "\n";
        return EXIT_FAILURE;
      }
      break;
    }
    default: {
      std::cerr << "Wrong number of arguments. To see command line usage, "
                   "execute with --help flag\n";
      return EXIT_FAILURE;
    }
  }
  return EXIT_SUCCESS;
}
