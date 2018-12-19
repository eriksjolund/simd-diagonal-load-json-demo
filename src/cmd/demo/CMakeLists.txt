project(demo)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
find_package(Qt5 COMPONENTS Core REQUIRED)
find_package(simd-diagonal-load REQUIRED)

add_my_program(${PROJECT_NAME})
target_link_libraries(${PROJECT_NAME} PRIVATE simd-diagonal-load-json-demo::defines-from-cmake-variables)
target_link_libraries(${PROJECT_NAME} PRIVATE simd-diagonal-load-json-demo::capnproto-helper-funcs)
target_link_libraries(${PROJECT_NAME} PRIVATE simd-diagonal-load-json-demo::input-matrices)
target_link_libraries(${PROJECT_NAME} PRIVATE simd-diagonal-load-json-demo::demo-plugin-interface)
target_link_libraries(${PROJECT_NAME} PRIVATE simd-diagonal-load-json-demo::demo-pluginloader)
target_link_libraries(${PROJECT_NAME} PRIVATE simd-diagonal-load-json-demo::demo-run-options)
target_link_libraries(${PROJECT_NAME} PRIVATE simd-diagonal-load::array-helper)
target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Core)

file(TO_NATIVE_PATH "${CMAKE_INSTALL_PREFIX}/${plugin_install_dir}" native_path)
target_compile_definitions(${PROJECT_NAME} PRIVATE "PLUGIN_INSTALL_DIR=\"${native_path}\"")
