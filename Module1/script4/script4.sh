#!/bin/bash

countAttempts=10

echo "Введите периодичность проверки процесса (в секундах)"
read timeout

echo "Введите имя процесса"
read process

#18) SIGCONT - возобновляет выполнение процесса, остановленного сигналом SIGSTOP
signal=18
stat=`ps -aux | grep $process | tr -s ' ' | cut -d ' ' -f 8 | cut -c 1 | head -1`
pid=`pgrep $process | head -1`

i=1
while [ "$i" -le "$countAttempts" ]
do
	sleep $timeout
	if [ "$stat" = "T" ]
	then
		kill -18 $pid
	fi
	i=$(($i+1))
done
