//
// Created by 12096 on 2022/11/14.
//

#ifndef MYCRT_MYCRT_H
#define MYCRT_MYCRT_H

#ifdef __cplusplus
extern "C" {
#endif

#define EOF (-1)
#define stdin 0
#define stdout 1
#define stderr 2

typedef void (*cxa_func_t)(void*);
typedef void (*atexit_func_t)(void);

int my_crt_heap_init();

void* malloc(unsigned long long);

void free(void*);

int my_crt_io_init();

void do_global_ctors();

void my_crt_call_exit_routine();

int open(const char *filename, const char *mode);

int read(int fd, void *buffer, unsigned size);

int write(int fd, void *buffer, unsigned size);

int close(int fd);

int seek(int fd, int offset, int mode);

int fputc(char c, int fd);

int fputs(const char *str, int fd);

#define va_list char*

void* va_arg(char** s, int size);

unsigned vfprintf(int fd, const char *format, va_list arglist);

unsigned printf(const char *format, ...);

unsigned fprintf(int fd, const char *format, ...);

char *itoa(int n, char *str, int radix);

int strcmp(const char *src, const char *dst);

char *strcpy(char *dest, char *src);

unsigned strlen(const char *str);

#ifdef __cplusplus
}
#endif

#endif //MYCRT_MYCRT_H
