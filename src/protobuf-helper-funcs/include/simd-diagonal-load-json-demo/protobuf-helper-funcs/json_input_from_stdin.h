#ifndef JSON_INPUT_FROM_STDIN_H
#define JSON_INPUT_FROM_STDIN_H

#include <iostream>
#include <sstream>
#include <fstream>

#include <google/protobuf/util/json_util.h>

#include <sstream>
#include <fstream>
#include <google/protobuf/util/json_util.h>
#include <simd-diagonal-load-json-demo/input-protobuf/input.pb.h>

template <typename protobuf_input>
protobuf_input json_input_from_stdin() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;
  std::stringstream buffer;
  buffer << std::cin.rdbuf();
  google::protobuf::util::JsonParseOptions parse_options;
  input::Root root;
  JsonStringToMessage(buffer.str(), &root, parse_options);
  return root;
}

#endif  // JSON_INPUT_FROM_STDIN_H
