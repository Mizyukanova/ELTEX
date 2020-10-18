#!/bin/bash

echo "Введите место расположения папок "
read path

echo "Введите количество папок "
read nFolders

echo "Введите количество подпапок "
read mFolders

echo "Введите шаблон названия папок и подпапок"
read template

nFiles=2

cd $path
i=1
while  [ $i -le $nFolders ]
do
	mkdir $template$i
	i=$(($i+1))
done

for (( countFolder0 = 1; countFolder0 <= nFolders; countFolder0++ )) 
do 
    	cd $template$countFolder0
	j=1
	while  [ $j -le $mFolders ]
	do
        	mkdir $template$j       
        	j=$(($j+1))
	done

	for (( countFolder = 1; countFolder <= mFolders; countFolder++ )) 
	do 
		cd $template$countFolder
		for (( countFile = 1; countFile <= nFiles; countFile++ )) 
		do 
			touch File$countFile
		done
		cd ..
	done
	cd ..
done
