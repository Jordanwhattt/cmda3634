#!/bin/bash
#SBATCH --nodes 1
#SBATCH --ntasks 8
#SBATCH -t 00:05:00
#SBATCH -p dev_q
#SBATCH -A cmda3634_rjh
#SBATCH -o slurm-timing.out

# Go to the directory where the job was submitted
cd $SLURM_SUBMIT_DIR

echo "THIS MUST BE RUN ON CASCADES TO USE THE MESSAGE LOGGING (MPE2) TOOLS"

echo "Core distribution on nodes:"
echo $SLURM_TASKS_PER_NODE

# Unload all except default modules
module reset

# load the cascades modules for MPI to use MPE2 message logging
module load gcc/6.1.0  openmpi/3.1.2  jdk/1.8.0   mpe2/2.4.9b

# Build the executable (if you haven't already)
make clean
make mpiHelloWorld.out


arraysize=600000

echo "nranks=1"
mpiexec -n 1   ./mpiHelloWorld.out $arraysize
echo "nranks=2"
mpiexec -n 2   ./mpiHelloWorld.out $arraysize
echo "nranks=4"
mpiexec -n 4   ./mpiHelloWorld.out $arraysize
echo "nranks=8"
mpiexec -n 8   ./mpiHelloWorld.out $arraysize


# The script will exit whether we give the "exit" command or not.
exit

