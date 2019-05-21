##
# @file      makefile
# @author    Mitch Richling <https://www.mitchr.me/>
# @Copyright Copyright 1997,2014 by Mitch Richling.  All rights reserved.
# @brief     Simple make file to build the examples in this directory.@EOL
# @Keywords  
# @Std       GenericMake
#
#            
#            
 
TARGLC = main

# Put your compiler and basic compile options here
CC       = gcc
CFLAGS   = -Wall

# Put your Fortran 77 LAPACK and BLAS compile and link options here!
# What is below works on my stock Debian box, and works on my OS X
# 10.9.2 system when I comment out the first three and uncomment
# APLKRZ.
BLLIB  = -lblas
LPLIB  = -llapacke
LPINC  = -I/usr/include/atlas
#APLKRZ  = -framework Accelerate 

# You will need a Fortran compiler for the TARG*F targets.
TARGETS = $(TARGLC) 

all : $(TARGETS)
	@echo Make Complete

lc : main.c
	$(CC) $(CFLAGS) main.c -lm $(BLLIB)  $(LPLIB) -o main

clean :
	rm -rf a.out *~ *.bak $(TARGLC)
