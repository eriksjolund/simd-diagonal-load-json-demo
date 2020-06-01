#include <fstream>

#include <capnp/compat/json.h>
#include <simd-diagonal-load-json-demo/capnproto-helper-funcs/parsejsonfile.h>

#include <kj/std/iostream.h>
#include <kj/io.h>

void parseJsonFile(char* filepath, capnp::DynamicStruct::Builder builder) {
  // Probably not the most efficient implementation.
  // But this function is not optimized for speed in any way.
  std::ifstream stream(filepath);
  std::string str(std::istreambuf_iterator<char>{stream}, {});
  kj::StringPtr kjstr(str.c_str());
  capnp::JsonCodec codec;
  codec.decode(kjstr, builder);
}

void parseJsonFileDescriptor(int fd, capnp::DynamicStruct::Builder builder) {
  kj::FdInputStream input_stream(fd);
  uint64_t max_bytes_limit = 1024*1024*1024; // 1 Gb (arbitrarily chosen)
  kj::String str = input_stream.readAllText(max_bytes_limit);
  capnp::JsonCodec codec;
  codec.decode(str, builder);
}
