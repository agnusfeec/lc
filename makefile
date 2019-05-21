##
# @file      makefile
# @author    Agnus Horta 
# @Copyright Copyright 2019 by Agnus Horta.  All rights reserved.
# @brief     Simple make file to build the Linear Classifier.@EOL
# @Keywords  
# @Std       GenericMake
#
#            
#            
 
TARGLC = main
TRAGMN = mnist

# Put your compiler and basic compile options here
CPP      = g++
CC       = gcc
CFLAGS   = -Wall

# OPENCV options here
OPENCV = `pkg-config --cflags --libs opencv`

# LAPACK and BLAS compile and link options here!
BLLIB  = -lblas
LPLIB  = -llapacke
LPINC  = -I/usr/include/atlas

TARGETS = $(TARGLC) 

all : $(TARGETS)
	@echo Make Complete

main : main.c
	$(CC) $(CFLAGS) main.c -lm $(BLLIB)  $(LPLIB) -o main

mnist : mnist.c
	$(CPP) $(CFLAGS) mnist.c -o mnist $(OPENCV)

clean :
	rm -rf a.out *~ *.bak $(TARGLC) $(TRAGMN)
