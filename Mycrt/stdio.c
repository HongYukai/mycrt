//
// Created by 12096 on 2022/12/1.
//
#include "mycrt.h"

int my_crt_io_init() {
    return 1;
}

int open(const char* filename, const char* mode) {
    int fd = -1;
    int flags = 0;
    int access = 00700; //! the priority of file
#define O_RDONLY 00
#define O_WRONLY 01
#define O_RDWR 02
#define O_CREAT 0100
#define O_TRUNC 01000
#define O_APPEND 02000
    if (strcmp(mode, "w") == 0) {
        flags |= O_WRONLY | O_CREAT | O_TRUNC;
    }
    if (strcmp(mode, "w+") == 0) {
        flags |= O_RDWR | O_CREAT | O_TRUNC;
    }
    if (strcmp(mode, "r") == 0) {
        flags |= O_RDONLY;
    }
    if (strcmp(mode, "r+") == 0) {
        flags |= O_RDWR | O_CREAT;
    }
    asm("movl $5, %%eax \n\t"
        "movl %1, %%ebx \n\t"
        "movl %2, %%ecx \n\t"
        "movl %3, %%edx \n\t"
        "int $0x80 \n\t"
        "movl %%eax, %0 \n\t":
    "=m"(fd):
    "m"(filename),"m"(flags),"m"(mode)) ;
    return fd;
}

int read(int fd, void* buffer, unsigned size) {
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

int write (int fd, void* buffer, unsigned size) {
    int ret = 0;
    asm("movl $4, %%eax \n\t"
        "movl %1, %%ebx \n\t"
        "movl %2, %%ecx \n\t"
        "movl %3, %%edx \n\t"
        "int $0x80 \n\t"
        "movl %%eax, %0 \n\t":
        "=m"(ret):
        "m"(fd),"m"(buffer),"m"(size));
    return ret;
}

int close(int fd) {
    int ret = 0;
    asm("movl $6, %%eax \n\t"
        "movl %1, %%ebx \n\t"
        "int $0x80 \n\t"
        "movl %%eax, %0 \n\t":
    "=m"(ret):
    "m"(fd));
    return ret;
}

int seek(int fd, int offset, int mode) {
    int ret = 0;
    asm("movl $19, %%eax \n\t"
        "movl %1, %%ebx \n\t"
        "movl %2, %%ecx \n\t"
        "movl %3, %%edx \n\t"
        "int $0x80 \n\t"
        "movl %%eax, %0 \n\t":
    "=m"(ret):
    "m"(fd),"m"(offset),"m"(mode));
    return ret;
}

int fputc(char c, int fd) {
    if (write(fd, &c, 1) == 1) {
        return 1;
    }
    else {
        return EOF;
    }
}

int fputs(const char* str, int fd) {
    unsigned len = strlen(str);
    if (write(fd, (void*)str, len) == len) {
        return len;
    }
    else {
        return EOF;
    }
}








