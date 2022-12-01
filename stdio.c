//
// Created by 12096 on 2022/12/1.
//
#include "mycrt.h"

int my_crt_io_init() {
    return 1;
}

static int open(const char* pathname, int flags, int mode) {
    int fd = 0;
    asm("movl $5, %%eax \n\t"
        "movl %1, %%ebx \n\t"
        "movl %2, %%ecx \n\t"
        "movl %3, %%edx \n\t"
        "int $0x80 \n\t"
        "movl %%eax, %0 \n\t":
        "=m"(fd):
        "m"(pathname),"m"(flags),"m"(mode)) ;
    return fd;
}

static int read(int fd, void* buffer, unsigned size) {
    int ret = 0;
    asm("movl $3, %%eax \n\t"   //! look up the system-call number: cat /usr/include/asm/unistd_32.h
        "movl %1, %%ebx \n\t"
        "movl %2, %%ecx \n\t"
        "movl %3, %%edx \n\t"
        "int $0x80 \n\t"
        "movl %%eax, %0 \n\t":
    "=m"(ret):
    "m"(fd),"m"(buffer),"m"(size)) ;
    return ret;
}

static int write (int fd, void* buffer, unsigned size) {
    int ret = 0;
    asm("movl $4, %%eax \n\t"
        "movl %1, %%ebx \n\t"
        "movl %2, %%ecx \n\t"
        "movl %3, %%edx \n\t"
        "movl %%eax, %0 \n\t":
        "=m"(ret):
        "m"(fd),"m"(buffer),"m"(size));
    return ret;
}

static int close(int fd) {
    int ret = 0;
    asm("movl $6, %%eax \n\t"
        "movl %1, %%ebx \n\t"
        "movl %%eax, %0 \n\t":
    "=m"(ret):
    "m"(fd));
    return ret;
}

static int seek(int fd, int offset, int mode) {
    int ret = 0;
    asm("movl $19, %%eax \n\t"
        "movl %1, %%ebx \n\t"
        "movl %2, %%ecx \n\t"
        "movl %3, %%edx \n\t"
        "movl %%eax, %0 \n\t":
    "=m"(ret):
    "m"(fd),"m"(buffer),"m"(size));
    return ret;
}