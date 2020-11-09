/* Задание: написать программу, распечатывающую значения 
аргументов командной строки и параметров окружающей среды для текущего процесса.*/
// Компиляция и компановка gcc task1.c
// Запуск ./a.out аргументы

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