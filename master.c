#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>


struct msgp {
    long msgtype;
    char msgtext[100];
};


int main (int argc, char **argv) {

    int amount = 0;

    if (argc < 2) {
        printf("Try again with amount of processes\n");
        return -1;
    } else {
        printf("Waiting for %d processes\n", atoi(argv[1]));
        amount = atoi(argv[1]);
    }

    int numb[2] = {amount, amount};

    int fd = open("help_file.txt", O_CREAT | O_TRUNC | O_WRONLY, 0777);
    write(fd, numb, 2 * sizeof(int));
    close(fd);

    key_t key = ftok("/home/ilidannaga/CLionProjects/myshell/mshell/wtf.c", 'a');
    int msgid = msgget(key, IPC_CREAT | 0666);

    int got_end = 0;
    int flag = 1;

    while (flag) {

        struct msgp message;

        msgrcv(msgid, &message,100, 0, 0);

        if (message.msgtype > amount) {
            got_end ++;
        } else {
            printf("copy number %ld: ", message.msgtype);
            puts(message.msgtext);
        }

        if (got_end >= amount)
            break;
    }

    msgctl(msgid, IPC_RMID, 0);

    return 0;

}