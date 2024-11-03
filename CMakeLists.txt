cmake_minimum_required(VERSION 3.13 FATAL_ERROR)

set(PROJECT_NAME "fatum")

project(${PROJECT_NAME} CXX)

set(CMAKE_CXX_STANDARD 20)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)

file(GLOB SOURCES "src/*.cpp")

add_library(${PROJECT_NAME} STATIC ${SOURCES} "include/fatum/")

target_compile_definitions(${PROJECT_NAME} PUBLIC _LOGGER GLFW_INCLUDE_NONE)

add_subdirectory(external/glfw)
add_subdirectory(external/glad)

target_link_libraries(${PROJECT_NAME} PUBLIC glfw glad)

set(ZRC_PATH "${CMAKE_CURRENT_SOURCE_DIR}/external/zrc")
#message("zrc_path: ${ZRC_PATH}")
add_custom_command(TARGET ${PROJECT_NAME} 
                   POST_BUILD
                   COMMAND "${ZRC_PATH}/FATUM-resource_maker.exe" "load(${ZRC_PATH}/loadpref.zrp)" "compile(${CMAKE_BINARY_DIR}/resources.zrc)" 
                )
                  

target_include_directories(${PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/external/glfw/include
    ${CMAKE_CURRENT_SOURCE_DIR}/external/glad/include )
