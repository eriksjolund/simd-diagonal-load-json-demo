#!/bin/bash

set -o errexit
set -o pipefail
set -o nounset

if [ $# -eq 4 ]; then
  simd_diagonal_load_json_demo_sourcedir="$1"
  dependencies_sourcedir="$2"
  builddir="$3" 
  installdir="$4"
else
  echo Error: Wrong number of arguments
  exit 1
fi

podman_run() {
  podman run \
    --rm --net=none \
    --security-opt label=disable \
    --env PATH="$installdir/bin:/root/.local/bin:/root/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin" \
    --env LD_LIBRARY_PATH="$installdir/lib:$installdir/lib64" \
    --mount=type=bind,src=$dependencies_sourcedir,dst=$dependencies_sourcedir,ro=true \
    --mount=type=bind,src=$simd_diagonal_load_json_demo_sourcedir,dst=$simd_diagonal_load_json_demo_sourcedir,ro=true \
    --mount=type=bind,src=$builddir,dst=$builddir,rw=true \
    --mount=type=bind,src=$installdir,dst=$installdir,rw=true \
    localhost/develop \
    $@
}

build_and_install() {
     podman_run cmake -G Ninja "-DCMAKE_INSTALL_PREFIX=$installdir" "-DCMAKE_PREFIX_PATH=$installdir" -DBUILD_SHARED_LIBS=on -B $builddir/$1 -S "$2"
     podman_run cmake --build $builddir/$1 --target install
}

if [ ! -f $dependencies_sourcedir/dependencies_have_been_downloaded ]; then
  git -C $dependencies_sourcedir clone https://github.com/eriksjolund/simd-diagonal-load.git
  git -C $dependencies_sourcedir/simd-diagonal-load checkout rearrange
  git -C $dependencies_sourcedir clone https://github.com/eriksjolund/simd-diagonal-load-json-demo.git
  git -C $dependencies_sourcedir clone https://github.com/eriksjolund/libsimdpp.git
  git -C $dependencies_sourcedir/libsimdpp checkout modernize_cmake_support 
  git -C $dependencies_sourcedir clone https://github.com/capnproto/capnproto.git
  git -C $dependencies_sourcedir/capnproto checkout v0.8.0
  touch $dependencies_sourcedir/dependencies_have_been_downloaded
fi

build_and_install simd-compile-options "$dependencies_sourcedir/libsimdpp/cmake/simd-compile-options"
build_and_install libsimdpp "$dependencies_sourcedir/libsimdpp"
build_and_install capnproto "$dependencies_sourcedir/capnproto"
build_and_install simd-diagonal-load "$dependencies_sourcedir/simd-diagonal-load"
build_and_install simd-diagonal-load-json-demo "$simd_diagonal_load_json_demo_sourcedir"

echo "Source these lines to get aliases for generate-input, dem and jq

alias podman_run_alias=\"podman run -i --network=none --security-opt label=disable \
                --env PATH=$installdir/bin:/root/.local/bin:/root/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin \
                --env LD_LIBRARY_PATH=$installdir/lib:$installdir/lib64 \
                --mount=type=bind,src=$dependencies_sourcedir,dst=$dependencies_sourcedir,ro=true \
                --mount=type=bind,src=$simd_diagonal_load_json_demo_sourcedir,dst=$simd_diagonal_load_json_demo_sourcedir,ro=true \
                --mount=type=bind,src=$builddir,dst=$builddir,ro=true \
                --mount=type=bind,src=$installdir,dst=$installdir,ro=true\"

alias generate-input=\"podman_run_alias localhost/develop generate-input\"
alias demo=\"podman exec -i --preserve-fds=1 democtr demo\"
alias jq=\"podman_run_alias localhost/develop jq\"
alias demorun=\"podman_run_alias -d --name democtr localhost/develop sleep 100000\"
"
