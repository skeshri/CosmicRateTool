#!/bin/bash

DATASET=$1
FILELIST=$2

#echo "$DATASET"

das_client.py --limit=100000 --query="file dataset=$DATASET" >& $FILELIST

sed -e '1,3d' $FILELIST > temp && mv temp $FILELIST
