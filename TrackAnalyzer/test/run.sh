#!/bin/bash

QUEUE=$1

if [ $# -lt 1 ] 
then
printf "Job is submitted to Queue '8nh'.\n\n"
printf "If you want to submit job in specific queue then please use :\n"
printf "sh run.sh [Queue name]\n\n"
bsub -q 8nh < job.sh 

else 
bsub -q $QUEUE < job.sh

fi

