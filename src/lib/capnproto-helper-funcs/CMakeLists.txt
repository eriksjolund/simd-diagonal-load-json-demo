project(capnproto-helper-funcs)

find_package(CapnProto REQUIRED)
add_library(${PROJECT_NAME} SHARED)
add_library(simd-diagonal-load-json-demo::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME} 
   INTERFACE 
  $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include> 
 )

target_include_directories(${PROJECT_NAME} 
   PRIVATE
  $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
> 
 )

target_sources(${PROJECT_NAME} PRIVATE parsejsonfile.cc)

add_subdirectory(include/simd-diagonal-load-json-demo/capnproto-helper-funcs)

target_link_libraries(${PROJECT_NAME} PUBLIC CapnProto::capnp CapnProto::capnp-json)

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)
install(TARGETS ${PROJECT_NAME} DESTINATION ${CMAKE_INSTALL_LIBDIR}/simd-diagonal-load-json-demo)

