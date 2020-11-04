#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
 
int main(int argc, char *argv[], char *envp[])
{

pid_t pid, ppid, chpid;
int a = 0;
 
chpid = fork();
 
/* При успешном создании нового процесса с этого места псевдопараллельно начинают работать 2 процесса: старый и новый */
if (chpid == 0)
{
	printf("I am a child\n");
}
else
{
	sleep(5);
	printf("I am a parent\n");
} 

/* Узнаем идентификаторы текущего и родительского процесса (в каждом из процессов !!!) */
pid = getpid();
ppid = getppid();

/* Печатаем значения PID, PPID и вычисленное значение a (в каждом из процессов !!!) */
printf("My pid = %d, my ppid = %d, result = %d\n", (int)pid, (int)ppid, a); 

return 0;

}
