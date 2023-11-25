# Chem 274B: Software Engineering Fundamentals for
#            Molecular Sciences 
# 
# Creator:  Francine Bianca Oca, Kassady Marasigan, Korede Ogundele
# Date Created: 11/23/2023
#
# Directory Path: CHEM274B-FINALPROJECT/Source
# This makefile creates objects and a library from CellularAutomata class.

# GNU C++ Compiler
CPP         = g++      # C++ Compuler

# compiler flags -g debug, -O2 optimized version -c create a library object
CPPFLAGS    = -O3 -c    

# The directory where the include files needed to create the library objects are
INC_DIR = ../Include

# The directory where all object files are going to moved afer creation
LIB_DIR     = ../Lib

# DATA_OBJS contains the current list of object files
DATA_OBJS = allelefreq.o

# DATA_LIB is the name of object library file that will contain all
# DATA_OBJS files
DATA_LIB = libcellularautomata.a 

# Use object files build a library object file.
# Compilation and creation of object file for adjacency list class
allelefreq.o: $(INC_DIR)/cellularautomata.h	
	$(CPP) $(CPPFLAGS) allelefreq.cpp -I$(INC_DIR)

# The following target creates a static library (a collection of
# linkable object files). After all the object files in DATA_OBJS have been archived
# in the library object file, they can be removed.
libcellularautomata.a: $(DATA_OBJS)
	ar ru $(DATA_LIB) $(DATA_OBJS) 
	mv $(DATA_LIB) $(LIB_DIR)
	rm $(DATA_OBJS)