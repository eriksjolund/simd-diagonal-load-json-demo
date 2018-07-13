project(check-valid-numbers)

add_library(${PROJECT_NAME} SHARED)
add_library(simd-diagonal-load-json-demo::${PROJECT_NAME} ALIAS ${PROJECT_NAME})
target_include_directories(${PROJECT_NAME}
                           PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
                                  $<INSTALL_INTERFACE:include>)

target_sources(${PROJECT_NAME} PRIVATE check_valid_input_helper_funcs.cc)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)
install(TARGETS ${PROJECT_NAME}
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/simd-diagonal-load-json-demo)
