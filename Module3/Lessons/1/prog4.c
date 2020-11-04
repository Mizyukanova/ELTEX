#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>

int main()
{

	int fd;
	size_t size;
	char string[20];


	/* Попытаемся открыть файл с именем myfile в текущей директории только
	для операций вывода. Если файл не существует, попробуем его создать с правами
	доступа 0666, т.  е. read-write для всех категорий пользователей */
	if((fd = open("myfile", O_RDONLY | O_CREAT, 0666)) < 0)
	{
		/* Если файл открыть не удалось, печатаем об этом сообщение и прекращаем работу */
		printf("Can\'t open file\n");
		exit(-1);
	}

	/* Пробуем прочитать из файла 14 байт, т.е. всю строку "Hello, world!"
	вместе с признаком конца строки */
	size = read(fd, string, 14);

	if(size != 14)
	{
		/* Если записалось меньшее количество байт, сообщаем об ошибке */
		printf("Can\'t write all string\n");
		exit(-1);
	}

	printf("%s\n",string);


	/* Закрываем файл */
	if(close(fd) < 0)
	{
		printf("Can\'t close file\n");
	}

	return 0;
}
