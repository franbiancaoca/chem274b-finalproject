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
    : rows(0), columns(0), size(0), genotype("") {}

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
    allele_data.resize(rows, std::vector<Phenotype>(columns, Phenotype::HomozygousDominant));
    return 0;
}

// Parametrized Constructor (Using Grid Dimensions)
CA_model::CA_model(int ndims, int dim1, int dim2)
{
    CA_setup_dimension(ndims, dim1, dim2);
}

// Neighborhood Setup
std::vector<Phenotype> CA_model::setup_vonneumann(int x, int y)
{
    std::vector<Phenotype> neighbors;
    std::vector<std::pair<int, int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

    for (const auto &dir : directions)
    {
        int nx = x + dir.first;
        int ny = y + dir.second;

        if (nx >= 0 && nx < rows && ny >= 0 && ny < columns)
        {
            neighbors.push_back(allele_data[nx][ny]);
        }
    }
    return neighbors;
}

// Setup Genotype
std::string CA_model::setup_states(std::string state)
{
    std::string HomozygousDominant = "GG";
    std::string Heterozygous = "Gg";
    std::string HomozygousRecessive = "gg";

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
            allele_data[i][j] = dist(gen) ? static_cast<Phenotype>(state) : Phenotype::HomozygousDominant;
        }
    }

    return 0; // Initialization is a success!
}

// Setup Rules
void CA_model::set_straight_conditional(std::function<Phenotype(Phenotype)> rule)
{
    straight_conditional = rule;
}

void CA_model::set_conditional_neighbor(std::function<Phenotype(Phenotype, const std::vector<Phenotype> &)> rule)
{
    conditional_neighbor = rule;
}

void CA_model::set_majority_rule(std::function<Phenotype(const vector<Phenotype> &)> rule)
{
    majority_rule = rule;
}

// Updates the grid based on rules
void CA_model::update_grid()
{
    // Variable to store counts
    int count_homozygous_recessive = 0;
    int count_heterozygous = 0;
    int count_homozygous_dominant = 0;
    std::vector<std::vector<Phenotype>> grid = allele_data;
    updated_state = current_state;   // Use current_state as the base for updating

    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < columns; ++j)
        {
            Phenotype current_state_cell = current_state[i][j];
            std::vector<Phenotype> neighbors = setup_vonneumann(i, j);

            // Apply rules using the current state
            if (straight_conditional)
            {
                updated_state[i][j] = straight_conditional(current_state_cell);
            }
            if (conditional_neighbor)
            {
                updated_state[i][j] = conditional_neighbor(current_state_cell, neighbors);
            }
            if (majority_rule)
            {
                updated_state[i][j] = majority_rule(neighbors);
            }

            // Count the phenotypes for output
            switch (updated_state[i][j])
            {
            case Phenotype::HomozygousRecessive:
                count_homozygous_recessive++;
                break;
            case Phenotype::Heterozygous:
                count_heterozygous++;
                break;
            case Phenotype::HomozygousDominant:
                count_homozygous_dominant++;
                break;
            }
        }
    }

    allele_data = grid;

    // Print counts or handle as needed
    std::cout << "Homozygous Dominant: " << count_homozygous_dominant
              << ", Heterozygous: " << count_heterozygous
              << ", Homozygous Recessive: " << count_homozygous_recessive << std::endl;

    // Swap the grids making the updated_state the current_state for the next iteration
    std::swap(current_state, updated_state);
}