cmake_minimum_required(VERSION 4.3)
project(CppConcurrencyInAction)

set(CMAKE_CXX_STANDARD 20)
add_compile_options(-O0  -fno-inline -fno-tree-vectorize -fno-builtin -fno-omit-frame-pointer -fno-optimize-sibling-calls -fno-unroll-loops -fno-strict-aliasing -fno-elide-constructors --std=c++14 -save-temps=obj)
file(GLOB_RECURSE HEADER_FILES "${CMAKE_SOURCE_DIR}/*.h")

add_executable(CppConcurrencyInAction main.cpp ${HEADER_FILES}
        MyLevelMutex.h
        CallOnce.h)