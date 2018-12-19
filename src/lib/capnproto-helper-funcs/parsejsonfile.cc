#include <fstream>

#include <capnp/compat/json.h>
#include <simd-diagonal-load-json-demo/capnproto-helper-funcs/parsejsonfile.h>

#include <kj/std/iostream.h>

void parseJsonFile(char* filepath, capnp::DynamicStruct::Builder builder) {
  // Probably not the most efficient implementation.
  // But this function is not optimized for speed in any way.
  std::ifstream stream(filepath);
  std::string str(std::istreambuf_iterator<char>{stream}, {});
  kj::StringPtr kjstr(str.c_str());
  capnp::JsonCodec codec;
  codec.decode(kjstr, builder);
}

void parseJsonStdin(capnp::DynamicStruct::Builder builder) {
  std::string str(std::istreambuf_iterator<char>{std::cin}, {});
  kj::StringPtr kjstr(str.c_str());
  capnp::JsonCodec codec;
  codec.decode(kjstr, builder);
}
