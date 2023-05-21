cmake_minimum_required(VERSION 3.15)

project(PakFilesystemHeaders VERSION 0.1)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_library(PakFilesystemHeaders INTERFACE)
target_include_directories(PakFilesystemHeaders INTERFACE .)