// CHEM 274B: Software Engineering Fundamentals for Molecular Sciences
// Creator: Francine Bianca Oca, Kassady Marasigan, Korede Ogundele
//
// This file is the header file that contains the API linker
// for the general purpose cellular automata library. 

#pragma once // Ensures that this file is only included once
             // during compilation
#include <string>
#include <iostream>
#include <vector>
#include <utility>
#include <random>
#include <functional>
using namespace std;

enum class CellState
{
    // Representing state of alleles
    Homozygous_Dominant,
    Heterozygous_Dominant
};
using Allele = CellState;

class CA_model
{
protected:
    int rows, columns;                               // Rows and columns for dimensions
    int size;                                        // Size of CA model
    std::vector<std::vector<CellState> > allele_data; // Vector that will hold the allele data for the grid
    std::string genotype;                            // Genotype
    function<CellState(CellState)> straight_conditional; // Straight Conditional Transition Rule
    function<CellState(CellState, const vector<CellState> &)> conditional_neighbor; // Conditional Neighbor Rule
    function<CellState(const vector<CellState> &)> majority_rule; // Majority Rule 

public:
    // Default Constructor
    CA_model();

    // Grid Setup
    int CA_setup_dimension(int ndims, int ndim1, int ndim2);

    // Parametrized Constructor (Using Grid Dimensions)
    CA_model(int ndims, int dim1, int dim2);

    // Neighborhood Setup
    std::vector<int> setup_vonneumann(int x, int y);

    // Setup Genotype
    std::string setup_states(std::string state);

    // Initial Configuration
    int CA_init_cond(int x_state, double prob);

    // Setup Rules
    void set_straight_conditional(function<CellState(CellState)> rule);
    void set_conditional_neighbor(function<CellState(CellState, const vector<CellState> &)> rule);
    void set_majority_rule(function<CellState(const vector<CellState> &)> rule);
};