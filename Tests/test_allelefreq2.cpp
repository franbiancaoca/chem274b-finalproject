// CHEM 274B: Software Engineering Fundamentals for Molecular Sciences
// Creator: Francine Bianca Oca, Kassady Marasigan, Korede Ogundele
//
// This file contains the C++ testing code that uses the cellular automata
// general purpose library to represent allele frequency changes over generations of 
// a population. 

#include <iostream>
#include <vector>
#include <random>
#include <functional>
#include "general_CA.h"

int main()
{
    int population_size = 100;   // Example population size
    double recessive_freq = 0.3; // Example recessive allele frequency

    // Create a 2D grid with 'population_size' as width and height
    CA_model model(2, population_size, population_size);

    // Initialize the grid with a certain state and probability
    model.CA_init_cond(static_cast<int>(Phenotype::HomozygousRecessive), recessive_freq);

    // Assuming get_generation_rule() returns a valid function for the conditional neighbor rule
    model.set_conditional_neighbor(get_generation_rule());

    for (int generation = 0; generation < 100; ++generation)
    {
        std::cout << "Generation " << generation << ": ";
        model.update_grid();
        // Note: The display of counts is now handled within the update_grid() method in CA_model
    }

    return 0;
}
