#include <cstdlib>
#include <cstring>
#include <string>
#include <iostream>
#include <capnp/message.h>

#include <simd-diagonal-load-json-demo/capnproto-helper-funcs/parsejsonfile.h>

#include "print_generated_input.h"

#include <simd-diagonal-load-json-demo/input-spec/input-spec.capnp.h>

namespace {

const char* command_line_usage_string() {
  return "Usage: generate-input --help\n"
         "       generate-input --spec JSONFILE\n\n"
         "OPTIONS\n"
         "    -h, --help    show help\n"
         "    -c, --spec FILE   show generated input with the input spec in "
         "JSON format in the file FILE\n";
  "    -s, --show-example-conf show an example run option configuration\n";
}

}  // namespace

int main(int argc, char** argv) {
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
      if ((strcmp(argv[1], "--spec") == 0) || (strcmp(argv[1], "-c") == 0)) {
        capnp::MallocMessageBuilder message;
        auto root = message.initRoot<InputSpec>();
        parseJsonFile(argv[2], root);
        auto reader = root.asReader();

        print_generated_input(reader);
        return EXIT_SUCCESS;
      }
      std::cerr << "Incorrect usage. To see command line usage, "
                   "execute with --help flag\n";
      return EXIT_FAILURE;
    }
    default: {
      std::cerr << "Wrong number of arguments. To see command line usage, "
                   "execute with --help flag\n";
      return EXIT_FAILURE;
    }
  }
  return EXIT_SUCCESS;
};
