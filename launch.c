#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#include <sys/wait.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>









int main (int argc, char **argv) {

    int fd = open("help_file.txt", O_RDONLY);
    int numb[2];

    if (read(fd, numb, 2 * sizeof(int)) < 1) {
        printf("Later\n");
        return -1;
    }
    close(fd);

    int i;

    for (i = 0; i < numb[0]/4 + 1; i++) {

        if (fork() == 0) {
            //son
            execlp("./2nd", "./2nd", "Breaking", "Free", NULL);
            exit(EXIT_FAILURE);
        }

        if (fork() == 0) {
            //son
            execlp("./2nd","./2nd", "For", "the", "glory", "of", "Merlin", NULL);
            exit(EXIT_FAILURE);
        }

        if (fork() == 0) {
            //son
            execlp("./2nd", "./2nd", "Adventure", "time", NULL);
            exit(EXIT_FAILURE);
        }

        if (fork() == 0) {
            //son
            execlp("./2nd", "./2nd", "Welcome", "to", "the", "Gravity", "Falls!", NULL);
            exit(EXIT_FAILURE);
        }

    }

    while (wait(NULL) != -1);

    return 0;

}