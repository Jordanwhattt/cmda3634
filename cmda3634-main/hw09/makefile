# set options for this machine
# specify which compilers to use for c and linking
cc	= gcc
LD	= gcc

# define variables
HDRDIR = ./

# optimization
OPTIM = -g

# compiler flags to be used (set to compile with debugging on)
CFLAGS = -I$(HDRDIR) $(OPTIM) -fopenmp 

# link flags to be used
LDFLAGS	= $(OPTIM) -fopenmp

# libraries to be linked in
LIBS	=  -lm

# header files to be counted as dependencies
INCLUDES = 

# directory for source files
SRCDIR = ./

# types of files we are going to construct rules for
.SUFFIXES: .c

# rule for .c files
.c.o: $(INCLUDES) makefile
	$(cc) $(CFLAGS) -o $*.o -c $*.c 

# library objects
VOBJS = pi.o

# what to do if user types "make pi.out"
pi.out: $(VOBJS) $(INCLUDES) makefile
	$(LD) $(LDFLAGS) -o pi.out $(VOBJS) $(LIBS)


# what to do if user types "make clean"
clean:
	rm *.o pi.out

