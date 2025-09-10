cmake_minimum_required(VERSION 3.15)
project(AcettoCorsa LANGUAGES CXX)

set(BEASE_NAME AcettoCorsa)

# dose this work?
#file(GLOB header_files include/*.h)
#file(GLOB Lib_header lib_include/*.h)

file(GLOB src_files src/*.cpp)

if(NOT DEFINED LIB_TYPE)
    set(LIB_TYPE SHARED)
endif()

message(STATUS "Target pointer size: ${CMAKE_SIZEOF_VOID_P}")
if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    message(STATUS "Building for x64")
    set(target_architecture "x64")
elseif(CMAKE_SIZEOF_VOID_P EQUAL 4)
    message(STATUS "Building for x86")
    set(target_architecture "x86")
endif()

add_library(${BEASE_NAME} ${LIB_TYPE} ${src_files})

target_include_directories(${BEASE_NAME} PRIVATE include)

target_include_directories(${BEASE_NAME} PRIVATE lib_include)

target_link_libraries(${BEASE_NAME} PRIVATE lib/fbx/${target_architecture}/*)

target_compile_definitions(${BEASE_NAME} PRIVATE
    UNICODE
    _UNICODE
    _WINDOWS
    _USRDLL
    AUTOMATIONEXPORTEXAMPLE_EXPORTS
    PROJECT_FILENAME=L"${BEASE_NAME}${target_architecture}.dll"
)


set_target_properties(${BEASE_NAME} PROPERTIES
    OUTPUT_NAME "${BEASE_NAME}${target_architecture}"
)