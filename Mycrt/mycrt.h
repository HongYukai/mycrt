//
// Created by 12096 on 2022/11/14.
//

#ifndef MYCRT_MYCRT_H
#define MYCRT_MYCRT_H

#define EOF (-1)
#define stdin 0
#define stdout 1
#define stderr 2

int my_crt_heap_init();

int my_crt_io_init();

int open(const char* filename, const char* mode);

int read(int fd, void* buffer, unsigned size);

int write (int fd, void* buffer, unsigned size);

int close(int fd);

int seek(int fd, int offset, int mode);

int fputc(char c, int fd);

int fputs(const char* str, int fd);

char* itoa(int n, char* str, int radix);

int strcmp(const char* src, const char* dst);

char* strcpy(char* dest, char* src);

unsigned strlen(const char* str);



#endif //MYCRT_MYCRT_H
