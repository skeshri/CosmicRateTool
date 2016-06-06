#!/bin/bash

QUEUE=$1

if [ $# -lt 1 ] 
then
bsub -q 8nh < job.sh 

else 
bsub -q $QUEUE < job.sh

fi

#bsub -q $1 < job.sh 

