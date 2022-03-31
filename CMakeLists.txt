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

# 进程控制
add_executable(fork1 src/processcontrol/fork1.c)
add_executable(waitpid1 src/processcontrol/waitpid1.c)
add_executable(echoall src/processcontrol/echoall.c)
add_executable(execle1 src/processcontrol/execle1.c)

# 信号
add_executable(signal1 src/signal/signal1.c)
add_executable(signal2 src/signal/signal2.c)
add_executable(sigsetjmp1 src/signal/sigsetjmp1.c)

# 线程
add_executable(pthread_create1 src/thread/thread_create1.c)
add_executable(pthread_join1 src/thread/thread_join1.c)

# ipc
add_executable(ipc1 src/ipc/pipe1.c)
add_executable(ipc2 src/ipc/pipe2.c)
add_executable(fifowrite src/ipc/fifowrite2.c)
add_executable(fiforead src/ipc/fiforead.c)

