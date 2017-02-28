#!/bin/bash
#SBATCH -n 2
#SBATCH -N 1
#SBATCH --output=./One_box.txt
#SBATCH --time=00:15:00
srun PA1 1000 1
