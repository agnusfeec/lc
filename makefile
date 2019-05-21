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

# Put your compiler and basic compile options here
CC       = gcc
CFLAGS   = -Wall

# LAPACK and BLAS compile and link options here!
BLLIB  = -lblas
LPLIB  = -llapacke
LPINC  = -I/usr/include/atlas

TARGETS = $(TARGLC) 

all : $(TARGETS)
	@echo Make Complete

main : main.c
	$(CC) $(CFLAGS) main.c -lm $(BLLIB)  $(LPLIB) -o main

clean :
	rm -rf a.out *~ *.bak $(TARGLC)
