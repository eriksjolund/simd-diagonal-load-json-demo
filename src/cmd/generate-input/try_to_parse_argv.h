#ifndef TRY_TO_PARSE_ARGV
#define TRY_TO_PARSE_ARGV

#include <optional>
#include "parsed_options.h"

std::optional<parsed_options> try_to_parse_argv(int argc, char** argv);

#endif  // TRY_TO_PARSE_ARGV
