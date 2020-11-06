
This project is from csapp.
The two openfd function can be used in other projects, they are much better than directly using ip address & port num in system call.

The function of this server is the same as that one from ../echo/server.c:
    catch everything from client and return data which is upper case

build step:
    1. mkdir ./build
    2. cd build
    3. cmake ..
    4. make

execute:
    1. start server : ./server [port-num]
    2. start client : ./client [host] [port-num]
    3. enjoy yourself
