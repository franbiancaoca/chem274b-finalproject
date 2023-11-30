#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include "cellularautomata.h"

int main()
{
    srand(static_cast<unsigned int>(time(nullptr))); // Seed for random number generator

    const int population_size = 100;                 // Size of the population
    const double starting_recessive_frequency = 0.2; // Starting frequency of recessive allele
    const int number_of_generations = 100;            // Number of generations to simulate

    // Initialize the population
    std::vector<Phenotype> population = initialize_population(population_size, starting_recessive_frequency);

    // Simulate the generations
    for (int generation = 0; generation < number_of_generations; ++generation)
    {
        population = simulate_generation(population);

        // Count recessive and dominant individuals in the current generation
        int recessive_count = std::count(population.begin(), population.end(), Phenotype::Recessive);
        int dominant_count = population_size - recessive_count; // Assuming only two phenotypes: dominant and recessive
        std::cout << "Generation " << generation << ": "
                  << "Recessive count = " << dominant_count << ", "
                  << "Dominant count = " << recessive_count << std::endl;
    }

    return 0;
}