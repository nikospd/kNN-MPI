# ####################################################################
# 
#			   C/C++ Makefile
# 
# Adapted from
#  D.Floros' template and
#  http://www.cs.swarthmore.edu/~newhall/unixhelp/howto_makefiles.html
#  
# ####################################################################
# 
# 'make'        build executable file 'main'
# 'make lib'	build the libraries .a
# 'make clean'  removes all .o and executable files
#

# define the shell to bash
SHELL := /bin/bash

# define the C/C++ compiler to use,default here is clang
CC = gcc
MPI = mpicc
# define compile-time flags
CFLAGS = -O3 -Wall -g

# define any directories containing header files
INCLUDES = -I./inc

# define library paths in addition to /usr/lib
#   if I wanted to include libraries not in /usr/lib specify
#   their path using -Lpath, something like:
LDFLAGS =
mpiP_root = /home/papamitsos93/Downloads/mpiP-3.4.1
# define any libraries to link into executable -L${mpiP_root}/lib -lmpiP -lm -lbfd -liberty -lunwind
LIBS = -L${mpiP_root}/lib -lmpiP -lm -lbfd -liberty -lunwind

# define the source file for the library
SRCs = knnring_sequential
SRC = knnring

# define directories for source files and libraries
SRCDIR = src
LIBDIR = lib

# define vpath to look for missing source files
VPATH = src

# define the different possible executables | sync async
TYPES = sync async

# define the executable file  name
MAIN_S = sequential_main
MAIN_MPI = mpi_main
# call everytime
.PRECIOUS: %.a

all: $(addprefix $(MAIN_MPI)_, $(TYPES)) $(addprefix $(MAIN_S)_, $(SRC))
# all: $(addprefix $(MAIN_S)_, $(SRC))


lib: $(addsuffix .a, $(addprefix $(SRC)_, $(TYPES))) $(addsuffix .a,  $(SRCs))
# lib: $(addsuffix .a,  $(SRCs))


$(MAIN_S)_%: $(MAIN_S).c $(SRCs).a
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $(word 1,$^) $(LIBDIR)/$(word 2,$^) $(LDFLAGS) $(LIBS) 

$(MAIN_MPI)_%: $(MAIN_MPI).c $(SRC)_%.a $(SRCs).a
	$(MPI) $(CFLAGS) $(INCLUDES) -o $@ $(word 1,$^) $(LIBDIR)/$(word 2,$^) $(LIBDIR)/$(word 3,$^) $(LDFLAGS) $(LIBS) 

# this is a suffix replacement rule for building .o's from .c's
# it uses automatic variables $<: the name of the prerequisite of
# the rule(a .cpp file) and $@: the name of the target of the rule (a .o file)

.o.a:
	ar rcs $(LIBDIR)/$@ $<

# (see the gnu make manual section about automatic variables)
.c.o:
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ -c $<

clean:
	$(RM) $(SRCDIR)/*.o *~ $(addprefix $(MAIN_MPI)_, $(TYPES)) $(addprefix $(MAIN_S)_, $(SRC)) $(LIBDIR)/$(SRC)*.a
	$(RM) $(SRCDIR)/*.o *~ $(addprefix $(MAIN_S)_, $(SRC)) $(LIBDIR)/$(SRC)*.a