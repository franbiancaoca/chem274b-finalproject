# Chem 274B: Software Engineering Fundamentals for
#            Molecular Sciences 
# 
# Creator:  Francine Bianca Oca, Kassady Marasigan, Korede Ogundele
# Created: 11/23/2023
#
# This makefile creates object files that are executable 
# They test the functionalities in Week7/Source/Datatypes
# After creating the executable files they are moved to 
# the ../Bin subdirectory

# GNU C++ Compiler
CPP         = g++      

# compiler flags -g debug, -O2 optimized version -c create a library object
CPPFLAGS    = -O3 -o

# The directory where the header file for linkage is stored
INC_DIR = ../Include

# The directory where all object/executables files are going to be moved after creation
LIB_DIR     = ../Lib
BIN_DIR     = ../Bin

# The next line contains the list of object files created by this Makefile.
EXECUTABLES = test_adjmatrix test_adjlist test_bfs test_dmatrix

# Tests the BFS implementations
test_allelefreq: $(INC_DIR)/cellularautomata.h
	$(CPP) $(CPPFLAGS) test_allelefreq test_allelefreq.cpp \
	-I$(INC_DIR) -L$(LIB_DIR) -lcellularautomata
	mv test_allelefreq $(BIN_DIR)