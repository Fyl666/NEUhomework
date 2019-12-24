#include<stdio.h>
#include<unistd.h>
#include<errno.h>
#include<string.h>
#include<stdlib.h>

int a = 0;
int main()
{
	pid_t id = fork();
	if(id==0)
	{
		a = 1;
		printf("child:a=%d\n",a);	
	}
	else
	{
		printf("father:a=%d\n",a);
		sleep(1);
	}
	return 0;
}
