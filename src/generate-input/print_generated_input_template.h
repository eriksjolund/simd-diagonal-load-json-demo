#ifndef PRINT_GENERATED_INPUT_TEMPLATE_H
#define PRINT_GENERATED_INPUT_TEMPLATE_H

#include <cstddef>
#include <string>
#include <simd-diagonal-load-json-demo/input-protobuf/input.pb.h>
#include <simd-diagonal-load-json-demo/protobuf-helper-funcs/print_json.h>
#include <iostream>
#include <cmath>

namespace {

unsigned two_to_the_power_of_impl2(unsigned num ) {
 if (num == 0) { return 1; }
   return 2 * two_to_the_power_of_impl2(num - 1);
}
}

template <typename IntegerType>
void print_generated_input(unsigned num_vertical_subdivisions,
                           input::Spec_integertype integertype,
                           unsigned simdvector_bitlength,
                           std::size_t matrix_width) {
  input::Root input_root;  // input_root will be filled with generated data and
                           // then printed to stdout

  auto spec = input_root.mutable_spec();

  spec->set_num_vertical_subdivisions(num_vertical_subdivisions);
  spec->set_matrix_width(matrix_width);

  spec->set_integertype_to_use(integertype);
  spec->set_simdvector_bitlength(simdvector_bitlength);

  std::size_t arr_index = 0;

  const unsigned num_matrices = two_to_the_power_of_impl2( num_vertical_subdivisions);
  const auto matrix_height =
      (simdvector_bitlength / (8 * sizeof(IntegerType))) / num_matrices;

  IntegerType iter = 0;

  for (int i = 0; i < num_matrices; ++i) {
    auto matrix = input_root.add_matrices();

    for (int j = 0; j < matrix_width; ++j) {
      auto column = matrix->add_columns();

      for (int k = 0; k < matrix_height; ++k) {
        if (iter == std::numeric_limits<IntegerType>::max()) {
          iter = 0;
        }
        column->add_elements(iter);
        ++iter;
      }
    }
  }
  print_json(input_root);
}

#endif  // PRINT_GENERATED_INPUT_TEMPLATE_H
