
// Компиляция и компановка gcc task1.c
// Запуск ./a.out
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main(int argc, char *argv[], char *envp[])
{
	int i=0;
	while (i < argc)
	{
		printf("%s\n",argv[i]);
		i+=1;
	}
	return 0;
}