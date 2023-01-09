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
    return 0;
}
