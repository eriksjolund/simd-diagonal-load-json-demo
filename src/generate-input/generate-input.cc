#include <cstdlib>
#include <cstring>
#include <string>
#include <sstream>
#include <iostream>
#include "print_generated_input_template.h"
#include <simd-diagonal-load-json-demo/input-protobuf/input.pb.h>

namespace {
std::vector<std::string> enum_values_as_strings() {
  std::vector<std::string> string_vec;
  const google::protobuf::EnumDescriptor* descriptor =
      input::Spec::integertype_descriptor();
  for (int i = 0; i < descriptor->value_count(); i++) {
    string_vec.push_back(descriptor->value(i)->name());
  }
  return string_vec;
}

std::string command_line_usage_string() {
  std::stringstream stream;
  stream << "Usage: generate-input num_matrices integertype "
            "simdvector_bitlength matrix_width\n\n"
            "integertype choose from: \n";

  for (auto str : enum_values_as_strings()) {
    stream << "     " << str << "\n";
  }
  return stream.str();
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
    case 5: {
      unsigned num_matrices = atoi(argv[1]);
      input::Spec_integertype spec_integertype_value;
      std::string integertype_str = argv[2];
      bool res = input::Spec::integertype_Parse(integertype_str,
                                                &spec_integertype_value);
      if (!res) {
        std::cerr << "Error: integer type : " << integertype_str << "\n"
                  << "was no found. To see command line usage, "
                     "execute with --help flag\n";
        return EXIT_FAILURE;
      }

      unsigned simdvector_bitlength = atoi(argv[3]);
      std::size_t matrix_width = atoi(argv[4]);

      switch (spec_integertype_value) {
        case input::Spec::uint8_t:
          print_generated_input<uint8_t>(num_matrices, spec_integertype_value,
                                         simdvector_bitlength, matrix_width);
          break;
        case input::Spec::uint16_t:
          print_generated_input<uint16_t>(num_matrices, spec_integertype_value,
                                          simdvector_bitlength, matrix_width);
          break;
        case input::Spec::uint32_t:
          print_generated_input<uint32_t>(num_matrices, spec_integertype_value,
                                          simdvector_bitlength, matrix_width);
          break;
        case input::Spec::uint64_t:
          print_generated_input<uint64_t>(num_matrices, spec_integertype_value,
                                          simdvector_bitlength, matrix_width);
          break;
        case input::Spec::int8_t:
          print_generated_input<int8_t>(num_matrices, spec_integertype_value,
                                        simdvector_bitlength, matrix_width);
          break;
        case input::Spec::int16_t:
          print_generated_input<int16_t>(num_matrices, spec_integertype_value,
                                         simdvector_bitlength, matrix_width);
          break;
        case input::Spec::int32_t:
          print_generated_input<int32_t>(num_matrices, spec_integertype_value,
                                         simdvector_bitlength, matrix_width);
          break;
        case input::Spec::int64_t:
          print_generated_input<int64_t>(num_matrices, spec_integertype_value,
                                         simdvector_bitlength, matrix_width);
          break;
        default:
          std::cerr << "Programming error: unkown type\n";
          return EXIT_FAILURE;
      }

      return EXIT_SUCCESS;
    }

    default: {
      std::cerr << "Wrong number of arguments. To see command line usage, "
                   "execute with --help flag\n";
      return EXIT_FAILURE;
    }
  }
  return EXIT_SUCCESS;
};
