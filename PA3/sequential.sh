#!/bin/bash
#SBATCH -n 1
#SBATCH --output=output/sequential/sequential.log
#SBATCH --mail-user=jakewheeler@nevada.unr.edu
#SBATCH --mail-type=ALL
#SBATCH --time=00:5:00
printf "10,000,000 integers"
test1=$(srun bin/sequential input/10000000.txt)
printf "$test1," >> ./output/sequential/sequential.csv && printf "$test1 s\n"
