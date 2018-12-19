#include <optional>
#include <QString>
#include "try_to_parse_argv.h"

std::optional<parsed_options> try_to_parse_argv(int argc, char** argv) {
  if (argc != 5) {
    return {};
  }
  QString num_matrices_str(argv[1]);
  QString matrix_width_str(argv[2]);
  QString matrix_height_str(argv[3]);
  QString min_value_str(argv[4]);
  QString max_value_str(argv[5]);
  bool result;

  std::uint64_t num_matrices = num_matrices_str.toULongLong(&result);
  if (!result) {
    return {};
  }

  std::uint64_t matrix_width = matrix_width_str.toULongLong(&result);
  if (!result) {
    return {};
  }

  std::uint64_t matrix_height = matrix_height_str.toULongLong(&result);
  if (!result) {
    return {};
  }

  std::int64_t min_value = min_value_str.toLongLong(&result);
  if (!result) {
    return {};
  }

  std::int64_t max_value = max_value_str.toLongLong(&result);
  if (!result) {
    return {};
  }

  if (min_value > max_value) {
    return {};
  }
  return parsed_options{num_matrices, matrix_width, matrix_height, min_value,
                        max_value};
}
