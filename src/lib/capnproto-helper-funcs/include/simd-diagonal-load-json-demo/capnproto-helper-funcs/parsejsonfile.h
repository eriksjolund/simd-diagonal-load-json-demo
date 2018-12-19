#ifndef PARSEJSONFILE
#define PARSEJSONFILE
#include <capnp/compat/json.h>
void parseJsonFile(char* filepath, capnp::DynamicStruct::Builder builder);
void parseJsonStdin(capnp::DynamicStruct::Builder builder);
#endif
