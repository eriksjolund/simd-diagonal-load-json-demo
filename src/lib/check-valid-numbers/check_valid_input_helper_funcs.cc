#include <simd-diagonal-load-json-demo/check-valid-numbers/check_valid_input_helper_funcs.h>
#include <cassert>    // for assert
#include <limits>     // for numeric_limits
#include <stdexcept>  // for runtime_error

void check_is_power_of_two(const uint32_t num, std::string name) {
  if (!(num != 0) && ((num & (num - 1)) == 0)) {
    throw std::runtime_error("The json field \"" + name +
                             "\" is not a power of 2");
  }
}

uint64_t max_value_for_unsigned_with_num_bits(const uint32_t num_bits) {
  if (!((num_bits >= 8) && (num_bits <= 64))) {
    throw std::runtime_error(
        "num_bits_per_element is not in the range from 8 to 64");
  }
  check_is_power_of_two(num_bits, "num_bits_per_element");
  switch (num_bits) {
    case 8:
      return std::numeric_limits<uint8_t>::max();
    case 16:
      return std::numeric_limits<uint16_t>::max();
    case 32:
      return std::numeric_limits<uint32_t>::max();
    case 64:
      return std::numeric_limits<uint64_t>::max();
    default:
      assert(false);
      throw std::runtime_error(
          "num_bits_per_element needs to be 8, 16, 32 or 64");
  }
}

void check_valid_range(unsigned value,
                       const std::string& value_name,
                       unsigned min,
                       const std::string& min_name,
                       unsigned max,
                       const std::string& max_name) {
  if (value < min) {
    throw std::runtime_error(value_name + " value is less than " + min_name);
  }
  if (value > max) {
    throw std::runtime_error(value_name + " value is greater than " + max_name);
  }
}
