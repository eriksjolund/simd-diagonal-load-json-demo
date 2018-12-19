project(demo-pluginloader)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
find_package(libsimdpp REQUIRED)
find_package(simd-diagonal-load REQUIRED)
find_package(Qt5 COMPONENTS Core REQUIRED)

add_library(${PROJECT_NAME} SHARED)


target_link_libraries(${PROJECT_NAME} PRIVATE simd-diagonal-load-json-demo::demo-plugin-interface)
target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Core)

add_library(simd-diagonal-load-json-demo::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

target_sources(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/demo_pluginloader.cc)

target_include_directories(${PROJECT_NAME}
   PRIVATE 
  $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include/simd-diagonal-load-json-demo/demo-pluginloader>
   INTERFACE 
  $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
  $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
 )

install(TARGETS ${PROJECT_NAME} DESTINATION ${CMAKE_INSTALL_LIBDIR}/simd-diagonal-load-json-demo)
