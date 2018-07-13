#include <simd-diagonal-load-json-demo/protobuf-helper-funcs/print_json.h>
#include <google/protobuf/util/json_util.h>
#include <iostream>
#include <string>

void print_json(const google::protobuf::Message& message) {
  google::protobuf::util::JsonPrintOptions options;
  options.add_whitespace = true;
  std::string output_str;
  MessageToJsonString(message, &output_str, options);
  std::cout << output_str << std::endl;
}
