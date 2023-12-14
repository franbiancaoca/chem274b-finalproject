# Chem 274B: Software Engineering Fundamentals for
#            Molecular Sciences 
# 
# Creator:  Francine Bianca Oca, Kassady Marasigan, Korede Ogundele
# Created: 11/23/2023
#
# This makefile creates object files that are executable 
# After creating the executable files they are moved to 
# the ../Bin subdirectory

# GNU C++ Compiler
CPP         = g++   

# compiler flags -g debug, -O2 optimized version -c create a library object
CPPFLAGS    = -O3 -std=c++11 -o

# The directory where the header file for linkage is stored
INC_DIR = ../Include

# The directory where all object/executables files are going to be moved after creation
LIB_DIR     = ../Lib
BIN_DIR     = ../Bin

# Tests the allele frequency model
test_allelefreq: $(INC_DIR)/general_CA.h
	$(CPP) $(CPPFLAGS) test_allelefreq test_allelefreq.cpp \
	-I$(INC_DIR) -L$(LIB_DIR) -lcellularautomata
	mv test_allelefreq $(BIN_DIR)

test_allelefreq2: $(INC_DIR)/general_CA.h
	$(CPP) $(CPPFLAGS) test_allelefreq2 test_allelefreq2.cpp \
	-I$(INC_DIR) -L$(LIB_DIR) -lcellularautomata
	mv test_allelefreq2 $(BIN_DIR)

test_genotype: $(INC_DIR)/CA_library.h
	$(CPP) $(CPPFLAGS) test_genotype test_genotype.cpp \
	-I$(INC_DIR) -L$(LIB_DIR) -lcellularautomata
	mv test_genotype $(BIN_DIR)