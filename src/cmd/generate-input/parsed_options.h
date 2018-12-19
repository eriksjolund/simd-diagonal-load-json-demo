#ifndef PARSED_OPTIONS
#define PARSED_OPTIONS

struct parsed_options {
  std::uint64_t num_matrices;
  std::uint64_t matrix_width;
  std::uint64_t matrix_height;
  std::int64_t min_value;
  std::int64_t max_value;
};

#endif  // PARSED_OPTIONS
