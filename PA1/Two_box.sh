#!/bin/bash
#SBATCH -n 2
#SBATCH -N 2
#SBATCH --output=./Two_box.txt
#SBATCH --ntasks-per-node=1
#SBATCH --time=00:15:00
srun PA1 1000 1
