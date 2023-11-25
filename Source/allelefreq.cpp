#include <iostream>
#include <vector>
#include <random>
#include "cellularautomata.h"

// Operations that determine the phenotype of the offspring
Phenotype determine_phenotype(Phenotype parent1, Phenotype parent2)
{
    // Both parents are recessive, offspring will be recessive
    if (parent1 == Phenotype::Recessive && parent2 == Phenotype::Recessive)
    {
        return Phenotype::Recessive;
    }
    // Both parents are dominant, 25% chance offspring is recessive
    else if (parent1 == Phenotype::Dominant && parent2 == Phenotype::Dominant)
    {
        return rand() % 4 == 0 ? Phenotype::Recessive : Phenotype::Dominant; // 1 in 4 chance for recessive
    }
    // One parent is dominant, other is recessive, 50% chance offspring is recessive
    else
    {
        return rand() % 2 == 0 ? Phenotype::Recessive : Phenotype::Dominant; // 1 in 2 chance for recessive
    }
}

// Initialization of population with a given starting allele frequency
std::vector<Phenotype> initialize_population(int size, double recessive_frequency)
{
    std::vector<Phenotype> population(size);
    for (Phenotype &individual : population)
    {
        individual = (static_cast<double>(rand()) / RAND_MAX < recessive_frequency) ? Phenotype::Recessive : Phenotype::Dominant;
    }
    return population;
}

// Simulates one generation and this is the
// implementation of the VON NEUMAN NEIGHBORHOOD!
std::vector<Phenotype> simulate_generation(const std::vector<Phenotype> &current_population)
{
    std::vector<Phenotype> next_generation(current_population.size());
    for (size_t i = 0; i < current_population.size(); ++i)
    {
        Phenotype left_parent = current_population[i];
        Phenotype right_parent = current_population[(i + 1) % current_population.size()]; // Wrap-around boundary condition
        next_generation[i] = determine_phenotype(left_parent, right_parent);
    }
    return next_generation;
}
