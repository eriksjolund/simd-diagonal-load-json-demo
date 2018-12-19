#include "demo_plugin.h"
#include "json_matrix.h"
#include <type_traits>
#include <sstream>
#include <simd-diagonal-load/algorithm/algorithm_types.h>
#include <simd-diagonal-load/algorithm/simd_diagonal_load.h>
#include <QString>

#include "build_time_plugin_config.h"
#include <simd-diagonal-load-json-demo/input-matrices/input-matrices.capnp.h>

//#define preprocessor_xstr(s) preprocessor_str(s)
//#define preprocessor_str(s) #s

QString DemoPlugin::demo_name() const {
  return QString(build_time_plugin_config::plugin_name);
}

QString DemoPlugin::simd_arch() const {
  //  return QString( preprocessor_xstr(SIMD_A) );
  return QString(build_time_plugin_config::simd_arch);
}

num_loads_t DemoPlugin::num_loads() const {
  return build_time_plugin_config::num_loads;
}

num_vertical_mixing_t DemoPlugin::num_vertical_mixing() const {
  return build_time_plugin_config::num_vertical_mixing;
}

num_vertical_subdivisions_t DemoPlugin::num_vertical_subdivisions() const {
  return build_time_plugin_config::num_vertical_subdivisions;
}

// input::Spec::integertype DemoPlugin::integertype() const {
QString DemoPlugin::integertype() const {
  return QString(build_time_plugin_config::integertype);
  //  return input::Spec::INTEGERTYPE;
}

std::uint8_t DemoPlugin::integertype_num_bits() const {
  return 8 * sizeof(std::INTEGERTYPE);
};

bool DemoPlugin::integertype_signed() const {
  return std::is_signed<std::INTEGERTYPE>();
}

unsigned DemoPlugin::simdvector_bitlength() const {
  return build_time_plugin_config::simdvector_bitlength;
}

unsigned DemoPlugin::matrix_width() const {
  return build_time_plugin_config::matrix_width;
}

void DemoPlugin::iterate_diagonals(
    const InputMatricesRoot::Reader& input_matrices) const {
  constexpr const unsigned num_bits_per_element = 8 * sizeof(INTEGERTYPE);
  using JsonM =
      //    JsonMatrix< preprocessor_macro_prepend_std(INTEGERTYPE),
      JsonMatrix<std::INTEGERTYPE,
                 SIMDVECTOR_BITLENGTH / (num_bits_per_element), NUM_LOADS,
                 NUM_VERTICAL_SUBDIVISIONS, NUM_VERTICAL_MIXING, MATRIX_WIDTH>;
  JsonM json_matrix{input_matrices};
  IterateDiagonalsTemplate<std::INTEGERTYPE,
                           SIMDVECTOR_BITLENGTH / num_bits_per_element,
                           NUM_LOADS, NUM_VERTICAL_SUBDIVISIONS,
                           NUM_VERTICAL_MIXING, MATRIX_WIDTH, JsonMatrix>()
      .iterate_diagonals(json_matrix);
  json_matrix.print_output();
}
