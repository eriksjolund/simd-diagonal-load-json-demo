#ifndef PRINT_JSON_H
#define PRINT_JSON_H

#include <unistd.h>
#include <string>
#include <kj/io.h>

#include <iostream>

#include <iostream>
#include <string>
#include <capnp/compat/json.h>

template <typename T>
void print_json(T some_struct_reader) {
  capnp::JsonCodec codec;
  codec.setPrettyPrint(true);
  kj::String encoded = codec.encode(some_struct_reader);
  kj::FdOutputStream stream(STDOUT_FILENO);
  stream.write({encoded.asBytes()});
  std::cout << std::endl;
}

#endif  // PRINT_JSON_H
