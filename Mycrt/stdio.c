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
    "m"(filename),"m"(flags),"m"(access)) ;
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

void* va_arg(char** s, int size) {
    char* mark = *s;
    *s = *s + size;
    return (void*)mark;
}

unsigned vfprintf(int fd, const char* format, va_list arglist) {
    int translating = 0;
    unsigned ret = 0;
    const char* p = 0;
    for (p = format; *p != '\0'; ++p) {
        switch (*p) {
            case '%':
                if (!translating) {
                    translating = 1;
                }
                else {
                    if (fputc('%', fd) < 0) {
                        return EOF;
                    }
                    ++ret;
                    translating = 0;
                }
                break;
            case 'd':
                if (translating) {
                    char buf[16];
                    translating = 0;
                    itoa(*(int*)va_arg(&arglist, sizeof(int)), buf, 10);
                    if (fputs(buf, fd) < 0) {
                        return EOF;
                    }
                    ret += strlen(buf);
                }
                else if (fputc('d', fd) < 0) {
                    return EOF;
                }
                else ++ret;
                break;
            case 's':
                if (translating) {
                    translating = 0;
                    char* s = *(char**)va_arg(&arglist, sizeof(char*));
                    if (fputs(s, fd) < 0) {
                        return EOF;
                    }
                    ret += strlen(s);
                }
                else if (fputc('s', fd) < 0) {
                    return EOF;
                }
                else ++ret;
                break;
            default:
                if (translating) {
                    translating = 0;
                }
                if (fputc(*p, fd) < 0) {
                    return EOF;
                }
                else ++ret;
                break;
        }
    }
    return ret;
}

unsigned printf(const char* format, ...) {
    va_list arglist = (va_list)((va_list)&format + sizeof(format));
    return vfprintf(stdout, format, arglist);
}

unsigned fprintf(int fd, const char* format, ...) {
    va_list arglist = (va_list)((va_list)&format + sizeof(format));
    return vfprintf(fd, format, arglist);
}








