  
# Set the minimum version of CMake that can be used
# To find the cmake version run
# $ cmake --version
cmake_minimum_required(VERSION 3.5)

# Set the project name
project (echo)

# Create a sources variable with a link to all cpp files to compile
set(SOURCES
    ./echo.cpp
)

# Add an executable with the above sources
add_executable(echo ${SOURCES})

# Set the directories that should be included in the build command for this target
# when running g++ these will be included as -I/directory/path/
target_include_directories(echo
    PRIVATE 
    /home/aa/Desktop/chenshuo_source/build/release-install-cpp11/include
)

#link_directories(/home/aa/Desktop/chenshuo_source/build/release-install-cpp11/lib)
add_library(muduo_base STATIC IMPORTED)
add_library(muduo_net STATIC IMPORTED)
set_property(TARGET muduo_net PROPERTY IMPORTED_LOCATION /home/aa/Desktop/chenshuo_source/build/release-install-cpp11/lib/libmuduo_net.a)
set_property(TARGET muduo_base PROPERTY IMPORTED_LOCATION /home/aa/Desktop/chenshuo_source/build/release-install-cpp11/lib/libmuduo_base.a)

#link muduo_net first and then muduo_base, otherwise will link failed
target_link_libraries(echo muduo_net muduo_base pthread)
