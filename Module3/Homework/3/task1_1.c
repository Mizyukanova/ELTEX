/* Программа 1 для иллюстрации работы с очередями сообщений */

 

/* Эта программа получает доступ к очереди сообщений,
отправляет в нее 5 текстовых сообщений с типом 1
и одно пустое сообщение с типом 255, которое будет служить
для программы 2 сигналом прекращения работы. */

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define LAST_MESSAGE 255 /* Тип сообщения для прекращения работы программы 2 */

int main()
{

	int msqid; /* IPC дескриптор для очереди сообщений */

	char pathname[] = "myfile"; /* Имя файла, использующееся для генерации ключа.
	Файл с таким именем должен существовать в текущей директории */

	key_t key; /* IPC ключ */

	int maxlen; /* Реальная длина и максимальная длина информативной части сообщения */

	int i=0,len; /* Cчетчик цикла и длина информативной части сообщения */

	/* Ниже следует пользовательская структура для сообщения */

	struct mymsgbuf
	{
		long mtype;
		char mtext[81];
	} mybuf;

	/* Генерируем IPC ключ из имени файла 09-1a.c в текущей директории
	и номера экземпляра очереди сообщений 0. */
	if((key = ftok(pathname,0)) < 0)
	{
		printf("Can\'t generate key\n");
		exit(-1);
	}

	/* Пытаемся получить доступ по ключу к очереди сообщений, если она существует,
	или создать ее, если она еще не существует, с правами доступа
	read & write для всех пользователей */
	if((msqid = msgget(key, 0666 | IPC_CREAT)) < 0)
	{
		printf("Can\'t get msqid\n");
		exit(-1);
	}

	/* Посылаем  сообщение с типом 1 в очередь сообщений, идентифицируемую msqid.*/
	/* Сначала заполняем структуру для нашего сообщения и определяем длину информативной части */
	mybuf.mtype = 1;
	strcpy(mybuf.mtext, "This is text message");
	len = strlen(mybuf.mtext)+1;

	/* Отсылаем сообщение. В случае ошибки сообщаем об этом и удаляем очередь сообщений из системы. */
	if (msgsnd(msqid, (struct msgbuf *) &mybuf, len, 0) < 0)
	{
		printf("Can\'t send message to queue\n");
		msgctl(msqid, IPC_RMID, (struct msqid_ds *) NULL);
		exit(-1);
	}
	
	maxlen = 81;
	while(i != 1)
	{
		if( len = msgrcv(msqid, (struct msgbuf *) &mybuf, maxlen, 2, 0) > 0)
		{
			i=1;
			printf("message type = %ld, info = %s\n", mybuf.mtype, mybuf.mtext);

			msgctl(msqid, IPC_RMID, (struct msqid_ds *) NULL);
		}
	}
	return 0;
}
