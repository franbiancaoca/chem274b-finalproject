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

enum class Phenotype
{
    // Representing state of alleles
    HomozygousDominant,
    Heterozygous,
    HomozygousRecessive
};
using Allele = Phenotype;

class CA_model
{
protected:
    int rows, columns;                               // Rows and columns for dimensions
    int size;                                        // Size of CA model
    std::vector<std::vector<Phenotype>> allele_data; // Vector that will hold the allele data for the grid
    std::string genotype;                            // Genotype
    function<Phenotype(Phenotype)> straight_conditional;                            // Straight Conditional Transition Rule
    function<Phenotype(Phenotype, const vector<Phenotype> &)> conditional_neighbor; // Conditional Neighbor Rule
    function<Phenotype(const vector<Phenotype> &)> majority_rule;                   // Majority Rule

public:
    // Default Constructor
    CA_model();

    // Grid Setup
    int CA_setup_dimension(int ndims, int ndim1, int ndim2);

    // Parametrized Constructor (Using Grid Dimensions)
    CA_model(int ndims, int dim1, int dim2);

    // Neighborhood Setup
    std::vector<Phenotype> setup_vonneumann(int x, int y);

    // Setup Genotype
    std::string setup_states(std::string state);

    // Initial Configuration
    int CA_init_cond(int x_state, double prob);

    // Setup Rules
    void set_straight_conditional(function<Phenotype(Phenotype)> rule);
    void set_conditional_neighbor(function<Phenotype(Phenotype, const vector<Phenotype> &)> rule);
    void set_majority_rule(function<Phenotype(const vector<Phenotype> &)> rule);

    // Updates the grid based on rules
    void update_grid();
};

// Operations that determine the phenotype of the offspring
Phenotype determine_phenotype(Phenotype parent1, Phenotype parent2);

// Initialization of population with a given starting allele frequency
std::vector<Phenotype> initialize_population(int size, double recessive_frequency);

// Simulates one generation and this is the
// implementation of the VON NEUMAN NEIGHBORHOOD!
std::vector<Phenotype> simulate_generation(const std::vector<Phenotype> &current_population);

std::function<Phenotype(Phenotype, const std::vector<Phenotype> &)> get_generation_rule();
