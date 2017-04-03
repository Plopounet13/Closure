#!/bin/sh

GEN_CMD="./closure -generate"
NLIN_CL_CMD="./closure -naive - 0"
LIN_CL_CMD="./closure -improved - 0"

echo "# \t naive \t improved" 
n=5;
for i in `seq 100 100 2000`; do
  naive_time=0
  imp_time=0
  for j in `seq 1 $n`; do
    nlin_time=$(./closure -generate $i | ./closure -naive - 0 | grep "time: " | sed 's/time: //g')
    lin_time=$($GEN_CMD $i | $LIN_CL_CMD| grep "time: " | sed 's/time: //g') 
    naive_time=$( echo "$nlin_time + $naive_time" | bc -l)
    imp_time=$( echo "$lin_time + $imp_time" | bc -l)
  done
  naive_time=$( echo "scale=3;$naive_time / 5" | bc -l)
  imp_time=$( echo "scale=3;$imp_time / 5" | bc -l)
  echo "$i \t $naive_time \t $imp_time" | sed 's/\./,/g'
done
