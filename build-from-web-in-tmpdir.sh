#!/bin/sh
set -e

build_and_install() {

builddir=`mktemp -d`
cd $builddir
cmake -G Ninja -DCMAKE_INSTALL_PREFIX=$2  -DCMAKE_PREFIX_PATH=$2  -DBUILD_SHARED_LIBS=on $1/$3
ninja -v
ninja install
}

srcdir=/tmp/tmp.RYzllu7xyD
if /bin/false; then
  srcdir=`mktemp -d`
  cd $srcdir

  git clone https://github.com/eriksjolund/simd-diagonal-load.git
  git -C simd-diagonal-load checkout rearrange
  git clone https://github.com/eriksjolund/simd-diagonal-load-json-demo.git
  git clone https://github.com/eriksjolund/libsimdpp.git
  git -C libsimdpp checkout modernize_cmake_support 
  git clone https://github.com/capnproto/capnproto.git
fi
installdir=`mktemp -d`

export LD_LIBRARY_PATH="$installdir/lib:$LD_LIBRARY_PATH"
export PATH="$installdir/bin:$PATH"

build_and_install $srcdir $installdir libsimdpp/cmake/simd-compile-options
build_and_install $srcdir $installdir libsimdpp
build_and_install $srcdir $installdir capnproto
build_and_install $srcdir $installdir simd-diagonal-load
build_and_install $srcdir $installdir simd-diagonal-load-json-demo

echo LD_LIBRARY_PATH=\"$installdir/lib:\$LD_LIBRARY_PATH\" PATH=\"$installdir/bin:\$PATH\" generate-input --spec examples/example1/inputspec.json "|" LD_LIBRARY_PATH=\"$installdir/lib:\$LD_LIBRARY_PATH\" PATH=\"$installdir/bin:\$PATH\" demo --conf examples/example1/demo-options.json | jq -c '[.matrices[0].diagonals[] | [.elements[].value]][]'
