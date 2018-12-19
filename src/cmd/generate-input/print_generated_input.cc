#include "print_generated_input.h"
#include <cstddef>
#include <cmath>
#include <cassert>
#include <capnp/compat/json.h>
#include <capnp/message.h>

#include <simd-diagonal-load-json-demo/input-spec/input-spec.capnp.h>
#include <simd-diagonal-load-json-demo/input-matrices/input-matrices.capnp.h>
#include <simd-diagonal-load-json-demo/capnproto-helper-funcs/print_json.h>
namespace {

void fill_matrices(InputSpec::Reader reader,
                   InputMatricesRoot::Builder& input_matrices) {
  input_matrices.setSpec(reader);
  std::int64_t iter = reader.getMinValue();
  auto matrices_builder = input_matrices.initMatrices(reader.getNumMatrices());
  for (std::uint64_t i = 0; i < reader.getNumMatrices(); ++i) {
    auto columns_builder =
        matrices_builder[i].initColumns(reader.getMatrixWidth());
    for (std::uint64_t j = 0; j < reader.getMatrixWidth(); ++j) {
      auto elements_builder =
          columns_builder[j].initElements(reader.getMatrixHeight());
      for (std::uint64_t k = 0; k < reader.getMatrixHeight(); ++k) {
        if (iter > reader.getMaxValue()) {
          iter = reader.getMinValue();
        }
        elements_builder.set(k, iter);
        ++iter;
      }
    }
  }
}
}  // namespace

void print_generated_input(InputSpec::Reader reader) {
  if (reader.getMinValue() > reader.getMaxValue()) {
    throw std::runtime_error("min value is bigger than max value");
  }
  ::capnp::MallocMessageBuilder message;
  InputMatricesRoot::Builder input_matrices =
      message.initRoot<InputMatricesRoot>();

  fill_matrices(reader, input_matrices);
  print_json(input_matrices.asReader());
}
