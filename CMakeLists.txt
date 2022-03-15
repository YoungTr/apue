cmake_minimum_required(VERSION 3.21)
project(apue C)

set(CMAKE_C_STANDARD 99)

add_executable(apue main.c)
add_executable(seek1 src/fileio/seek1.c)
add_executable(seek2 src/fileio/seek2.c)
add_executable(dup2 src/fileio/dup2.c)
add_executable(lstat1 src/filedir/lstat.c)

add_executable(atexit1 src/process/atexit1.c)
add_executable(setjmp1 src/process/setjmp1.c)
add_executable(longjmp1 src/process/longjmp1.c)
