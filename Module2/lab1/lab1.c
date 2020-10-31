// Компиляция gcc lab1.c -c
// Сборка gcc -o lab1 lab.o
// Запуск ./lab1
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() 
{
  char str[80];
  char identifier[40]; 
  char replace[40];
  char *istr;
  int i;
  
  memset(identifier,0,40);

  printf("Введите строку для преобразования: ");
  scanf("%s", str);
  
  if ((istr = strstr (str,"==")) != NULL)
  {
    i=istr-str;
    strncpy(replace,str,i);
    sprintf(replace+i, "=%s", str+i+2);
    strcpy(str, replace);
  }
  else if ((istr = strstr (str,"!=")) != NULL)
  {
    *istr='<';
    *(istr+1)='>';
  }
  else if ((istr = strstr (str,"+=")) != NULL)
  {
    i=istr-str;
    strncpy(identifier,str,i);
    strncpy(replace,str,i);
    sprintf(replace+i, ":=%s+%s", identifier, str+i+2);
    strcpy(str, replace);
  }
  else if ((istr = strstr (str,"-=")) != NULL)
  {
    i=istr-str;
    strncpy(identifier,str,i);
    strncpy(replace,str,i);
    sprintf(replace+i, ":=%s-%s", identifier, str+i+2);
    strcpy(str, replace);
  }
  else if ((istr = strstr (str,"=")) != NULL)
  {
    i=istr-str;
    strncpy(replace,str,i);
    sprintf(replace+i, ":=%s", str+i+1);
    strcpy(str, replace);
  }
  else
  {
    printf("Операции не найдено.");
  }
  
  printf("Полученная строка на языке Pascal: %s\n",str);
  return 0;
}