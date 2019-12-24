#include<unistd.h>
#include<sys/types.h>
#include<errno.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_DATA_LEN    256
#define SLEEP_TIME  0

void handler(int id) 
{ int status; if (waitpid(-1,&status,0)<0 ){ perror("waitpid"); exit(3); } printf("handler func wait success!\n"); }

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
        pid1 = waitpid(pid1,NULL,0);
        pid2 = waitpid(pid2,NULL,0);
        pid3 = waitpid(pid3,NULL,0);
        read(pipe_fd[0],buf,sizeof(buf)-3);
        printf("%s",buf);
    }
        return 0;
}

