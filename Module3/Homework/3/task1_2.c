/* Программа 2 для иллюстрации работы с очередями сообщений */


/* Эта программа осуществляет двустороннюю связь через одну очередь сообщений. 
Процесс 1 может посылать процессу 2 сообщения с типом 1, а получать от него сообщения с типом 2.*/


#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define LAST_MESSAGE 255 /* Тип сообщения для прекращения работы */

int main()
{

	int msqid; /* IPC дескриптор для очереди сообщений */

	char pathname[] = "myfile"; /* Имя файла, использующееся для генерации ключа.
	Файл с таким именем должен существовать в текущей директории */

	key_t key; /* IPC ключ */

	int i=0, len, maxlen; /* Реальная длина и максимальная длина информативной части сообщения */

	/* Ниже следует пользовательская структура для сообщения */
	struct mymsgbuf
	{
		long mtype;
		char mtext[81];
	} mybuf;

	/* Генерируем IPC ключ из имени файла 09-1a.c в текущей директории
	и номера экземпляра очереди сообщений 0 */
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

	/* В бесконечном цикле принимаем сообщения типа 1 в порядке FIFO с максимальной длиной информативной части 81 символ до тех пор, пока не поступит сообщение с типом LAST_MESSAGE*/	
	/* Если принятое сообщение имеет тип 1, печатаем текст принятого сообщения. */
	maxlen = 81;
	while(i != 1)
	{
		if( len = msgrcv(msqid, (struct msgbuf *) &mybuf, maxlen, 1, 0) > 0)
		{
			i=1;
			printf("message type = %ld, info = %s\n", mybuf.mtype, mybuf.mtext);
			
			//msgctl(msqid, IPC_RMID, (struct msqid_ds *) NULL);
		}
	}
	

	/* Посылаем  сообщение с типом 2 в очередь сообщений, идентифицируемую msqid.*/
	/* Сначала заполняем структуру для нашего сообщения и определяем длину информативной части */
	mybuf.mtype = 2;
	strcpy(mybuf.mtext, "This is next message");
	len = strlen(mybuf.mtext)+1;

	/* Отсылаем сообщение. В случае ошибки сообщаем об этом и удаляем очередь сообщений из системы. */
	if (msgsnd(msqid, (struct msgbuf *) &mybuf, len, 0) < 0)
	{
		printf("Can\'t send message to queue\n");
		msgctl(msqid, IPC_RMID, (struct msqid_ds *) NULL);
		exit(-1);
	}

	return 0; /* Исключительно для отсутствия warning'ов при компиляции. */
}