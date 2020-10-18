#!/bin/bash

echo "Введите имя процесса"
read process

echo "Лог-файлы для $process:"
(find /var/log -mtime 30 | grep -irl $process /var/log) 2> /dev/null
