#!/bin/bash

DATASET=$1
FILELIST=$2

if [ "$#" -lt '1' ]
then
  printf "\nDataset name is not given.\n"
  printf "Usage:\n"
  printf "./downloadFiles.sh [DataSet] [FileName(optional)]\n\n"
  exit 1;
fi
 
if [ "$#" != '2' ]
then
FILELIST="list.txt"
fi

das_client.py --limit=0 --query="file dataset=$DATASET | grep file.name, file.nevents > 0" >& $FILELIST

sed -e '1,3d' $FILELIST > temp && mv temp $FILELIST

if [ `find -iname temp` ]
then
rm temp
fi

