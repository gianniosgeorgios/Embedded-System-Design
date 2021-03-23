#include <unistd.h>
#include <sys/syscall.h>
#include <stdio.h>
#define SYS_new 386
int main(void) {
    printf("Invoking system call.\n");
    long ret = syscall(SYS_new);
    printf("Syscall returned %ld.\n", ret);
    return 0;
}

