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

#define amount 10
#define shift 11


int main (int argc, char **argv) {

    int numb[2] = {amount, amount};

    printf("Defined as %d sender processes atm\n", numb[0]);

    int fd = open("help_file.txt", O_CREAT | O_TRUNC | O_WRONLY, 0777);
    write(fd, numb, 2 * sizeof(int));
    close(fd);

    key_t key = ftok("/home/ilidannaga/CLionProjects/myshell/mshell/wtf.c", 'a');
    int msgid = msgget(key, IPC_CREAT | 0666);

    int got_end[amount] = {0};

    int flag = 1;

    while (flag) {

        struct msgp message;

        msgrcv(msgid, &message,100, 0, 0);

        if (message.msgtype > amount) {
            got_end[message.msgtype - shift] = 1;
        } else {
            printf("copy number %ld: ", message.msgtype);
            puts(message.msgtext);
        }

        int i;
        flag = 0;
        for (i = 0; i < amount; i++) {
            if (!got_end[i])
                flag = 1;
        }
    }

    msgctl(msgid, IPC_RMID, 0);

    return 0;

}