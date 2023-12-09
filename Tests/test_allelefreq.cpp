#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include "general_CA.h"

int main()
{
    srand(static_cast<unsigned int>(time(nullptr)));    // Seed for random number generator

    const int population_size = 100;                    // Size of the population
    const double starting_recessive_frequency = 0.2;    // Starting frequency of recessive allele
    const int number_of_generations = 100;              // Number of generations to simulate

    // Initialize the population
    std::vector<Phenotype> population = initialize_population(population_size, starting_recessive_frequency);

    // Simulate the generations
    for (int generation = 0; generation < number_of_generations; ++generation)
    {
        population = simulate_generation(population);

        // Count phenotypes in the current generation
        int homozygous_dominant_count = std::count(population.begin(), population.end(), Phenotype::HomozygousDominant);
        int heterozygous_count = std::count(population.begin(), population.end(), Phenotype::Heterozygous);
        int homozygous_recessive_count = std::count(population.begin(), population.end(), Phenotype::HomozygousRecessive);

        std::cout << "Generation " << generation << ": "
                  << "Dominant count = " << homozygous_dominant_count << ", "
                  << "Heterozygous count = " << heterozygous_count << ", "
                  << "Recessive count = " << homozygous_recessive_count << std::endl;
    }

    return 0;
}