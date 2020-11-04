#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{

	int fd, result;
	size_t size;
	char resstring[14];
	char name[]="aaa.fifo";

	/* Обнуляем маску создания файлов текущего процесса для того, чтобы
	права доступа у создаваемого FIFO точно соотвествовали параметру вызова mknod() */

	//(void)umask(0);

	/* Мы находимся в порожденном процессе, который будет получать информацию от процесса-родителя. Открываем FIFO на чтение.*/
	if ( (fd = open(name, O_RDONLY | O_NDELAY)) < 0 )
	{
		/* Если открыть FIFO не удалось, печатаем об этом сообщение и прекращаем работу */
		printf("Can\'t open FIFO for reading\n");
		exit(-1);
	}

	/* Пробуем прочитать из FIFO 14 байт в массив, т.е. всю записанную строку */
	size = read(fd, resstring, 14);

	if(size < 0)
	{
		/* Если прочитать не смогли, сообщаем об ошибке и завершаем работу */
		printf("Can\'t read string\n");
		exit(-1);
	}

	/* Печатаем прочитанную строку */
	printf("%s\n",resstring);

	/* Закрываем входной поток и завершаем работу */

	close(fd);
	printf("Child exit\n");

	return 0;
}
