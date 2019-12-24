#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#define FIFO_NAME "/tmp/myfifo"
#define BUF_SIZE 1024

#define MAX_DATA_LEN 256
#define SLEEP_TIME 5

int main()
{
    int wfd;
    char buf[BUF_SIZE] = "Child1";
    umask(0);
    if (mkfifo(FIFO_NAME, S_IFIFO | 0666))
    {
        printf("Can't create FIFO.\n");
        exit(1);
    }
    while ((wfd = open(FIFO_NAME, O_WRONLY | O_NONBLOCK)) == -1)
    {
        perror("fopen error!");
        sleep(3);
    }

    pid_t pid1, pid2, pid3;
    int pipe_fd[2];
    int len, realen, pipeid;
    char buff[MAX_DATA_LEN], outpipe[MAX_DATA_LEN];
    pipeid = pipe(pipe_fd);
    pid1 = fork();
    if (pid1 == 0)
    {
        sleep(3);
        printf("Write: ");
        write(wfd, buf, strlen(buf) + 1);
        close(wfd);
        exit(0);
    }

    else
    {
        int rfd;
        char buf[BUF_SIZE];
        umask(0);
        if ((rfd = open(FIFO_NAME, O_RDONLY | O_NONBLOCK)) == -1)
        {
            perror("fopen error.\n");
            exit(1);
        }
        read(rfd, buf, BUF_SIZE);
        printf("Read content:%s\n", buf);
        sleep(2);
        close(rfd);
        exit(0);
    }
}
