#!/bin/bash
#SBATCH -n 1
#SBATCH --output=output/parallel/parallel.log
#SBATCH --mail-user=jakewheeler@nevada.unr.edu
#SBATCH --mail-type=ALL
#SBATCH --time=00:20:00
printf "60x60"
out=$(srun bin/parallel -c -s 60 -e 123)
printf "$out," >> ./output/parallel/parallel.csv && printf " $out s,"

printf "120x120"
out=$(srun bin/parallel -c -s 120 -e 123)
printf "$out," >> ./output/parallel/parallel.csv && printf " $out s,"

printf "240x240"
out=$(srun bin/parallel -c -s 240 -e 123)
printf "$out," >> ./output/parallel/parallel.csv && printf " $out s,"

printf "300x300"
out=$(srun bin/parallel -c -s 300 -e 123)
printf "$out," >> ./output/parallel/parallel.csv && printf " $out s,"

printf "420x420"
out=$(srun bin/parallel -c -s 420 -e 123)
printf "$out," >> ./output/parallel/parallel.csv && printf " $out s,"

printf "540x540"
out=$(srun bin/parallel -c -s 540 -e 123)
printf "$out," >> ./output/parallel/parallel.csv && printf " $out s,"

printf "660x660"
out=$(srun bin/parallel -c -s 660 -e 123)
printf "$out\n" >> ./output/parallel/parallel.csv && printf " $out s,"

printf "780x780"
out=$(srun bin/parallel -c -s 780 -e 123)
printf "$out\n" >> ./output/parallel/parallel.csv && printf " $out s,"

printf "900x900"
out=$(srun bin/parallel -c -s 900 -e 123)
printf "$out\n" >> ./output/parallel/parallel.csv && printf " $out s,"

printf "1020x1020"
out=$(srun bin/parallel -c -s 1020 -e 123)
printf "$out\n" >> ./output/parallel/parallel.csv && printf " $out s\n"