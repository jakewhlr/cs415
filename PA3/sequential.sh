#!/bin/bash
#SBATCH -n 1
#SBATCH --output=output/sequential/sequential.log
#SBATCH --mail-user=jakewheeler@nevada.unr.edu
#SBATCH --mail-type=ALL
#SBATCH --time=00:10:00
printf "1,000,000 integers"
out=$(srun bin/sequential -c -s 1000000 -e 123)
printf "$out," >> ./output/sequential/sequential.csv && printf "$out s\n"

printf "10,000,000 integers"
out=$(srun bin/sequential -c -s 10000000 -e 123)
printf "$out," >> ./output/sequential/sequential.csv && printf "$out s\n"

printf "100,000,000 integers"
out=$(srun bin/sequential -c -s 100000000 -e 123)
printf "$out," >> ./output/sequential/sequential.csv && printf "$out s\n"

printf "500,000,000 integers"
out=$(srun bin/sequential -c -s 500000000 -e 123)
printf "$out," >> ./output/sequential/sequential.csv && printf "$out s\n"

printf "1,000,000,000 integers"
out=$(srun bin/sequential -c -s 1000000000)
printf "$out\n" >> ./output/sequential/sequential.csv && printf "$out s\n"
