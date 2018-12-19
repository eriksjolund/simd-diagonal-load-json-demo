#ifndef PRINT_RESULT_H
#define PRINT_RESULT_H
#include <cassert>

#include <simd-diagonal-load/algorithm/algorithm_types.h>

#include <simd-diagonal-load-json-demo/capnproto-helper-funcs/print_json.h>
#include <simd-diagonal-load/array-helper/two_to_the_power_of.h>
namespace {}

template <typename integerT, unsigned simd_vector_length>
void copy_simd_values(
    const std::vector<std::array<integerT, simd_vector_length> > simd_vectors,
    ::capnp::List< ::Elements, ::capnp::Kind::STRUCT>::Builder& builder) {
  for (int i = 0; i < simd_vectors.size(); ++i) {
    auto elements = builder[i].initElements(simd_vector_length);
    auto simd_vector = simd_vectors.at(i);
    for (int j = 0; j < simd_vector_length; ++j) {
      elements.set(j, simd_vector.at(j));
    }
  }
}

template <typename integerT,
          unsigned simd_vector_length,
          num_vertical_subdivisions_t num_vertical_subdivisions>
void copy_matrix(
    const Result<integerT, simd_vector_length, num_vertical_subdivisions>::vecT&
        matrix,
    ::capnp::List< ::DiagonalMatrix, ::capnp::Kind::STRUCT>::Builder& builder) {
  auto diag_builder = builder.initDiagonals(matrix.size());

  std::size_t index = 0;
  for (const auto& diagonal : matrix) {
    for (const auto& diagonal : matrix) {
    }

    copy_matrix< integerT, simd_vector_length, num_vertical_subdivisions >(matrix, 
    assert(index < std::numeric_limits<decltype(index)::max());
    ++index;
  }
}

template <typename integerT,
          unsigned simd_vector_length,
          num_vertical_subdivisions_t num_vertical_subdivisions>
void copy_matrices(
    const Result<integerT, simd_vector_length, num_vertical_subdivisions>::
        arrayT& matrices,
    ::capnp::List< ::DiagonalMatrix, ::capnp::Kind::STRUCT>::Builder& builder) {
  std::size_t index = 0;
  for (const auto& matrix : matrices) {
    assert(index < builder.size());
    copy_matrix<integerT, simd_vector_length, num_vertical_subdivisions>(
        matrix, builder[index]);
    assert(index < std::numeric_limits < decltype(index)::max());
    ++index;
  }
}
}

template <typename integerT,
          unsigned simd_vector_length,
          num_vertical_subdivisions_t num_vertical_subdivisions>
void print_result(
    const Result<integerT, simd_vector_length, num_vertical_subdivisions>&
        result) {
  copy_simd_values(result.simd_inputs, simd_input_builder);

  auto simd_output_builder =
      output_root.getInternal().initSimdOutput(result.simd_outputs.size());
  copy_simd_values(result.simd_outputs, simd_output_builder);
  auto matrices = output_root.initMatrices(num_vertical_subdivisions);
  copy_matrices<integerT, simd_vector_length, num_vertical_subdivisions>(
      result.matrices_diags, matrices);

  print_json(simd_output_builder.asReader());

  //  output_root_.getInternal().initSimdOutput(result.simd_outputs.size());
  // result.

  // result.simd_outputs
}
#endif  // PRINT_RESULT_H
