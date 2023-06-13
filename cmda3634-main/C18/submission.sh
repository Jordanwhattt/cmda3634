#!/bin/bash
#SBATCH --nodes 1
#SBATCH --ntasks 32
#SBATCH -t 00:05:00
#SBATCH -p dev_q
#SBATCH -A cmda3634_rjh
#SBATCH -o slurm-timing.out

# Go to the directory where the job was submitted
cd $SLURM_SUBMIT_DIR

echo "Core distribution on nodes:"
echo $SLURM_TASKS_PER_NODE

# Unload all except default modules
module reset

# Load the modules you need
module load gcc

# Build the executable (if you haven't already)
make strongScalingStudy.out

# OpenMP settings
export OMP_NUM_THREADS=$SLURM_NTASKS
export OMP_PROC_BIND=true
export OMP_DYNAMIC=false

arraysize=600000

./strongScalingStudy.out 1   $arraysize
./strongScalingStudy.out 2   $arraysize
./strongScalingStudy.out 4   $arraysize
./strongScalingStudy.out 8   $arraysize
./strongScalingStudy.out 16  $arraysize
./strongScalingStudy.out 32  $arraysize
./strongScalingStudy.out 64  $arraysize
./strongScalingStudy.out 128 $arraysize

# The script will exit whether we give the "exit" command or not.
exit

