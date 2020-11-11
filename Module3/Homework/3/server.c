#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#define LAST_MESSAGE 255

struct mymsgbuf
{
	long mtype;
	int id;
	char message[100];
}mybuf;

int main()
{
	int len,maxlen,msqid;
	char pathname[]="myfile";
	key_t key;

	/* Генерируем IPC ключ из имени файла 09-1a.c в текущей директории
	и номера экземпляра очереди сообщений 0. */
	if((key=ftok(pathname,0)) < 0)
	{
		printf("Error: can't generate key\n");
	}
	
	/* Пытаемся получить доступ по ключу к очереди сообщений, если она существует,
	или создать ее, если она еще не существует, с правами доступа
	read & write для всех пользователей */
	if((msqid=msgget(key, 0666 | IPC_CREAT))<0)
	{
		printf("Error: can't get msqid\n");
	}
	
	while(1)
	{
		maxlen=sizeof(mybuf);
		
		if((len=msgrcv(msqid,(struct msgbuf*)&mybuf,maxlen,1,0)) < 0)
		{
			printf("Error: can't recive message from queue\n");
		}

		printf("message type = %ld, id is %d\n",mybuf.mtype,mybuf.id);

		mybuf.mtype=mybuf.id;
		len=sizeof(mybuf);
		strcpy(mybuf.message,"Hello, client. This is text message from server.\n");
		
		if(msgsnd(msqid,(struct msgbuf*)&mybuf,len,0) < 0)
		{
			printf("Error: Can't send message to queue\n");
			msgctl(msqid,IPC_RMID,(struct msqid_ds*)NULL);
		}
		printf("Server %d sent message %s\n",getpid(),mybuf.message);
	}
	return 0;
}
