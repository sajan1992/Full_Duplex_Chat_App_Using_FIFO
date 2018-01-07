#include"header.h"
#define FIFONAME1 "./MyFIFO1"
#define FIFONAME2 "./MyFIFO2"
#define EXIT "exit"

int main()
{
	int ret1,ret2,rfork,ec,flag=0;
	char msg1[100],msg2[100];
	memset(&msg1,'\0',100);
	memset(&msg2,'\0',100);
//FIFO for read purpose
	if(access(FIFONAME1,F_OK) == -1)
	{
		ret1 = mkfifo(FIFONAME1,666);
		if(ret1 == -1)
		{
			perror("\e[41mMkfifo\e[0m");
			exit(EXIT_FAILURE);

		}
	}
	ret1 = open(FIFONAME1,O_RDONLY);
	if(ret1 == -1)
	{
		perror("\e[41mOPEN\e[0m");
		exit(EXIT_FAILURE);
	}
	printf("\e[42mCONNECTION ESTABLISHED [ RDONLY ]\e[0m\n");

//FIFO for read purpose
	if(access(FIFONAME2,F_OK) == -1)
	{
		ret2 = mkfifo(FIFONAME2,666);
		if(ret2 == -1)
		{
			perror("\e[41mMkfifo\e[0m");
			exit(EXIT_FAILURE);

		}
	}
	ret2 = open(FIFONAME2,O_WRONLY);
	if(ret2 == -1)
	{
		perror("\e[41mOPEN\e[0m");
		exit(EXIT_FAILURE);
	}
	printf("\e[42mCONNECTION ESTABLISHED [ WRONLY ]\e[0m\n");
	printf("\e[44mUSE \'exit\' to EXIT\e[0m\n");
	rfork = fork();
	if(rfork == -1)
	{
		perror("Fork");
		exit(EXIT_FAILURE);
	}
	//writing from fd
	if(rfork == 0)
	{
		while(1)
		{
		read(0,msg1,100);
		if(*msg1)
		{
			write(ret2,msg1,strlen(msg1));
		if(!(strncmp(msg1,"exit",4)))
		{
			kill(getppid(),SIGKILL);
			exit(EXIT_SUCCESS);
		}
		memset(&msg1,'\0',100);
		}
		}
	}
	//reading from fd
	if(rfork > 0)
	{
		while(1)
		if(read(ret1,msg2,100))
		{
		printf("\e[44mRecieved: \e[0m %s \n",msg2);
		if(!(strncmp(msg2,"exit",4)))
		{
			printf("\n\e[41mExit command Initiated!\e[0m\n");
			kill(rfork,SIGKILL);
			exit(EXIT_SUCCESS);
		}
		memset(&msg2,'\0',100);
		}
	}
	printf("\n");
	return 0;
}
