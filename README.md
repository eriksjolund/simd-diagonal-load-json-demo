# simd-diagonal-load-json-demo

Command-line tools to demonstrate the features of the C++ library [simd-diagonal-load](https://github.com/eriksjolund/simd-diagonal-load).
Although simd-diagonal-load was implemented for high performance, simd-diagonal-load-json-demo is just for demonstration purposes (not for high performance).

## The problem simd-diagonal-load tries to solve

Sometimes there is a need to iterate with a sliding diagonal [SIMD](https://en.wikipedia.org/wiki/SIMD) vector over a matrix of values. If the values can just be loaded column-wise, there
is a need to somehow shift the values into the sliding diagonal.

A naive implementation could be formulated as:

```c++
int width=1000000; // a big number
uint8_t matrix[width][16];
fill_matrix_with_interesting_values(&matrix);

for (int i=0; i < width - 16; ++i) {
  uint8_t diagonal_vector[16];
  for (int j=0; j<16; ++j) {
    diagonal_vector[j] = matrix[i+j][j];
  }
  do_something(&diagonal_vector);
}
```

https://stackoverflow.com/questions/15198011/how-to-load-a-sliding-diagonal-vector-from-data-stored-column-wise-withsse

## Quick demonstration

### Run via OCI Container

An [OCI](https://opencontainers.org/) Container of simd-diagonal-load-json-demo is
available on Dockerhub.

First define some bash aliases
```
alias generate-input="podman run --rm -i docker.io/eriksjolund/simd-diagonal-load-json-demo:latest generate-input"
alias demo="podman run --rm -i -v simd-diagonal-load-json-demo/examples:/examples:Z docker.io/eriksjolund/simd-diagonal-load-json-demo:latest demo"
alias jq="podman run --rm -i docker.io/eriksjolund/simd-diagonal-load-json-demo:latest jq"
```

(In case you want to run `docker`, just replace `podman` with `docker` in the commands above)

Clone the repository so that you have the input files for the examples available.

```
$ git clone https://github.com/eriksjolund/simd-diagonal-load-json-demo.git
```

In case you use SELINUX (e.g. Fedora, CentOS), relabel the directory _simd-diagonal-load-json-demo/examples_
so that `podman run` can bind mount and read the files

```
chcon -R -t container_file_t simd-diagonal-load-json-demo/examples
```

Generate some input with the included command-line tool __generate-input__ 

    $ cat simd-diagonal-load-json-demo/examples/example1/inputspec.json | generate-input > /tmp/input.json

With the help of the command-line tool [jq](https://stedolan.github.io/jq/) the JSON input can displayed like this

    $ cat /tmp/input.json | jq -c '[.matrices[0] | .columns[].elements][]'
    ["0","1","2","3","4","5","6","7"]
    ["8","9","10","11","12","13","14","15"]
    ["16","17","18","19","20","21","22","23"]
    ["24","25","26","27","28","29","30","31"]
    ["32","33","34","35","36","37","38","39"]
    ["40","41","42","43","44","45","46","47"]
    ["48","49","50","51","52","53","54","55"]
    ["56","57","58","59","60","61","62","63"]

The included command-line tool __demo__ performs the algortihm and prints out the result to stdout

    $ cat /tmp/input.json | demo -c /examples/example1/demo-options.json | jq -c '[.matrices[0].diagonals[] | [.elements[].value]][]' 
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
    user@ubuntu:~

# Installation

## Installation on Ubuntu 18.10


Install requirements

```
    user@ubuntu:~$ sudo apt-get install jq libqt5core5a qtbase5-dev cmake g++ qtbase5-dev ninja-build
```

To build and install into /tmp run the script

```

    user@ubuntu:~$ cd simd-diagonal-load-json-demo
    user@ubuntu:~/simd-diagonal-load-json-demo$ sh build-from-web-in-tmpdir.sh

```

The last line printed in the previous command shows the command of how to run the [examples/example1](examples/example1). Cut and paste it into the terminal and press enter

```

    user@ubuntu:~/simd-diagonal-load-json-demo$ LD_LIBRARY_PATH="/tmp/tmp.tb4tsLAGHO/lib:$LD_LIBRARY_PATH" PATH="/tmp/tmp.tb4tsLAGHO/bin:$PATH" generate-input --spec examples/example1/inputspec.json | LD_LIBRARY_PATH="/tmp/tmp.tb4tsLAGHO/lib:$LD_LIBRARY_PATH" PATH="/tmp/tmp.tb4tsLAGHO/bin:$PATH" demo --conf examples/example1/demo-options.json | jq -c '[.matrices[0].diagonals[] | [.elements[].value]][]'
    ["0",null,null,null,null,null,null,null,null,null,null,null,null,null,null,null]
    ["16","1",null,null,null,null,null,null,null,null,null,null,null,null,null,null]
    ["32","17","2",null,null,null,null,null,null,null,null,null,null,null,null,null]
    ["48","33","18","3",null,null,null,null,null,null,null,null,null,null,null,null]
    ["64","49","34","19","4",null,null,null,null,null,null,null,null,null,null,null]
    ["80","65","50","35","20","5",null,null,null,null,null,null,null,null,null,null]
    ["96","81","66","51","36","21","6",null,null,null,null,null,null,null,null,null]
    ["112","97","82","67","52","37","22","7",null,null,null,null,null,null,null,null]
    [null,"113","98","83","68","53","38","23","8",null,null,null,null,null,null,null]
    [null,null,"114","99","84","69","54","39","24","9",null,null,null,null,null,null]
    [null,null,null,"115","100","85","70","55","40","25","10",null,null,null,null,null]
    [null,null,null,null,"116","101","86","71","56","41","26","11",null,null,null,null]
    [null,null,null,null,null,"117","102","87","72","57","42","27","12",null,null,null]
    [null,null,null,null,null,null,"118","103","88","73","58","43","28","13",null,null]
    [null,null,null,null,null,null,null,"119","104","89","74","59","44","29","14",null]
    [null,null,null,null,null,null,null,null,"120","105","90","75","60","45","30","15"]
    [null,null,null,null,null,null,null,null,null,"121","106","91","76","61","46","31"]
    [null,null,null,null,null,null,null,null,null,null,"122","107","92","77","62","47"]
    [null,null,null,null,null,null,null,null,null,null,null,"123","108","93","78","63"]
    [null,null,null,null,null,null,null,null,null,null,null,null,"124","109","94","79"]
    [null,null,null,null,null,null,null,null,null,null,null,null,null,"125","110","95"]
    [null,null,null,null,null,null,null,null,null,null,null,null,null,null,"126","111"]
    [null,null,null,null,null,null,null,null,null,null,null,null,null,null,null,"127"]
    user@ubuntu:~/simd-diagonal-load-json-demo$ 


```

