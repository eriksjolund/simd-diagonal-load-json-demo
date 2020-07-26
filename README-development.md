## Development of simd-diagonal-load-json-demo

### Build a container with the required build tools 

If you want to modify the source code of simd-diagonal-load-json-demo and build it, the easiest
way to build it, is by using the container image __develop__ (defined by _Dockerfile.develop_).

First clone the git repo

```
cd ~
git clone https://github.com/eriksjolund/simd-diagonal-load-json-demo.git
```

Modify a source code file, for instance _demo.cc_

```
gnome-edit simd-diagonal-load-json-demo/src/cmd/demo/demo.cc
```

Build the container __image__

```
podman build -t develop -f simd-diagonal-load-json-demo/Dockerfile.develop
```

It is now available as _localhost/develop_.

Create some directories and set some variables

```
builddir=`mktemp -d`
installdir=`mktemp -d`
dependencies_sourcedir=~/dependencies_sourcedir
mkdir $dependencies_sourcedir
```

Build simd-diagonal-load-json-demo and its requirements

```
bash simd-diagonal-load-json-demo/build-locally-with-podman.bash ~/simd-diagonal-load-json-demo $dependencies_sourcedir $builddir $installdir
```

## Run the new build with example input data

The last lines printed to stdout in the previous command defines some aliases:

* generate-input
* demo
* jq
* demorun

Copy-paste those lines into the bash shell.

`demorun` is a work-around until podman 2.1.0 has been released. (Assuming that podman release will have support for `podman run --preserved-fds`, see https://github.com/containers/podman/issues/6458#issuecomment-663868176).
After running `demorun` once, the alias `demo` will start to work.
