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
#include <type_traits>
#include <simdpp/simd.h>

#include <capnp/message.h>
#include <simd-diagonal-load-json-demo/output-matrices/output-matrices.capnp.h>

//#include <simd-diagonal-load/algorithm/typelookup.h>
#include <simd-diagonal-load/algorithm/lookup_templates.h>
#include <simd-diagonal-load/algorithm/algorithm_types.h>
#include <simd-diagonal-load/algorithm/power_of_two.h>
#include <simd-diagonal-load/array-helper/array_helper.h>

#include <simd-diagonal-load-json-demo/input-matrices/input-matrices.capnp.h>

#include <simd-diagonal-load-json-demo/demo-run-options/demo-run-options.capnp.h>

#include <simd-diagonal-load-json-demo/capnproto-helper-funcs/print_json.h>

template <typename integerT,
          unsigned simd_vector_length,
          num_loads_t num_loads,
          num_vertical_subdivisions_t num_vertical_subdivisions,
          num_vertical_mixing_t num_vertical_mixing,
          unsigned MatrixWidth>
class JsonMatrix {
  typedef
      typename lookup_vec_from_integertype<integerT, simd_vector_length>::type
          looked_up_vec;

 public:
  constexpr static const unsigned num_matrices =
      two_to_the_power_of<unsigned, num_vertical_subdivisions>();

  constexpr static const unsigned num_simd_outputs =
      MatrixWidth +
      (simd_vector_length /
       two_to_the_power_of<std::size_t, num_vertical_subdivisions>()) -
      1;

 public:
  JsonMatrix(const InputMatricesRoot::Reader& input_matrices)
      : input_matrices_{input_matrices},
        output_root_{output_message_.initRoot<OutputMatricesRoot>()},
        simd_input_builder_{
            output_root_.getInternal().initSimdInput(MatrixWidth)},
        simd_output_builder_{
            output_root_.getInternal().initSimdOutput(num_simd_outputs)} {
    {
      assert(input_matrices.getSpec().getNumMatrices() == num_matrices);

      auto build = output_root_.initMatrices(num_matrices);
      for (auto matrix : build) {
        auto diagonals = matrix.initDiagonals(num_simd_outputs);
        for (auto diagonal : diagonals) {
          diagonal.initElements(simd_vector_length / num_matrices);
        }
      }
    }
  }

  inline looked_up_vec get_next_column() {
    std::array<std::array<integerT, simd_vector_length / num_matrices>,
               num_matrices>
        values;
    std::array<integerT, simd_vector_length> arr;
    std::size_t arr_index = 0;

    auto simd_input_elements_builder =
        simd_input_builder_[column_index_].initElements(simd_vector_length);

    for (int i = 0; i < num_matrices; ++i) {
      assert(i < input_matrices_.getMatrices().size());
      auto matrix = input_matrices_.getMatrices()[i];
      assert(column_index_ < matrix.getColumns().size());
      auto cols = matrix.getColumns()[column_index_];
      for (int j = 0; j < simd_vector_length / num_matrices; ++j) {
        assert(j < cols.getElements().size());

        const auto simd_index =
            get_index(i, j, simd_vector_length / num_matrices, num_matrices,
                      num_vertical_mixing);
        auto value = cols.getElements()[j];
        arr[simd_index] = value;
        assert(simd_index < simd_input_elements_builder.size());

        simd_input_elements_builder.set(simd_index, value);

        ++arr_index;
      }
    }
    looked_up_vec vec = simdpp::load_u<looked_up_vec>(&arr[0]);
    ++column_index_;
    return vec;
  }
  template <unsigned startpos, unsigned endpos>
  inline void handle_diagonal(const looked_up_vec& vec) {
    constexpr const unsigned simd_num_bits_per_element = 8 * sizeof(integerT);
    auto arr = to_array<simd_num_bits_per_element, simd_vector_length>(vec);

    assert(diagonals_handled_ < simd_output_builder_.size());
    auto simd_output_elements_builder =
        simd_output_builder_[diagonals_handled_].initElements(
            simd_vector_length);

    for (unsigned i = 0; i < simd_vector_length; ++i) {
      assert(i < simd_output_elements_builder.size());
      simd_output_elements_builder.set(i, arr[i]);
    }

    {
      std::size_t arr_index = 0;
      for (int i = 0; i < num_matrices; ++i) {
        for (int j = 0; j < simd_vector_length / num_matrices; ++j) {
          const auto ind = get_index(i, j, simd_vector_length / num_matrices,
                                     num_matrices, num_vertical_mixing);
          auto value = arr[ind];

          if (j >= startpos && j <= endpos) {
            // TODO: change so that we don't look up all the top structures
            // every time...
            auto elem = output_root_.getMatrices()[i]
                            .getDiagonals()[diagonals_handled_]
                            .getElements()[j];
            elem.setValue(value);
          }
          ++arr_index;
        }
      }
      ++diagonals_handled_;
    }
  }
  void print_output() { print_json(output_root_); }

 private:
  std::size_t column_index_ = 0;
  std::size_t diagonals_handled_ = 0;

  const InputMatricesRoot::Reader& input_matrices_;

  capnp::MallocMessageBuilder output_message_;
  OutputMatricesRoot::Builder output_root_;
  ::capnp::List< ::Elements, ::capnp::Kind::STRUCT>::Builder
      simd_input_builder_;
  ::capnp::List< ::Elements, ::capnp::Kind::STRUCT>::Builder
      simd_output_builder_;
};

#endif  // JSON_MATRIX_H
