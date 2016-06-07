#!/bin/bash

DATASET=$1
FILELIST=$2

#echo "$DATASET"
if [ "$#" != '2' ]
then
  echo -e "\nNumber of argument should be two"
  echo -e "1) Dataset name.\n2) filename.\n"
  exit 1;
fi

das_client.py --limit=100000 --query="file dataset=$DATASET" >& $FILELIST

sed -e '1,3d' $FILELIST > temp && mv temp $FILELIST
