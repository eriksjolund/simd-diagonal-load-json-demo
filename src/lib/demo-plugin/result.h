#ifndef RESULT_H
#define RESULT_H

#include <array>
#include <vector>

#include <simd-diagonal-load/algorithm/power_of_two.h>

template <typename integerT>
struct ResultDiagonal {
  std::vector<integerT> diagonal;
  unsigned startPos;
  unsigned endPos;
};

template <typename integerT,
          unsigned simd_vector_length,
          num_vertical_subdivisions_t num_vertical_subdivisions>
struct Result {
  using simdT = std::vector<std::array<integerT, simd_vector_length> >;
  simdT simd_inputs;
  simdT simd_outputs;
  using vecT = std::vector<ResultDiagonal<integerT> >;
  using arrayT =
      std::array<vecT,
                 two_to_the_power_of<std::size_t, num_vertical_subdivisions>()>;

  arrayT matrices_diags;
};
#endif  // RESULT_H
