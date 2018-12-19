find_package(CapnProto REQUIRED)

list(APPEND CAPNPC_IMPORT_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/../../../../input-spec/include)

#set(CAPNPC_SRC_PREFIX ${CMAKE_CURRENT_SOURCE_DIR}/../../../..)
capnp_generate_cpp(CAPNP_SRCS CAPNP_HDRS demo-run-options.capnp)

add_library(${PROJECT_NAME} SHARED)
target_sources(${PROJECT_NAME} PRIVATE ${CAPNP_SRCS})

#target_link_libraries(${PROJECT_NAME} PRIVATE CapnProto::capnp-rpc)

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_BINARY_DIR})

target_link_libraries(${PROJECT_NAME} PRIVATE input-spec)

target_include_directories(${PROJECT_NAME} 
   INTERFACE 
  $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include>
  $<INSTALL_INTERFACE:include> 
 )

add_library(simd-diagonal-load-json-demo::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

target_link_libraries(${PROJECT_NAME} PUBLIC CapnProto::capnp CapnProto::capnp-json)
#set_property(TARGET ${PROJECT_NAME} PROPERTY POSITION_INDEPENDENT_CODE ON)
#set_target_properties(${PROJECT_NAME} PROPERTIES POSITION_INDEPENDENT_CODE ON)

install(TARGETS ${PROJECT_NAME} DESTINATION ${CMAKE_INSTALL_LIBDIR}/simd-diagonal-load-json-demo)

