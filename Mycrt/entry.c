//
// Created by 12096 on 2022/11/14.
//

#include "mycrt.h"

extern int main(int argc, char* argv[]);
void exit(int exit_code);

static void crt_fatal_error(const char* msg) {
<<<<<<< HEAD
    printf("fatal error: %s\n", msg);
=======
    // printf("fatal error: %s", msg);
>>>>>>> 4b4fae43dc16ab2f8e3139d39dcd2b4e9d2a788e
    exit(1);
}

void exit(int exit_code) {
    // my_crt_call_exit_routine();
    asm("movl %0, %%ebx \n\t"
        "movl $1, %%eax \n\t"
        "int $0x80 \n\t"
        "hlt \n\t"::"m"(exit_code));  //! hlt is a protective instruction
}

void my_crt_entry(void) {
    int ret;
    int argc;
    char** argv;
    volatile char* ebp_reg = 0;
    asm("movl %%ebp, %0 \n\t":"=r"(ebp_reg));
    argc = *(int*)(ebp_reg + 4);
    argv = (char**) (ebp_reg + 8);
    if (!my_crt_heap_init()) {  //! heap is not initialized
        crt_fatal_error("heap initialized failed.");
    }
    if (!my_crt_io_init()) {  //! io is not initialized
        crt_fatal_error("io initialized failed.");
    }
    ret = main(argc, argv);
    exit(ret);
}