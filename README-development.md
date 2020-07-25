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



The last line printed in the previous command shows the command of how to run the [examples/example1](examples/example1). Cut and paste it into the terminal and press enter

```
user@fedora:~/simd-diagonal-load-json-demo$ LD_LIBRARY_PATH="/tmp/tmp.tb4tsLAGHO/lib:$LD_LIBRARY_PATH" PATH="/tmp/tmp.tb4tsLAGHO/bin:$PATH" generate-input --spec examples/example1/inputspec.json | LD_LIBRARY_PATH="/tmp/tmp.tb4tsLAGHO/lib:$LD_LIBRARY_PATH" PATH="/tmp/tmp.tb4tsLAGHO/bin:$PATH" demo 3< examples/example1/demo-options.json | jq -c '[.matrices[0].diagonals[] | [.elements[].value]][]'
["0",null,null,null,null,null,null,null]
["8","1",null,null,null,null,null,null]
["16","9","2",null,null,null,null,null]
["24","17","10","3",null,null,null,null]
["32","25","18","11","4",null,null,null]
["40","33","26","19","12","5",null,null]
["48","41","34","27","20","13","6",null]
["56","49","42","35","28","21","14","7"]
[null,"57","50","43","36","29","22","15"]
[null,null,"58","51","44","37","30","23"]
[null,null,null,"59","52","45","38","31"]
[null,null,null,null,"60","53","46","39"]
[null,null,null,null,null,"61","54","47"]
[null,null,null,null,null,null,"62","55"]
[null,null,null,null,null,null,null,"63"]
user@fedora:~/simd-diagonal-load-json-demo$ 


```
