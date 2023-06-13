#!/bin/bash
# number of compute nodes
#SBATCH -N 1
#SBATCH --ntasks-per-node 128
#SBATCH -t 00:06:00
#SBATCH -p dev_q
#SBATCH -A cmda3634_rjh
#SBATCH -o sum.out

# Submit this file as a job request with
# sbatch submission.sh

# Change to the directory from which the job was submitted
cd $SLURM_SUBMIT_DIR

# Unload all except default modules
module reset

# Load the modules you need
module load gcc

# Compile (this may not be necessary if the program is already built)
gcc -o ompSum.out ompSum.c -lm -fopenmp

# Find out the number of threads from SLURM
export OMP_NUM_THREADS=$SLURM_NTASKS
export OMP_PROC_BIND=true
export OMP_DYNAMIC=false

# Print the number of threads for future reference
echo "Different ways to sum entries in an array with OpenMP" 

# Run the program. Don't forget arguments!

N=80000000

./ompSum.out 1 $N
./ompSum.out 2 $N
./ompSum.out 4 $N
./ompSum.out 8 $N
./ompSum.out 16 $N
./ompSum.out 32 $N
./ompSum.out 64 $N
./ompSum.out 128 $N

# The script will exit whether we give the "exit" command or not.
exit
