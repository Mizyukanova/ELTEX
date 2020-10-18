#!/bin/bash

echo "Введите через сколько секунд завести будильник"
read timeout

echo "Введите путь к воспроизводимому файлу"
read file

sleep $timeout
aplay $file
