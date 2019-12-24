#include<unistd.h>
#include<sys/types.h>
#include<errno.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <termios.h>

struct termios tio;
tio.c_cc[VTIME] = 0; // timeout in deciseconds for noncanonical read
tio.c_cc[VMIN] = 0; // minimum number of characters for noncanonical read
tcsetattr(fd, TCSANOW, &tio);
#define MAX_DATA_LEN    256
#define SLEEP_TIME  5


int main()
{
    pid_t pid1,pid2,pid3;
    int pipe_fd[2];
    int len,realen,pipeid;
    char buf[MAX_DATA_LEN],outpipe[MAX_DATA_LEN];
    pipeid=pipe(pipe_fd);
    if(pipeid<0)
    {
        printf("pipe error\n");
        exit(1);
    }
    if((pid1=fork())==-1){
            printf("pid1 error\n");
            exit(1);
    }
    if(pid1==0)  {
        sleep(SLEEP_TIME);
        close(pipe_fd[0]);
        sprintf(outpipe,"Child1\n");
        len=strlen(outpipe);
        realen=write(pipe_fd[1], outpipe, len);
        exit(0);
    }
    if((pid2=fork())==-1){
                printf("pid2 error\n");
                exit(1);
        }
        if(pid2==0)  {
        sleep(SLEEP_TIME);
        close(pipe_fd[0]);
        sprintf(outpipe,"Child2\n");
        len=strlen(outpipe);
        realen=write(pipe_fd[1], outpipe, len);
        exit(0);
    }
        if((pid3=fork())==-1){
                printf("pid3 error\n");
                exit(1);
        }
        if(pid3==0)  {
        sleep(SLEEP_TIME);
        close(pipe_fd[0]);
        sprintf(outpipe,"Child3\n");
        len=strlen(outpipe);
        realen=write(pipe_fd[1], outpipe, len);
        exit(0);
    }
    else{
        read(pipe_fd[0],buf,sizeof(buf)-3);
        printf("%s",buf);
        exit(0);
    }
        return 0;
}

