#!/bin/bash
#SBATCH -n 2
#SBATCH -N 2
#SBATCH --ntasks-per-node=1
srun PA1 1000 1000
