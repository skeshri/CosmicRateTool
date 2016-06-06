#!/bin/bash

DATASET=$1
FILELIST=$2

#echo "$DATASET"
if ["$# < 2"]
then
echo "Enter Dataset name as first argument and second argument as filename.\n"
exit
fi

das_client.py --limit=100000 --query="file dataset=$DATASET" >& $FILELIST

sed -e '1,3d' $FILELIST > temp && mv temp $FILELIST
