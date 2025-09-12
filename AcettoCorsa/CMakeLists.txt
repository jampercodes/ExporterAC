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
    message(STATUS "Building for x86")
    set(target_architecture "x86")
else()
    message(STATUS "Building for x64")
    set(target_architecture "x64")
endif()

if(CMAKE_SIZEOF_VOID_P EQUAL 4)
    set(FBXSDK_LIB "${CMAKE_SOURCE_DIR}/lib/fbx/x86/libfbxsdk.lib")
else()
    set(FBXSDK_LIB "${CMAKE_SOURCE_DIR}/lib/fbx/x64/libfbxsdk.lib")
endif()



add_library(${BEASE_NAME} ${LIB_TYPE} ${src_files})


link_directories(${BEASE_NAME} ${FBXSDK_LIB})

target_include_directories(${BEASE_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/Include)

target_include_directories(${BEASE_NAME} PRIVATE lib_include)

target_compile_definitions(${BEASE_NAME} PRIVATE FBXSDK_ENV_WIN FBXSDK_COMPILER_MSC FBXSDK_NEW_API)


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