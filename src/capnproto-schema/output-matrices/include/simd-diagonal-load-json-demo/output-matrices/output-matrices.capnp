@0xa2dd1ea70cf8809c;

struct MaybeElement {
  union {
    empty @0 :Void;
    value @1 :Int64;
  }
}

struct Diagonal {
  elements @0 :List(MaybeElement);
}

struct DiagonalMatrix {
  diagonals @0 :List(Diagonal);
}

struct Elements {
  elements @0 :List(Int64);
}

struct Internal {
  simdInput @0 :List(Elements);
  simdOutput @1 :List(Elements);
}

struct OutputMatricesRoot {
  matrices  @0 :List(DiagonalMatrix);
  internal @1 :Internal;
}
















