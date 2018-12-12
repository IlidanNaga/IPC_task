#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

    int fd = open("help_file.txt", O_RDWR);
    int numb[2];

    if (!read(fd, numb, 2 * sizeof(int))) {
        printf("ERROR opening sender\n");
        return -1;
    }

    if (numb[0] < 1)
        return 0;

    int type = numb[0];
    int die = numb[1] + numb[0];
    numb[0] --;

    lseek(fd, 0L, SEEK_SET);

    write(fd, numb, 2 * sizeof(int));

    close(fd);

    sleep(1);
    key_t key = ftok("/home/ilidannaga/CLionProjects/myshell/mshell/wtf.c", 'a');
    int msgid = msgget(key, IPC_CREAT);

    int i;
    struct msgp message;

    for (i = 1; i < argc; i++) {

        message.msgtype = type;
        memmove(message.msgtext, argv[i], sizeof(argv[i]));

        msgsnd(msgid, &message, 100, 0);
    }

    message.msgtype = die;
    msgsnd(msgid, &message, 100, 0);

    return 0;
}