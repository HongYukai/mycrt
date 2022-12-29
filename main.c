<<<<<<< HEAD
#include "./Mycrt/mycrt.h"

int main(int argc, char* argv[]) {
//    int fd = open("test.txt", "r");
//    char buf[16];
//    int n = read(fd, buf, sizeof(buf));
//    const char expr[] = "%s\n";
//    printf(expr, buf);
    printf("%d\n", 1);
    int* i = (int*) malloc(sizeof(int));
    *i = 6;
    printf("%d\n", *i);
=======
#include "mycrt.h"

int main(int argc, char* argv[]) {
    int fd = open("test.txt", "r");
    char buf[16];
    int n = read(fd, buf, sizeof(buf));
    const char expr[] = "%s\n";
    printf(expr, buf);
>>>>>>> 4b4fae43dc16ab2f8e3139d39dcd2b4e9d2a788e
    return 0;
}
