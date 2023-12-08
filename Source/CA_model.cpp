// CHEM 274B: Software Engineering Fundamentals for Molecular Sciences
// Creator: Francine Bianca Oca, Kassady Marasigan, Korede Ogundele
//
// This file contains the general purpose library used to
// model cellular automata. For our case, this general purpose
// library will be used to model allele frequency changes over
// generations for a population.

#include <iostream>
#include <vector>
#include <random>
#include <functional>
#include "general_CA.h"

// Default Constructor
CA_model::CA_model()
    : rows(0), columns(0), size(0), genotype(0) {}

// Grid Setup
int CA_model::CA_setup_dimension(int ndims, int ndim1, int ndim2)
{
    if (ndims != 2)
    {
        cerr << "Only 2D grids are supported." << endl;
        return -1;
    }
    columns = ndim1;
    rows = ndim2;
    size = rows * columns;
    allele_data.resize(rows, std::vector<CellState>(columns, CellState::Homozygous_Dominant));
    return 0;
}

// Parametrized Constructor (Using Grid Dimensions)
CA_model::CA_model(int ndims, int dim1, int dim2)
    : rows(0), columns(0), size(0), genotype(0)
{
    CA_setup_dimension(ndims, dim1, dim2);
}

// Neighborhood Setup
vector<int> CA_model::setup_vonneumann(int x, int y)
{
    std::vector<int> neighbors;
    vector<pair<int, int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

    for (auto &dir : directions)
    {
        int nx = x + dir.first;
        int ny = y + dir.second;

        // Boundary Conditions
        if (nx >= 0 && nx < rows && ny >= 0 && ny < columns)
        {
            neighbors.push_back(static_cast<int>(allele_data[nx][ny])); // Cast CellState to int
        }
    }
    return neighbors;
}

// Setup Genotype
std::string CA_model::setup_states(std::string state)
{
    std::string Homozygous_Dominant = "GG";
    std::string Heterozygous = "Gg";
    std::string Recessive = "gg";

    return 0;
}

// Initial Configuration
int CA_model::CA_init_cond(int state, double prob)
{
    if (rows == 0 || columns == 0)
    {
        cerr << "Grid dimensions are not set." << endl;
        return -1;
    }

    if (prob < 0.0 || prob > 1.0)
    {
        cerr << "Probability must be between 0.0 and 1.0." << endl;
        return -1;
    }

    std::random_device rd;                  
    std::mt19937 gen(rd());                 
    std::bernoulli_distribution dist(prob);

    // Iterate over each cell in the grid
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < columns; ++j)
        {
            if (dist(gen))
            { // With probability 'prob', set the cell to 'state'
                allele_data[i][j] = static_cast<CellState>(state);
            }
            // Else -> default state
        }
    }

    return 0; // Initialization is a success!
}

// Setup Rules
void CA_model::set_straight_conditional(function<CellState(CellState)> rule)
{
    straight_conditional = rule;
}

void CA_model::set_conditional_neighbor(function<CellState(CellState, const vector<CellState> &)> rule)
{
    conditional_neighbor = rule;
}

void CA_model::set_majority_rule(function<CellState(const vector<CellState> &)> rule)
{
    majority_rule = rule;
}