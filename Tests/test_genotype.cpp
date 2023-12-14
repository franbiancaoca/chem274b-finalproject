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
#include "CA_library.h"

int main()
{
    // Seeding the rand()
    std::srand(static_cast<unsigned>(std::time(nullptr)));
    
    // Create a model instance of the CellularAutomata class
    CellularAutomata model;

    // Set the appropriate dimensions for CA model
    // -> 2D since it is a grid
    model.set_dimensions(TWO_DIMENSIONAL);

    // Set the appropriate neighborhood for CA model
    // -> Von Neumann since only two neighbors can be parents
    model.set_neighborhood(VON_NEUMANN);

    // Set the appropriate boundaries for CA model
    // -> No boundaries since all cells start with specific genotype
    model.set_boundaries(NO_BOUNDARIES);

    // Set the appropriate rule for CA model
    // -> Conditional transition rule on a neighbor since genotype changes based on its neighbor
    model.set_rule(CONDITIONAL_TRANSITION);

    // Set the appropriate grid size for CA model
    // -> 10 x 10 to start with 100 parent cells
    model.set_grid_size(10, 10);

    // Set the appropriate neighborhood radius for CA model
    // -> 1 since model only accounts for cell and its neighbor
    model.set_neighborhood_radius(1);

    // Set the appropriate numver of states for CA model
    // -> 3 since there are three genotypes (homodom, hetero, and rec)
    model.set_states(3);

    // Setup the CA model based on specific configurations
    model.setup_dimensions();
    model.setup_boundaries();
    model.setup_neighborhood();
    model.setup_rule();

    // Display the initial (current) state of the grid
    std::cout << "Initial state:\n";
    const std::vector<std::vector<int>> &current_grid = model.get_grid();
    for (const auto &row : current_grid)
    {
        for (int cell_state : row)
        {
            std::cout << cell_state << ' ';
        }

        std::cout << '\n';
    }

    // Run the CA model for a specified number of generations
    int num_generations = 10;
    for (int generation = 1; generation <= num_generations; ++generation)
    {
        // Update model for the next generation
        model.update();

        // Display the updated state of the grid
        std::cout << "Generation " << generation << ":\n";
        const std::vector<std::vector<int>> &updated_grid = model.get_grid();
        for (const auto &row : updated_grid)
        {
            for (int cell_state : row)
            {
                std::cout << cell_state << ' ';
            }
            std::cout << '\n';
        }
    }

    return 0;
}