cmake_minimum_required (VERSION 2.8)
project (echo)

#find_package(Threads)

#aux_source_directory(. DIR_SRCS)

#add_executable(${PROJECT_NAME} ${DIR_SRCS})
add_executable(client client.c)
add_executable(server server.c)
#target_link_libraries(Demo ${CMAKE_THREAD_LIBS_INIT})