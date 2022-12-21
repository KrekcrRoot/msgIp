cmake_minimum_required(VERSION 3.24)
project(msgip)




include_directories("D:\\langs\\boost_1_81_0")
include_directories(headers)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
set(THREADS_PREFER_PTHREAD_FLAG TRUE)
find_package(Threads REQUIRED)

link_libraries(ws2_32 wsock32)


add_executable(msgip main.cpp Imply.cpp)
target_link_libraries(msgip -static-libgcc -static-libstdc++ -lwsock32 -lws2_32 Threads::Threads)