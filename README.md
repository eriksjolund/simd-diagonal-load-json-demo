# simd-diagonal-load-json-demo

Command-line tools to demonstrate the features of the C++ library [simd-diagonal-load](https://github.com/eriksjolund/simd-diagonal-load).
Although simd-diagonal-load was implemented for high performance, simd-diagonal-load-json-demo is just for demonstration purposes (not for high performance).

# The problem simd-diagonal-load tries to solve

Sometimes there is a need to iterate with a sliding diagonal SIMD vector over a matrix of values. If the values can just be loaded column-wise, there
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

# Quick demonstration

Generate some input with the included command-line tool __generate-input__ 

    user@ubuntu:~$ generate-input 1 int32_t 256 8 > /tmp/input.json

With the help of the command-line tool [jq](https://stedolan.github.io/jq/) the JSON input can displayed like this

    user@ubuntu:~$ cat /tmp/input.json | jq -c '[.matrices[0] | .columns[].elements][]'
    ["0","1","2","3","4","5","6","7"]
    ["8","9","10","11","12","13","14","15"]
    ["16","17","18","19","20","21","22","23"]
    ["24","25","26","27","28","29","30","31"]
    ["32","33","34","35","36","37","38","39"]
    ["40","41","42","43","44","45","46","47"]
    ["48","49","50","51","52","53","54","55"]
    ["56","57","58","59","60","61","62","63"]


The included command-line tool __demo__ performs the algortihm and prints out the result to stdout

    user@ubuntu:~$ cat /tmp/input.json | demo 1 1 | jq -c '[.result.matrices[0].diagonals[] | [.elements[].element]][]' 
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
    esjolund@laptop:~

# Installation

First install the requirements.

On Ubuntu the commands are:

```
sudo apt-get install protobuf-c-compiler
sudo apt-get install libprotobuf-dev
sudo apt-get install jq
sudo apt-get install qtbase5-dev
```

After that perfom a standard CMake installation. There are some CMake variables that can be adjusted:

* NUM_LOADS_MINIMUM
* NUM_LOADS_MAXIMUM
* NUM_MATRICES_MINIMUM
* NUM_MATRICES_MAXIMUM
* NUM_VERTICAL_MIXING_MINIMUM
* NUM_VERTICAL_MIXING_MAXIMUM
* NUM_VERTICAL_SUBDIVISIONS_MINIMUM
* NUM_VERTICAL_SUBDIVISIONS_MAXIMUM
* SIMDVECTOR_BITLENGTH_MINIMUM
* SIMDVECTOR_BITLENGTH_MAXIMUM
* MATRIX_WIDTH_MINIMUM
* MATRIX_WIDTH_MAXIMUM
* INTEGERTYPES
