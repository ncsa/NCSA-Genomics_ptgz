executables = bin/ptgz
objects = obj/timer.o obj/tarentry.o obj/mpitar.o obj/ptgz-mpi.o
sources = src/timer.cc src/tarentry.cc src/mpitar.cc src/ptgz-mpi.cpp

### Choose an appropriate compiler
### Choose appropriate compiler flags

## MPI C++ Compiler and Flags
CC = mpic++

## GCC
CFLAGS := -std=c++11 -fopenmp -O3

## Intel
# CFLAGS := -std=c++11 -openmp -O3

## Cray C++ Compiler and Flags
# CC = CC
# CFLAGS := -std=c++11 -fopenmp -O3


all: ptgz

clean:
	rm -rf bin/ obj/ mpitar/mpitar

ptgz: $(sources) $(objects) | bin bin/mpitar
	$(CC) $(CFLAGS) -o $(executables) $(objects)

obj/%.o: src/%.cpp | obj
	$(CC) $(CFLAGS) -c -o $@ $<

obj:
	mkdir -p $@

bin:
	mkdir -p $@

set-permissions:
	chmod -R 751 bin/

install: set-permissions
	cp $(executables) /bin/ptgz
