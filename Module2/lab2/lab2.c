#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <math.h>

void input(char **packedData, int *size) 
{
	long inputNumber;
	char *data;
	
	int n;
	printf ("Сколько переменных:"); 
	scanf("%d",&n);

	data=(char*)malloc(2*n);

	printf ("Ввод переменных:\n"); 
	int offset = 0;
	// Ввод элементов массива
	for (int i = 0; i<n; i++)
	{
		scanf("%ld", &inputNumber);
		if ( inputNumber > -pow(2, sizeof(char)*8-1) && inputNumber < pow(2, sizeof(char)*8-1)-1 )
		{
			if (offset+sizeof(char)+1 > 2*n)
			{
				data=(char*)realloc(data, 2*offset);
			}
			*(data+offset)=0;
			offset++;
			*(data+offset)=inputNumber;
			offset++;
			printf ("Сохранено в char\n");
		}
		else if (inputNumber > -pow(2, sizeof(int)*8-1) && inputNumber < pow(2, sizeof(int)*8-1)-1 )
		{
			if (offset+sizeof(int)+1 > 2*n)
			{
				data=(char*)realloc(data, 2*(offset+sizeof(int)));
			}
			*(data+offset)=1;
			offset++;
			*(int*)(data+offset)=inputNumber;
			offset+=sizeof(int);
			printf ("Сохранено в int\n");
		}
		else if (inputNumber > -pow(2, sizeof(long)*8-1) && inputNumber < pow(2, sizeof(long)*8-1)-1 )
		{
			printf("done\n");
			if (offset+sizeof(long)+1 > 2*n)
			{
				data=(char*)realloc(data, 2*(offset+sizeof(long)));
			}
			*(data+offset)=2;
			offset++;
			*(long*)(data+offset)=inputNumber;
			offset+=sizeof(long);
			printf ("Сохранено в long\n");
		}
	}
	*packedData=data;
	*size=offset;
	return ;
}

void output(char *data, int offset)
{
	printf ("Вывод переменных:\n");
	for (int i=0; i<offset; )
	{
		if (data[i] == 0)
		{
			i+=sizeof(char);
			printf("%d\n", *(data+i));
			i+=sizeof(char);
		}
		else if (data[i] == 1)
		{
			i+=sizeof(char);
			printf("%d\n", *(int*)(data+i));
			i+=sizeof(int);
		}
		else if (data[i] == 2)
		{
			i+=sizeof(char);
			printf("%ld\n", *(long*)(data+i));
			i+=sizeof(long);
		}
	}
}

int main()
{
	char *a=NULL;
	int n=0;

	input(&a, &n);
	
	output(a, n);
	return 0;
}

