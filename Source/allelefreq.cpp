#include <iostream>
#include <vector>
#include <random>
#include "general_CA.h"

// RULES: Operations that determine the genotype of the offspring
Genotype determine_genotype(Genotype parent1, Genotype parent2)
{
    // If both parents are homozygous dominant, 
    // 100% chance offspring will be homozygous dominant
    if (parent1 == Genotype::HomozygousDominant && parent2 == Genotype::HomozygousDominant)
    {
        return Genotype::HomozygousDominant;
    }

    // If both parents are recessive, 
    // 100% chance offspring will be recessive
    else if (parent1 == Genotype::Recessive && parent2 == Genotype::Recessive)
    {
        return Genotype::Recessive;
    }

    // If one parent is homozygous dominant and other is recessive, 
    // 100% chance offspring will be heterozygous
    else if (parent1 == Genotype::HomozygousDominant && parent2 == Genotype::Recessive)
    {
        return Genotype::Heterozygous;
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
            return Genotype::Heterozygous;
        }
        // 25% chance offspring will be homozygous dominant
        else if (rand_value < 0.75)
        {
            return Genotype::HomozygousDominant;
        }
        // 25% chance offspring will be recessive
        else
        {
            return Genotype::Recessive;
        }
    }
}

// INIT: Initialization of population with a given starting allele frequency
std::vector<Genotype> initialize_population(int size, double recessive_frequency)
{
    std::vector<Genotype> population(size);
    for (Genotype &individual : population)
    {
        double rand_value = static_cast<double>(rand()) / RAND_MAX;
        if (rand_value < recessive_frequency)
        {
            individual = Genotype::Recessive;  // Offspring is recessive
        }
        else if (rand_value < 2 * recessive_frequency)
        {
            individual = Genotype::Heterozygous;   // Ofspring is heterozygous
        }
        else
        {
            individual = Genotype::HomozygousDominant; // Offspring is homozygous dominant
        }
    }
    
    return population;
}

// Simulates one generation and this is the
// implementation of the VON NEUMAN NEIGHBORHOOD!
std::vector<Genotype> simulate_generation(const std::vector<Genotype> &current_population)
{
    std::vector<Genotype> next_generation(current_population.size());
    for (size_t i = 0; i < current_population.size(); ++i)
    {
        Genotype left_parent = current_population[i];
        Genotype right_parent = current_population[(i + 1) % current_population.size()]; // BOUNDARY
        next_generation[i] = determine_genotype(left_parent, right_parent);
    }

    return next_generation;
}
