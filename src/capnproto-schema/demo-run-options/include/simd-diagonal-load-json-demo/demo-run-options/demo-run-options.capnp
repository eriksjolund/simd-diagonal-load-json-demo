@0xe284678adf312878;

# enum SimdArch {
#     x86sse2 @0;
#     x86sse3 @1;
#     x86ssse3 @2;
#     x86sse41 @3;
#     x86popcntinsn @4;
#     x86avx @5;
#     x86avx2 @6;
#     x86avx512f @7;
#     x86avx512bw @8;
#     x86avx512dq @9;
#     x86avx512vl @10;
#     armneon @11;
#     arm64neon @12;
# }

# enum IntegerChoice {
#   uint8 @0;
#   uint16 @1;
#   uint32 @2;
#   uint64 @3;
#   int8 @4;
#   int16 @5;
#   int32 @6;
#   int64 @7;
# }

struct DemoRunOptions {
  numLoads @0 :UInt8;
  numVerticalSubdivisions @1 :UInt8;
  numVerticalMixing @2 :UInt8;
  simdArch @3 :Text;
  integerChoice @4 :Text;
# When JSON annotations pull request have been merged, we should probably use
# enums instead of :Text for simdArch and integerChoice
# https://github.com/capnproto/capnproto/pull/700


#  simdArch @3 :SimdArch;
#  integerChoice @4 :IntegerChoice;

}
