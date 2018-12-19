#!/bin/sh

# The clang-format-7 command makes use of the configuration file 
# simd-diagonal-load/src/.clang-format

files="cmd/demo/demo.cc
cmd/generate-input/generate-input.cc
cmd/generate-input/parsed_options.h
cmd/generate-input/print_generated_input.cc
cmd/generate-input/print_generated_input.h
cmd/generate-input/try_to_parse_argv.cc
cmd/generate-input/try_to_parse_argv.h
lib/capnproto-helper-funcs/include/simd-diagonal-load-json-demo/capnproto-helper-funcs/parsejsonfile.h
lib/capnproto-helper-funcs/include/simd-diagonal-load-json-demo/capnproto-helper-funcs/print_json.h
lib/capnproto-helper-funcs/parsejsonfile.cc
lib/check-valid-numbers/check_valid_input_helper_funcs.cc
lib/check-valid-numbers/include/simd-diagonal-load-json-demo/check-valid-numbers/check_valid_input_helper_funcs.h
lib/demo-plugin/check-template-parameters/check_template_parameters.cc
lib/demo-plugin/demo_plugin.cc
lib/demo-plugin/demo_plugin.h
lib/demo-plugin-interface/include/simd-diagonal-load-json-demo/demo-plugin-interface/demo_plugin_interface.h
lib/demo-plugin/json_matrix.h
lib/demo-pluginloader/demo_pluginloader.cc
lib/demo-pluginloader/include/simd-diagonal-load-json-demo/demo-pluginloader/demo_pluginloader.h
lib/demo-plugin/print_result.h
lib/demo-plugin/result.h"

for i in $files; do 
  if [ ! -w $i ]; then
     echo "file $i does not exist"
     exit 1
  fi
  clang-format-7 -i $i
done
