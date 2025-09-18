cmake_minimum_required(VERSION 3.15)
project(AcettoCorsa LANGUAGES CXX)

set(BASE_NAME AcettoCorsa)

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




add_library(${BASE_NAME} ${LIB_TYPE} ${src_files})


target_include_directories(${BASE_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/Include)

target_include_directories(${BASE_NAME} PRIVATE lib_include)

#target_compile_definitions(${BASE_NAME} PRIVATE FBXSDK_ENV_WIN FBXSDK_COMPILER_MSC FBXSDK_NEW_API)

target_compile_definitions(${BASE_NAME} PRIVATE
    UNICODE
    _UNICODE
    _WINDOWS
    _USRDLL
    AUTOMATIONEXPORTEXAMPLE_EXPORTS
    PROJECT_FILENAME=L"${BASE_NAME}${target_architecture}.dll"
)


set_target_properties(${BASE_NAME} PROPERTIES
    OUTPUT_NAME "${BASE_NAME}${target_architecture}"
)

# Add common definitions, including the required Windows version macro
target_compile_definitions(${BASE_NAME} PRIVATE
    _WIN32_WINNT=0x0A00 # Required for SDKDDKVer.h
    FBXSDK_ENV_WIN
    FBXSDK_NEW_API
    UNICODE
    _UNICODE
    _WINDOWS
    _USRDLL
    AUTOMATIONEXPORTEXAMPLE_EXPORTS
)