#!/bin/sh

# The clang-format-6.0 command makes use of the configuration file 
# simd-diagonal-load/src/.clang-format

files="./check-valid-numbers/check_valid_input_helper_funcs.cc
./check-valid-numbers/include/simd-diagonal-load-json-demo/check-valid-numbers/check_valid_input_helper_funcs.h
./demo/demo.cc
./demo-plugin/check-template-parameters/check_template_parameters.cc
./demo-plugin/demo_plugin.cc
./demo-plugin/demo_plugin.h
./demo-plugin-interface/include/simd-diagonal-load-json-demo/demo-plugin-interface/demo_plugin_interface.h
./demo-plugin/json_matrix.h
./demo-pluginloader/demo_pluginloader.cc
./demo-pluginloader/include/simd-diagonal-load-json-demo/demo-pluginloader/demo_pluginloader.h
./generate-input/generate-input.cc
./generate-input/print_generated_input.cc
./generate-input/print_generated_input.h
./generate-input/print_generated_input_template.h
./protobuf-helper-funcs/include/simd-diagonal-load-json-demo/protobuf-helper-funcs/json_input_from_stdin.h
./protobuf-helper-funcs/include/simd-diagonal-load-json-demo/protobuf-helper-funcs/print_json.h
./protobuf-helper-funcs/print_json.cc"

for i in $files; do 
  if [ ! -w $i ]; then
     echo "file $i does not exist"
     exit 1
  fi
  clang-format-6.0 -i $i
done
