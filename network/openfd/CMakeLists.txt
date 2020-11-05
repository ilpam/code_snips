cmake_minimum_required (VERSION 2.8)
project (echo)

add_executable(client client.c misc.c ./lib/rio.c ./lib/openfd.c ./lib/error_report.c)
add_executable(server server.c misc.c ./lib/rio.c ./lib/openfd.c ./lib/error_report.c)