#ifndef CHECK_VALID_INPUT_HELPER_FUNCS_H
#define CHECK_VALID_INPUT_HELPER_FUNCS_H

#include <cstdint>
#include <string>  // for string

void check_is_power_of_two(const uint32_t num, std::string name);

uint64_t max_value_for_unsigned_with_num_bits(const uint32_t num_bits);

void check_valid_range(unsigned value,
                       const std::string& value_name,
                       unsigned min,
                       const std::string& min_name,
                       unsigned max,
                       const std::string& max_name);

#endif  // CHECK_VALID_INPUT_HELPER_FUNCS_H
