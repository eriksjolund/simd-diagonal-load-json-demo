@0xba48819e1a0cb9ea;

using Runopt = import "/simd-diagonal-load-json-demo/input-spec/input-spec.capnp";

struct InputColumn {
  elements @0 :List(Int64);
}

struct InputMatrix {
  columns @0 :List(InputColumn);
}

struct InputMatricesRoot {
  spec @0 :Runopt.InputSpec; 
  matrices @1 :List(InputMatrix);
}

