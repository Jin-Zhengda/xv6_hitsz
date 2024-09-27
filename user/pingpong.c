#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"


int main(void) {
    int p1[2], p2[2];
    char p_read[5], c_read[5];

    pipe(p1);
    pipe(p2);

    int parent_pid = getpid();
    int child_pid = fork();


    if (child_pid == 0) {
        close(p1[1]);
        close(p2[0]);

        read(p1[0], &c_read, 4);
        int child_pid = getpid();
        if (strcmp(c_read, "ping") == 0) {
            write(p2[1], "pong", 4);
            printf("%d: received ping from pid %d\n", child_pid, parent_pid);
            close(p1[0]);
            close(p2[1]);
            exit(0);
        }
    } else {
        close(p1[0]);
        close(p2[1]);

        write(p1[1], "ping", 4);
        read(p2[0], &p_read, 4);
        wait(0);
        if (strcmp(p_read, "pong") == 0) {
            printf("%d: received pong from pid %d\n", parent_pid, child_pid);
            close(p1[1]);
            close(p2[0]);
            exit(0);
        }
    }
}