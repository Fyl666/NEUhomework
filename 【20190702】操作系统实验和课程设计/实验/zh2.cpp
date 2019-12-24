/*************************/
//它并没有按照指定顺序执行，
//在之前子进程未建立时，
//由于父进程要执行时间长，
//然后子进程居然执行了？
/********************* */
#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<sys/wait.h>
#define MAXN 1023
using namespace std;
int AcessSeries[MAXN]= {1,2,3,4,1,2,5,1,2,3,4,5};
int reg[MAXN],frame[MAXN],exist[MAXN];;
int regSize,hitNum,ifout;
int acessSize, pagesSize;


void randomG(int acc, int pag)
{
    for(int i=acc;i<MAXN;AcessSeries[i]=-1, i++);
    cout<<"AcessSeries:"<<endl;
    for(int i=12;i<acc;i++)
    {
        int randnum = rand()%pag + 1;
        AcessSeries[i] = randnum;
    }
    for(int i=0;i<acc;cout<<AcessSeries[i]<<" ",i++);
    cout<<endl;
}

void display()
{
    for(int i=0;i<regSize && frame[i]!=-1;i++)
    {
        cout<<frame[i]<<"|";
    }
}

int hit(int come)
{
    for(int i=0;i<regSize && reg[i]!=-1;i++)
    {
        if(reg[i]==come)
            return i;
    }
    return -1;
}

int getRealLen(int order)
{
    int len=0;
    if(order==1)for(int i=0;reg[i]!=-1;i++,len=i);
    if(order==2)for(int i=0;frame[i]!=-1;i++,len=i);
    if(order==3)for(int i=0;exist[i]!=-1;i++,len=i);
    return len;
}

int getBig()
{
    for(int i=0;i<MAXN;exist[i]=-1,i++);
    for(int i=0;i<MAXN;i++)
    {
        int flag = 0;
        for(int j=0;exist[j]!=-1;j++)
        {
            if(AcessSeries[i]==exist[j]){flag=1;break;}
        }
        if(flag==0){exist[getRealLen(3)]=AcessSeries[i];}
    }
    return getRealLen(3);
}

void universal(int style)
{
    int hitflag;
    for(int i=0;AcessSeries[i]!=-1;i++)
    {
        hitflag = hit(AcessSeries[i]);
        if(hitflag>=0)
        {
            hitNum ++;
            //FIFO
            if(style == 1){}
            //LRU
            else if(style == 2)
            {
                int temp = AcessSeries[i];
                for(int j=hitflag;j>0;reg[j]=reg[j-1],j--);
                reg[0] = temp;
            }
        }
        else
        {
            //adjust reg
            int target=-1;
            for(int j=0;j<regSize&&reg[j]!=-1;target=reg[j],j++);
            for(int j=regSize-1;j>0;reg[j]=reg[j-1],j--);
            reg[0]=AcessSeries[i];
            //adjust frame
            int len = getRealLen(2);
            if(len<regSize){frame[len]=AcessSeries[i];}
            else
            {
                for(int j=0;j<regSize;j++)
                {
                    if(frame[j]==target)
                    {
                        frame[j]=AcessSeries[i];
                        break;
                    }
                }
            }
        }
        if(ifout==1)
        {
            cout<<AcessSeries[i]<<":";
            display();
            if(hitflag>=0)cout<<"->Hit :)";
            cout<<endl;
        }
    }
    if(ifout==1) cout<<hitNum<<"/"<<acessSize<<" were hit."<<endl;
}

int fifo()
{
    hitNum = 0;
    for(int i=0;i<MAXN;reg[i]=frame[i]=-1,i++);
    if(ifout==1)cout<<"FIFO:"<<endl;
    universal(1);
    return hitNum;
}

int lru()
{
    hitNum = 0;
    for(int i=0;i<MAXN;reg[i]=frame[i]=-1,i++);
    if(ifout==1)cout<<"LRU:"<<endl;
    universal(2);
    return hitNum;
}

void child()
{
    pid_t pid1, pid2;
    cout<<endl<<"Input Size of Reg:";
    pid1 = fork();
    pid2 = fork();
    if(pid1>0){fifo();}
    if(pid2>0){lru();}
    else
    {
        wait(0);
    }
}

int main()
{
    cout<<"Input Size of Acess_Series:";
    cin>>acessSize;
    cout<<"Input Types of pages:";
    cin>>pagesSize;
    randomG(acessSize,pagesSize);
    int hitThis = 0, ifbelady = 0, big = getBig();
    cout<<"Hit times of FIFO(Size:1-"<<big<<"): ";
    for(int i=1;i<=big;i++)
    {
        regSize=i;
        int temp = fifo();
        if(temp<hitThis)ifbelady=1;
        cout<<temp<<"|";
        hitThis = temp;
    }
    cout<<" of "<<acessSize;
    if(ifbelady==1){cout<<endl<<"FIFO Belady!";}
    hitThis = 0, ifbelady = 0;
    cout<<endl<<"Hit times of LRU(Size:1-"<<big<<"): ";
    for(int i=1;i<=big;i++)
    {
        regSize=i;
        int temp = lru();
        if(temp<hitThis)ifbelady=1;
        cout<<temp<<"|";
        hitThis = temp;
    }
    cout<<" of "<<acessSize;
    if(ifbelady==1){cout<<endl<<"LRU Belady!";}
    ifout = 1;

    child();
    return 0;
}