#!/bin/bash

nFolders=50
mFolders=100
nFiles=200

mkdir Folder{1..50}

for (( countFolder0 = 1; countFolder0 <= nFolders; countFolder0++ )) 
do 
    cd Folder$countFolder0
	mkdir Folder{1..100}       

	for (( countFolder = 1; countFolder <= mFolders; countFolder++ )) 
	do 
		cd Folder$countFolder
		for (( countFile = 1; countFile <= nFiles; countFile++ )) 
		do 
			touch File$countFile
		done
		cd ..
	done
	cd ..
done
