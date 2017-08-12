cmake_minimum_required(VERSION 3.4)

project(logging_lib)

message("-- Create logging_lib")
add_library(logging_lib ${CMAKE_CURRENT_SOURCE_DIR}/easylogging++.cc)
