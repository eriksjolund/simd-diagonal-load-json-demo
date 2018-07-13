#include <cstdint>
#include <simd-diagonal-load/algorithm/check_template_parameters.h>

#define aaa "uint8_t"
#define preprocessor_macro_prepend_std(x) return std::_##x

int main() {
  check_template_parameters<std::uint8_t, SIMDVECTOR_BITLENGTH,
                            NUM_VERTICAL_SUBDIVISIONS, NUM_VERTICAL_MIXING,
                            NUM_LOADS>();
  return 0;
}
