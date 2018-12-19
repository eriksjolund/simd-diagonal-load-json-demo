cmake_minimum_required(VERSION 3.11.4)
project(check_template_parameters 
    LANGUAGES
        CXX
)
find_package(libsimdpp REQUIRED)
find_package(simd-diagonal-load REQUIRED)

add_executable(compilationtest check_template_parameters.cc)
target_link_libraries(compilationtest PRIVATE simd-diagonal-load::algorithm)

foreach(i NUM_LOADS
          NUM_BITS_PER_ELEMENT
	  SIMDVECTOR_BITLENGTH
	  NUM_VERTICAL_SUBDIVISIONS
	  NUM_VERTICAL_MIXING)
  target_compile_definitions(compilationtest PRIVATE "${i}=${${i}}")
endforeach()

set_target_properties(compilationtest PROPERTIES CXX_STANDARD 17
                                             CXX_STANDARD_REQUIRED ON)
