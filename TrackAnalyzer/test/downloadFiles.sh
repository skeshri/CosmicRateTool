#!/bin/bash

DATASET=$1
FILELIST=$2

if [ !"$1" ]
then
  printf "\nDataset name is not given."
  printf "Usage:\n"
  printf "./downloadFiles.sh [DataSet] [FileName(optional)]\n\n"
  exit 1;
fi

if [ !"$2" ]
then 
FILELIST="list.txt"
fi

das_client.py --limit=100000 --query="file dataset=$DATASET" >& $FILELIST

sed -e '1,3d' $FILELIST > temp && mv temp $FILELIST

if [ `find -iname temp` ]
then
rm temp                                                                                                                                      
fi

