find_package(CapnProto REQUIRED)

#set(CAPNPC_SRC_PREFIX ${CMAKE_CURRENT_SOURCE_DIR}/../../../..)
capnp_generate_cpp(CAPNP_SRCS CAPNP_HDRS input-spec.capnp)

add_library(${PROJECT_NAME} SHARED)
add_library(simd-diagonal-load-json-demo::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

target_sources(${PROJECT_NAME} PRIVATE ${CAPNP_SRCS})

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_BINARY_DIR})

target_include_directories(${PROJECT_NAME} 
   INTERFACE 
  $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include>
  $<INSTALL_INTERFACE:include> 
 )



target_link_libraries(${PROJECT_NAME} PUBLIC CapnProto::capnp CapnProto::capnp-json)

install(TARGETS ${PROJECT_NAME} DESTINATION ${CMAKE_INSTALL_LIBDIR}/simd-diagonal-load-json-demo)

