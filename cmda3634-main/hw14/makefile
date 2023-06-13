#name you want for the executable file
EXECUTABLE = main.out

# library objects (change this part if you change your filenames)
VOBJS = cyclicPassing.o

# This is the first rule, so it will be used when user types "make"
# Since "output" never exists, Make will build the executable
output: $(EXECUTABLE)

COMPILER = mpicc

# header directory
HDRDIR = ./

# optimization flags
OPTIM = -O0

# debugger flags if desired (often you'll want -g)
DBUG =

# compiler flags
CFLAGS = -I $(HDRDIR) $(OPTIM) $(DBUG)

# linker flags
LDFLAGS	= $(OPTIM) $(DBUG)

# libraries to be linked in (often you'll want -lm)
LIBS = -lm

# header files to be counted as dependencies
INCLUDES =

# directory for source files
SRCDIR = ./

# types of files we are going to state rules for
.SUFFIXES: .c

# Rule specifying that .o files depend on "included" files and the makefile
# This rule also teaches Make how to create .o files
.c.o: $(INCLUDES) makefile
	$(COMPILER) $(CFLAGS) -o $*.o -c $*.c 

# what to do if user types "make clean"
clean:
	rm -f *.o $(EXECUTABLE)

$(EXECUTABLE): $(VOBJS) $(INCLUDES) makefile
	$(COMPILER) $(LDFLAGS) -o $(EXECUTABLE) $(VOBJS) $(LIBS)
