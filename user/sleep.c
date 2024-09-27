#include "kernel/types.h"
#include "user/user.h"


int main(int argc, char* argv[]) {
    if (argc != 2) {
        fprintf(2, "Usage: sleep <number>\n");
        exit(1);
    }
    sleep(atoi(argv[1]));
    printf("Nothoing happends for a little while\n");
    exit(0);
}