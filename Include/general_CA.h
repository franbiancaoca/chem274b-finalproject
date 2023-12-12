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

enum class Genotype
{
    // Representing state of alleles
    HomozygousDominant,
    Heterozygous,
    Recessive
};
using Allele = Genotype;

class CA_model
{
protected:
    int rows, columns;                               // Rows and columns for dimensions
    int size;                                        // Size of CA model
    std::vector<std::vector<Genotype>> allele_data; // Vector that will hold the allele data for the grid
    std::string genotype;                            // Genotype
    function<Genotype(Genotype)> straight_conditional;                            // Straight Conditional Transition Rule
    function<Genotype(Genotype, const vector<Genotype> &)> conditional_neighbor; // Conditional Neighbor Rule
    function<Genotype(const vector<Genotype> &)> majority_rule;                   // Majority Rule

public:
    // Default Constructor
    CA_model();

    // Grid Setup
    int CA_setup_dimension(int ndims, int ndim1, int ndim2);

    // Parametrized Constructor (Using Grid Dimensions)
    CA_model(int ndims, int dim1, int dim2);

    // Neighborhood Setup
    std::vector<Genotype> setup_vonneumann(int x, int y);

    // Setup Genotype
    std::string setup_states(std::string state);

    // Initial Configuration
    int CA_init_cond(int x_state, double prob);

    // Setup Rules
    void set_straight_conditional(function<Genotype(Genotype)> rule);
    void set_conditional_neighbor(function<Genotype(Genotype, const vector<Genotype> &)> rule);
    void set_majority_rule(function<Genotype(const vector<Genotype> &)> rule);

    // Updates the grid based on rules
    void update_grid();
};

// Operations that determine the genotype of the offspring
Genotype determine_genotype(Genotype parent1, Genotype parent2);

// Initialization of population with a given starting allele frequency
std::vector<Genotype> initialize_population(int size, double recessive_frequency);

// Simulates one generation and this is the
// implementation of the VON NEUMAN NEIGHBORHOOD!
std::vector<Genotype> simulate_generation(const std::vector<Genotype> &current_population);

std::function<Genotype(Genotype, const std::vector<Genotype> &)> get_generation_rule();
