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

    // Ask user for the starting frequency of the recessive allele
    double recessive_frequency;
    std::cout << "Enter the starting frequency of the recessive allele (0 to 1): ";
    std::cin >> recessive_frequency;

    // Check if input is within the correct range
    if (recessive_frequency < 0.0 || recessive_frequency > 1.0)
    {
        std::cerr << "Frequency must be between 0 and 1." << std::endl;
        return 1; // Exit with error code
    }

    // Convert the frequency to a probability threshold for easier comparison
    int recessive_threshold = static_cast<int>(recessive_frequency * RAND_MAX);

    // Modify the grid based on the recessive frequency
    for (int i = 0; i < model.get_grid_rows(); ++i)
    {
        for (int j = 0; j < model.get_grid_cols(); ++j)
        {
            // Generate a random number and compare it to the threshold
            if (std::rand() < recessive_threshold)
            {
                // If the random number is less than the threshold, set the cell to recessive
                model.set_cell_state(i, j, 3); // Assuming there is a function to set the state of a cell
            }
            else
            {
                // Otherwise, randomly assign a dominant or heterozygous state
                model.set_cell_state(i, j, (std::rand() % 2) + 1); // 1 or 2
            }
        }
    }

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