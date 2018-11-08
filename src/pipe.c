// CAREFUL! This one is part of the assignment, so don't share it unless you
// really want to.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
    int fd[2];
    char buf[128];

    pipe(fd);

    pid_t pid = fork();

    if (pid == 0) {
        puts("CHILD: Waiting to read...");
        read(fd[0], buf, sizeof buf);
        printf("%s\n", buf);
        exit(0);
    }

    puts("PARENT: sleeping");
    sleep(3);

    puts("PARENT: writing");
    write(fd[1], "Hello!", 7);

    return 0;
}