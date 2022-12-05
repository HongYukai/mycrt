#include "mycrt.h"

int main(int argc, char* argv[]) {
    int fd = open("test.txt", "r");
    char buf[16];
    int n = read(fd, buf, sizeof(buf));
    const char expr[] = "%s\n";
    printf(expr, buf);
    return 0;
}
