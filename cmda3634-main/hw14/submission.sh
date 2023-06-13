#!/bin/bash
#SBATCH --nodes 1
#SBATCH --ntasks 128
#SBATCH -t 00:05:00
#SBATCH -p dev_q
#SBATCH -A cmda3634_rjh
#SBATCH -o slurm-timing.out

# Go to the directory where the job was submitted
cd $SLURM_SUBMIT_DIR

# Unload all except default modules
module reset

# Load the modules you need
module load gcc
module load mpich/ge/gcc/64

# Build the executable (if you haven't already)
make clean
make main.out





echo "nranks=8"
mpiexec -n 8   ./main.out

#The script will exit whether we give the "exit" command or not.
exit

