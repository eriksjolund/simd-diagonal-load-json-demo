#ifndef JSON_MATRIX_H
#define JSON_MATRIX_H

#include <array>
#include <algorithm>
#include <cassert>
#include <limits>
#include <array>
#include <vector>
#include <sstream>
#include <fstream>
#include <simdpp/simd.h>

//#include <simd-diagonal-load/algorithm/typelookup.h>
#include <simd-diagonal-load/algorithm/lookup_templates.h>
#include <simd-diagonal-load/array-helper/array_helper.h>

#include <google/protobuf/util/json_util.h>

#include <simd-diagonal-load-json-demo/input-protobuf/input.pb.h>
#include <simd-diagonal-load-json-demo/output-protobuf/output.pb.h>

#include <simd-diagonal-load-json-demo/protobuf-helper-funcs/print_json.h>

namespace {

void add_empty_matrices(output::Root& output_root, const unsigned count) {
  for (int i = 0; i < count; ++i) {
    auto result_matrices = output_root.mutable_result()->add_matrices();
  }
}

}  // namespace

template <typename integerT,
          unsigned simd_vector_length,
          unsigned num_loads,
          unsigned num_vertical_subdivisions,
          unsigned num_vertical_mixing,
          std::size_t MatrixWidth>
class JsonMatrix {
  //  typedef TypeLookup<  integerT,                     simd_vector_length,
  //  num_loads,                     num_vertical_subdivisions>      lookup;

  typedef
      typename lookup_vec_from_integertype<integerT, simd_vector_length>::type
          looked_up_vec;

 public:
  JsonMatrix(input::Root input_root) : input_root_{input_root} {
    add_empty_matrices(output_root_, num_vertical_subdivisions);
  }

  inline looked_up_vec get_next_column() {
    std::array<
        std::array<integerT, simd_vector_length / num_vertical_subdivisions>,
        num_vertical_subdivisions>
        values;
    std::array<integerT, simd_vector_length> arr;
    std::size_t arr_index = 0;
    auto simd_input = output_root_.mutable_internal()->add_simd_input();
    for (int j = 0; j < simd_vector_length; ++j) {
      auto element = simd_input->add_elements();
    }

    for (int i = 0; i < num_vertical_subdivisions; ++i) {
      assert(i < input_root_.matrices_size());
      auto matrix = input_root_.matrices(i);
      assert(column_index_ < matrix.columns_size());
      auto cols = matrix.columns(column_index_);

      for (int j = 0; j < simd_vector_length / num_vertical_subdivisions; ++j) {
        auto value = cols.elements(j);
        const auto simd_index =
            get_index(i, j, simd_vector_length / num_vertical_subdivisions,
                      num_vertical_subdivisions, num_vertical_mixing);
        arr[simd_index] = value;

        // Is this correct use of the protobuf API?

        auto mutable_element =
            simd_input->mutable_elements(simd_index)->mutable_element();
        mutable_element->set_value(value);
        ++arr_index;
      }
    }
    looked_up_vec vec = simdpp::load_u<looked_up_vec>(&arr[0]);
    ++column_index_;
    return vec;
  }

  template <unsigned startpos, unsigned endpos>
  inline void handle_diagonal(const looked_up_vec& vec) {
    auto simd_output = output_root_.mutable_internal()->add_simd_output();
    constexpr const unsigned simd_num_bits_per_element = 8 * sizeof(integerT);
    auto arr = to_array<simd_num_bits_per_element, simd_vector_length>(vec);

    for (unsigned j = 0; j < simd_vector_length; ++j) {
      auto element = simd_output->add_elements();
      auto mutable_element = element->mutable_element();
      mutable_element->set_value(arr[j]);
    }
    {
      std::size_t arr_index = 0;
      for (int i = 0; i < num_vertical_subdivisions; ++i) {
        assert(i < output_root_.result().matrices_size());
        auto matrix = output_root_.mutable_result()->mutable_matrices(i);
        auto diagonals = matrix->add_diagonals();
        for (int j = 0; j < simd_vector_length / num_vertical_subdivisions;
             ++j) {
          const auto ind =
              get_index(i, j, simd_vector_length / num_vertical_subdivisions,
                        num_vertical_subdivisions, num_vertical_mixing);
          auto value = arr[ind];
          auto element = diagonals->add_elements();
          if (j >= startpos && j <= endpos) {
            auto mutable_element = element->mutable_element();
            mutable_element->set_value(value);
          }
          ++arr_index;
        }
      }
    }
  }

  void print_output() { print_json(output_root_); }

 private:
  input::Root input_root_;
  output::Root output_root_;
  std::size_t column_index_ = 0;
};

#endif  // JSON_MATRIX_H
