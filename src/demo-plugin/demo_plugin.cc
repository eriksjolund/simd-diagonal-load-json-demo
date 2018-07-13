#include "demo_plugin.h"
#include "json_matrix.h"
#include <sstream>
#include <simd-diagonal-load/algorithm/simd_diagonal_load.h>
#include <QString>
#include <simd-diagonal-load-json-demo/input-protobuf/input.pb.h>

#define preprocessor_xstr(s) preprocessor_str(s)
#define preprocessor_str(s) #s

QString DemoPlugin::demo_name() const {
  return QString(PLUGIN_NAME);
}

unsigned DemoPlugin::num_loads() const {
  return NUM_LOADS;
}

unsigned DemoPlugin::num_vertical_mixing() const {
  return NUM_VERTICAL_MIXING;
}
unsigned DemoPlugin::num_vertical_subdivisions() const {
  return NUM_VERTICAL_SUBDIVISIONS;
}

input::Spec::integertype DemoPlugin::integertype() const {
  return input::Spec::INTEGERTYPE;
}

unsigned DemoPlugin::simdvector_bitlength() const {
  return SIMDVECTOR_BITLENGTH;
}

unsigned DemoPlugin::matrix_width() const {
  return MATRIX_WIDTH;
}

void DemoPlugin::iterate_diagonals(const input::Root& input_root) const {
  constexpr const unsigned num_bits_per_element = 8 * sizeof(INTEGERTYPE);
  using JsonM =
      //    JsonMatrix< preprocessor_macro_prepend_std(INTEGERTYPE),
      JsonMatrix<std::INTEGERTYPE,
                 SIMDVECTOR_BITLENGTH /
                     (num_bits_per_element * NUM_VERTICAL_SUBDIVISIONS),
                 NUM_LOADS, NUM_VERTICAL_SUBDIVISIONS, NUM_VERTICAL_MIXING,
                 MATRIX_WIDTH>;
  JsonM json_matrix{input_root};
  IterateDiagonalsTemplate<std::INTEGERTYPE,
                           SIMDVECTOR_BITLENGTH / (num_bits_per_element *
                                                   NUM_VERTICAL_SUBDIVISIONS),
                           NUM_LOADS, NUM_VERTICAL_SUBDIVISIONS,
                           NUM_VERTICAL_MIXING, MATRIX_WIDTH, JsonMatrix>()
      .iterate_diagonals(json_matrix);
  json_matrix.print_output();
}
