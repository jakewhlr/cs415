#!/bin/bash
#SBATCH -n 4
#SBATCH --output=output/parallel/parallel.log
#SBATCH --mail-user=jakewheeler@nevada.unr.edu
#SBATCH --mail-type=ALL
#SBATCH --time=00:20:00
printf "60x60"
out=$(srun --mpi=pmi2 bin/parallel -c -s 60 -e 123)
printf "$out," >> ./output/parallel/parallel.csv && printf " $out s\n"

printf "120x120"
out=$(srun --mpi=pmi2 bin/parallel -c -s 120 -e 123)
printf "$out," >> ./output/parallel/parallel.csv && printf " $out s\n"

printf "240x240"
out=$(srun --mpi=pmi2 bin/parallel -c -s 240 -e 123)
printf "$out," >> ./output/parallel/parallel.csv && printf " $out s\n"

printf "300x300"
out=$(srun --mpi=pmi2 bin/parallel -c -s 300 -e 123)
printf "$out," >> ./output/parallel/parallel.csv && printf " $out s\n"

printf "420x420"
out=$(srun --mpi=pmi2 bin/parallel -c -s 420 -e 123)
printf "$out," >> ./output/parallel/parallel.csv && printf " $out s\n"

printf "540x540"
out=$(srun --mpi=pmi2 bin/parallel -c -s 540 -e 123)
printf "$out," >> ./output/parallel/parallel.csv && printf " $out s\n"

printf "660x660"
out=$(srun --mpi=pmi2 bin/parallel -c -s 660 -e 123)
printf "$out\n" >> ./output/parallel/parallel.csv && printf " $out s\n"

printf "780x780"
out=$(srun --mpi=pmi2 bin/parallel -c -s 780 -e 123)
printf "$out\n" >> ./output/parallel/parallel.csv && printf " $out s\n"

printf "900x900"
out=$(srun --mpi=pmi2 bin/parallel -c -s 900 -e 123)
printf "$out\n" >> ./output/parallel/parallel.csv && printf " $out s\n"

printf "1020x1020"
out=$(srun --mpi=pmi2 bin/parallel -c -s 1020 -e 123)
printf "$out\n" >> ./output/parallel/parallel.csv && printf " $out s\n"
