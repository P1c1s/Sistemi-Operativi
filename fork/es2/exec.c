#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    execl("ls", "ls");
    return 0;
}