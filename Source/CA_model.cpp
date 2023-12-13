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
    allele_data.resize(rows, std::vector<Genotype>(columns, Genotype::HomozygousDominant));
    return 0;
}

// Parametrized Constructor (Using Grid Dimensions)
CA_model::CA_model(int ndims, int dim1, int dim2)
{
    CA_setup_dimension(ndims, dim1, dim2);
}

// Neighborhood Setup
std::vector<Genotype> CA_model::setup_vonneumann(int x, int y)
{
    std::vector<Genotype> neighbors;
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
            allele_data[i][j] = dist(gen) ? static_cast<Genotype>(state) : Genotype::HomozygousDominant;
        }
    }

    return 0; // Initialization is a success!
}

// Setup Rules
void CA_model::set_straight_conditional(std::function<Genotype(Genotype)> rule)
{
    straight_conditional = rule;
}

void CA_model::set_conditional_neighbor(std::function<Genotype(Genotype, const std::vector<Genotype> &)> rule)
{
    conditional_neighbor = rule;
}

void CA_model::set_majority_rule(std::function<Genotype(const vector<Genotype> &)> rule)
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
    std::vector<std::vector<Genotype>> grid = allele_data;

    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < columns; ++j)
        {
            Genotype current_state = allele_data[i][j];
            std::vector<Genotype> neighbors = setup_vonneumann(i, j);

            // Apply rules
            if (straight_conditional)
            {
                grid[i][j] = straight_conditional(current_state);
            }
            if (conditional_neighbor)
            {
                grid[i][j] = conditional_neighbor(current_state, neighbors);
            }
            if (majority_rule)
            {
                grid[i][j] = majority_rule(neighbors);
            }

            switch (grid[i][j])
            {
            case Genotype::Recessive:
                count_homozygous_recessive++;
                break;
            case Genotype::Heterozygous:
                count_heterozygous++;
                break;
            case Genotype::HomozygousDominant:
                count_homozygous_dominant++;
                break;
            }
        }
    }

    allele_data = grid;

    std::cout << "Homozygous Dominant: " << count_homozygous_dominant
              << ", Heterozygous: " << count_heterozygous
              << ", Recessive: " << count_homozygous_recessive << std::endl;
}