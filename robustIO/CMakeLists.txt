#cmake_minimum_required(VERSION 3.5)
project(rio)
############################################################
# Create an executable
############################################################
# Add an executable with the above sources
add_executable(rio_test
    test.c rio.c
)