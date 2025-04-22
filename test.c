# include <unistd.h>

#include <unistd.h>
#include <stdio.h>

int main() {
    char cwd[256];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("Current dir: %s\n", cwd);
    } else {
        perror("getcwd() error");
    }
    return 0;
}