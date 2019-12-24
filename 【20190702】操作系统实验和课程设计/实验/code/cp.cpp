#include <cstdio>
#include <cstdlib>
#include <deque>
#include <iostream>
#define PIPESIZE 8 //缓冲区大小为PIPESIZE

#define RUN 0                          /* status of process */
#define WAIT 1 /* status of process */ //阻塞态
#define READY 2                        /* status of process */
#define FINISH 3                       /* status of process */

using namespace std;

struct pcb
{ //pcb
    //char *name;
    string name;
    int status;
    int time; /* times of execution */
};

struct pipetype
{                         //记录缓冲区状况的表
    int num_data;         //缓冲区数据数目
    int producer_ptr;     //写指针
    int consumer_ptr;     //读指针
    deque<int> prod_wait; //生产者等待队列（保存的是生产的数据）
    int consu_waite_size; //消费者等待队列，只记录消费者等待数目
};
pipetype pipetb;

int pipe[PIPESIZE]; //缓冲区

void runp(int output, pcb &p, int *pipe, pipetype &pipetb);
void runc(pcb &p, int *pipe, pipetype &pipetb);
void print(pcb &p, int *pipe, pipetype &pipetb);

int main()
{
    int output = 0; //生产者生产的数据
    for (int i = 0; i < PIPESIZE; i++)
        pipe[i] = -1;
    char ch = 'n';

    cout<<"Press 'p' to Run PRODUCER, 'c' to Run CONSUMER, 'e' to exit from the program.\nEnter(p/c/e):";

    for (int i = 0; i < 1000; i++)
    {
        while (ch == 'n')
        {
            scanf("%c", &ch);
            if (ch != 'p' && ch != 'c' && ch != 'e')
            {
                cout<<"Enter(p/c/e):";
                ch = 'n';
            }
        }
        switch (ch)
        {
        case 'p':
        {
            pcb process = {"PRODUCER", READY, 0}; //产生一个生产者进程并去执行 最后调用print函数
            output = (output + 1) % 100;
            runp(output, process, pipe, pipetb);
            print(process, pipe, pipetb);
            break;
        }
        case 'c':
        {
            pcb process = {"CONSUMER", READY, 0}; //产生一个消费者进程并去执行 最后调用print函数
            runc(process, pipe, pipetb);
            print(process, pipe, pipetb);
            break;
        }
        case 'e':
            exit(0);
        }
        ch = 'n';
    }
}

void runp(int output, pcb &p, int *pipe, pipetype &pipetb)
{ /* Run producer */
cout<<endl;
    p.status = RUN;
    printf("Run PRODUCER: product %d.\n", output);

    if (pipetb.num_data == PIPESIZE)
    { //相当于P(empty);
        pipetb.prod_wait.push_back(output);
        printf("The buffer is full. The PRODUCE is BLOCKED, %d PRODUCEs BLOCKED.\n", pipetb.prod_wait.size());
        cout<<"Wait:";
        for(int i=0;i<pipetb.prod_wait.size();i++)
        cout<<pipetb.prod_wait[i]<<"|";
        cout<<endl;
    }
    else
    { //如果P通过，把数据放到缓冲区里
        pipe[pipetb.producer_ptr] = output;
        pipetb.num_data++;
        //pipetb->producer_ptr++;
        pipetb.producer_ptr = (pipetb.producer_ptr + 1) % PIPESIZE;
        p.status = FINISH;
        //printf("The PRODUCE is END.\n");
        p.time++;
    }

    if (pipetb.consu_waite_size)
    { //相当于V(full);唤醒消费者进程
        pipetb.consu_waite_size--;
        printf("A CONSUMER is WAKEUP and RUNNING. Consuming: %d. %d CONSUMERs BLOCKED.\n", output, pipetb.consu_waite_size);
        pipe[pipetb.consumer_ptr] = -1;
        pipetb.consumer_ptr = (pipetb.consumer_ptr + 1) % PIPESIZE;
        pipetb.num_data--;
    }
}

void runc(pcb &p, int *pipe, pipetype &pipetb)
{ /* Run consumer */
cout<<endl;
    int c;
    p.status = RUN;
    printf("Run CONSUMER:");
    if (pipetb.num_data == 0)
    { //相当于P(full);
        pipetb.consu_waite_size++;
        printf("The buffer is empty. The CONSUMER is BLOCKED, %d CONSUMERs BLOCKED.\n", pipetb.consu_waite_size);
    }
    else
    { //如果P通过，从缓冲区拿一个数据，顺序为从前向后循环
        c = pipe[pipetb.consumer_ptr];
        pipe[pipetb.consumer_ptr] = -1;
        //pipetb->consumer_ptr++;
        pipetb.consumer_ptr = (pipetb.consumer_ptr + 1) % PIPESIZE;
        pipetb.num_data--;
        p.status = FINISH;
        printf("Use %d.\n", c);//Use %d. The CONSUMER is END.\n
        p.time++;
    }

    if (pipetb.prod_wait.size())
    { //相当于V(empty);唤醒生产者进程
        pipe[pipetb.producer_ptr] = pipetb.prod_wait.front();
        pipetb.num_data++;
        pipetb.prod_wait.pop_front();
        printf("A PRODUCER is WAKEUP, %d PRODUCERs BLOCKED.\n", pipetb.prod_wait.size());
        pipetb.producer_ptr = (pipetb.producer_ptr + 1) % PIPESIZE;
    }
}

void print(pcb &p, int *pipe, pipetype &pipetb)
{ //打印显示缓冲区情况、读写指针、数据数目
    int i;
    //printf("         ");
   // for (i = 0; i < PIPESIZE; i++)
    ///    printf("------ ");
   // printf("\n        |");
    for (i = 0; i < PIPESIZE; i++)
        if (pipe[i] != -1)
            printf("  %2d  |", pipe[i]);
        else
            printf("      |");
    //printf("\n         ");
    //for (i = 0; i < PIPESIZE; i++)
    //    printf("------ ");
    printf("\nWritePtr = %d, ReadPtr = %d,  ", pipetb.producer_ptr, pipetb.consumer_ptr);
    printf("Numbers of data : %d\n", pipetb.num_data);
    printf("\n");
}

