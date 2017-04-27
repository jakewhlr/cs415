#!/bin/bash
#SBATCH -n 1
#SBATCH --output=output/parallel/parallel.log
#SBATCH --mail-user=jakewheeler@nevada.unr.edu
#SBATCH --mail-type=ALL
#SBATCH --time=00:20:00
printf "100x100"
out=$(srun bin/parallel -c -s 100 -e 123)
printf "$out," >> ./output/parallel/parallel.csv && printf " $out s\n"

printf "500x500"
out=$(srun bin/parallel -c -s 500 -e 123)
printf "$out," >> ./output/parallel/parallel.csv && printf " $out s\n"

printf "1000x1000"
out=$(srun bin/parallel -c -s 1000 -e 123)
printf "$out," >> ./output/parallel/parallel.csv && printf " $out s\n"

printf "1500x1500"
out=$(srun bin/parallel -c -s 1500 -e 123)
printf "$out," >> ./output/parallel/parallel.csv && printf " $out s\n"

printf "2000x2000"
out=$(srun bin/parallel -c -s 2000 -e 123)
printf "$out," >> ./output/parallel/parallel.csv && printf " $out s\n"

printf "2500x2500"
out=$(srun bin/parallel -c -s 2500 -e 123)
printf "$out," >> ./output/parallel/parallel.csv && printf " $out s\n"

printf "3000x3000"
out=$(srun bin/parallel -c -s 3000 -e 123)
printf "$out\n" >> ./output/parallel/parallel.csv && printf " $out s\n"
