#include <cstdlib>
#include <cstring>
#include <iostream>
#include <string>
#include <unistd.h>

#include <capnp/message.h>

#include <simd-diagonal-load-json-demo/capnproto-helper-funcs/parsejsonfile.h>

#include "print_generated_input.h"

#include <simd-diagonal-load-json-demo/input-spec/input-spec.capnp.h>

namespace {

const char* command_line_usage_string() {
  return "Usage: generate-input --help\n"
         "       generate-input\n\n"
         "OPTIONS\n"
         "    -h, --help    show help\n"
         "    -s, --show-example-input-spec    show an example INPUT SPEC JSON\n\n"
         "Without any arguments, generate-input will read the INPUT SPEC JSON FILE\n"
         "from STDIN.\n\n"
         "EXAMPLE\n"
         "generate-input -s | generate-input\n" ;
}

}  // namespace

int main(int argc, char** argv) {
  switch (argc) {
    case 1: {
      capnp::MallocMessageBuilder message;
      auto root = message.initRoot<InputSpec>();
      parseJsonFileDescriptor(STDIN_FILENO, root);
      auto reader = root.asReader();
      print_generated_input(reader);
      return EXIT_SUCCESS;
    }
    case 2: {
      if ((strcmp(argv[1], "--help") == 0) || (strcmp(argv[1], "-h") == 0)) {
        std::cout << command_line_usage_string() << std::endl;
        return EXIT_SUCCESS;
      }
      if ((strcmp(argv[1], "--show-example-input-spec") == 0) || (strcmp(argv[1], "-s") == 0)) {
        std::cout << "TODO: write example JSON here\n";
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
