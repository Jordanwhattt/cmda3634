# define variables
HDRDIR  = ./

# set options for this machine
# specify which compilers to use for c and linking
CC	= gcc
LD	= gcc
NCC	= nvcc
NLD	= nvcc

# compiler flags to be used (set to compile with debugging on)
CFLAGS = -I$(HDRDIR) -O3 -fopenmp
NCFLAGS = -I$(HDRDIR) -O3 -arch=sm_60  --use_fast_math

# link flags to be used 
LDFLAGS	= -fopenmp
NLDFLAGS =

# libraries to be linked in
LIBS	=  -lpng -lm 

# types of files we are going to construct rules for
.SUFFIXES: .c .cu

# rule for .c files
.c.o:
	$(CC) $(CFLAGS) -o $*.o -c $*.c
.cu.o:
	$(NCC) $(NCFLAGS) -o $*.o -c $*.cu

# list of objects to be compiled
SOBJS    = serialMandelbrot.o png_util.o
COBJS    = cudaMandelbrot.o png_util.o

serial:$(SOBJS) 
	$(LD)  $(LDFLAGS) -o serialMandelbrot $(SOBJS) $(LIBS)

cuda:$(COBJS) 
	$(NLD)  $(NLDFLAGS) -o cudaMandelbrot $(COBJS) $(LIBS)


# what to do if user types "make clean"
clean : 
	rm -r $(NOBJS) $(COBJS) serialMandelbrot cudaMandelbrot
