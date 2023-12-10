#include <iostream>
#include <vector>
#include <random>
#include "general_CA.h"

// RULES: Operations that determine the phenotype of the offspring
Phenotype determine_phenotype(Phenotype parent1, Phenotype parent2)
{
    // If both parents are homozygous dominant, 
    // 100% chance offspring will be homozygous dominant
    if (parent1 == Phenotype::HomozygousDominant && parent2 == Phenotype::HomozygousDominant)
    {
        return Phenotype::HomozygousDominant;
    }

    // If both parents are recessive, 
    // 100% chance offspring will be recessive
    else if (parent1 == Phenotype::Recessive && parent2 == Phenotype::Recessive)
    {
        return Phenotype::Recessive;
    }

    // If one parent is homozygous dominant and other is recessive, 
    // 100% chance offspring will be heterozygous
    else if (parent1 == Phenotype::HomozygousDominant && parent2 == Phenotype::Recessive)
    {
        return Phenotype::Heterozygous;
    }

    // If both parents are heterozygous, 
    // 50% chance offspring will be heterozygous, 25% homo dominant and 25% homo recessive
    else
    {
        // Generate random number from 0 to 1
        double rand_value = ((double)rand() / RAND_MAX);

        // 50% chance offspring will be heterozygous
        if (rand_value < 0.5)
        {
            return Phenotype::Heterozygous;
        }
        // 25% chance offspring will be homozygous dominant
        else if (rand_value < 0.75)
        {
            return Phenotype::HomozygousDominant;
        }
        // 25% chance offspring will be recessive
        else
        {
            return Phenotype::Recessive;
        }
    }
}

// INIT: Initialization of population with a given starting allele frequency
std::vector<Phenotype> initialize_population(int size, double recessive_frequency)
{
    std::vector<Phenotype> population(size);
    for (Phenotype &individual : population)
    {
        double rand_value = static_cast<double>(rand()) / RAND_MAX;
        if (rand_value < recessive_frequency)
        {
            individual = Phenotype::Recessive;  // Offspring is recessive
        }
        else if (rand_value < 2 * recessive_frequency)
        {
            individual = Phenotype::Heterozygous;   // Ofspring is heterozygous
        }
        else
        {
            individual = Phenotype::HomozygousDominant; // Offspring is homozygous dominant
        }
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
        Phenotype right_parent = current_population[(i + 1) % current_population.size()]; // BOUNDARY
        next_generation[i] = determine_phenotype(left_parent, right_parent);
    }

    return next_generation;
}
