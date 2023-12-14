// CHEM 274B: Software Engineering Fundamentals for Molecular Sciences
// Creator: Francine Bianca Oca, Kassady Marasigan, Korede Ogundele
//
// This file contains the general purpose library used to
// model cellular automata. For our case, this general purpose
// library will be used to model allele frequency changes over
// generations for a population.

#include <iostream>
#include <vector>
#include <random>
#include <functional>
#include "CA_library.h"

// Default constructor
CellularAutomata::CellularAutomata() {}

// Default constructor
CellularAutomata::~CellularAutomata() {}

// Setter method to set dimension type of CA
// Inputs:
//      dimensions : The dimension type (ONE_DIMENSIONAL or TWO_DIMENSIONAL)
void CellularAutomata::set_dimensions(DimensionType dimensions)
{
    this->dimensions = dimensions;
}

// Setter method to set neighborhood type of CA
// Inputs:
//      neighborhood : The neighborhood type (VON_NEUMANN or MOORE)
void CellularAutomata::set_neighborhood(NeighborhoodType neighborhood)
{
    this->neighborhood = neighborhood;
}

// Setter method to set boundary type of CA
// Inputs:
//      boundaries : The boundary type (PERIODIC, FIXED, or NO_BOUNDARIES)
void CellularAutomata::set_boundaries(BoundaryType boundaries)
{
    this->boundaries = boundaries;
}

// Setter method to set rule type of CA
// Inputs:
//      rule : The dimension type (STRAIGHT_CONDITIONAL, CONDITIONAL_TRANSITION, or MAJORITY_RULE)
void CellularAutomata::set_rule(RuleType rule)
{
    this->rule = rule;
}

// Setter method to set size of the grid
// Inputs:
//      rows : The number of rows in the grid
//      cols : The number of columns in the grid
void CellularAutomata::set_grid_size(int rows, int cols)
{
    this->rows = rows;
    this->cols = cols;
}

// Setter method to set neighborhood radius type of CA
// Inputs:
//      neighborhood_radius : The radius of the neighborhood
void CellularAutomata::set_neighborhood_radius(int neighborhood_radius)
{
    this->neighborhood_radius = neighborhood_radius;
}

// Setter method to set number of states for each cell in the CA
// Inputs:
//      states : The number of states
void CellularAutomata::set_states(int states)
{
    this->states = states;
}

// Setter method to set the initial state of CA
// Inputs:
//      grid : The initial configuration of the CA grid
void CellularAutomata::set_grid(const std::vector<std::vector<int>>& grid)
{
    this->grid = grid;
}

// Getter method to get dimension type of CA
// Returns:
//      dimensions : The dimension type (ONE_DIMENSIONAL or TWO_DIMENSIONAL)
DimensionType CellularAutomata::get_dimensions() const
{
    return dimensions;
}

// Getter method to get neighborhood type of CA
// Returns:
//      neighborhood : The neighborhood type (VON_NEUMANN or MOORE)
NeighborhoodType CellularAutomata::get_neighborhood() const
{
    return neighborhood;
}

// Getter method to get boundary type of CA
// Returns:
//      boundaries : The boundary type (PERIODIC, FIXED, or NO_BOUNDARIES)
BoundaryType CellularAutomata::get_boundaries() const
{
    return boundaries;
}

// Getter method to get rule type of CA
// Returns:
//      rule : The dimension type (STRAIGHT_CONDITIONAL, CONDITIONAL_TRANSITION, or MAJORITY_RULE)
RuleType CellularAutomata::get_rule() const
{
    return rule;
}

// Getter method to get number of rows in the grid
// Returns:
//      rows : The number of rows in the grid
int CellularAutomata::get_grid_rows() const
{
    return rows;
}

// Getter method to get number of columns in the grid
// Returns:
//      cols : The number of columns in the grid
int CellularAutomata::get_grid_cols() const
{
    return cols;
}

// Getter method to get neighborhood radius type of CA
// Returns:
//      neighborhood_radius : The radius of the neighborhood
int CellularAutomata::get_neighborhood_radius() const
{
    return neighborhood_radius;
}

// Getter method to get number of states for each cell in the CA
// Returns:
//      states : The number of states
int CellularAutomata::get_states() const
{
    return states;
}

// Getter method to get the initial state of CA
// Returns:
//      grid : The initial configuration of the CA grid
const std::vector<std::vector<int>>& CellularAutomata::get_grid() const
{
    return grid;
}

// Setup function to initialize the grid based on the specified dimension
void CellularAutomata::setup_dimensions()
{
    if (dimensions == ONE_DIMENSIONAL)
    {
        // 1D logic setup
        grid = std::vector<std::vector<int>>(rows, std::vector<int>(cols, 0));
    }
    else if (dimensions == TWO_DIMENSIONAL)
    {
        // 2D logic setup
        grid = std::vector<std::vector<int>>(rows, std::vector<int>(cols, 0));
    }
}

// Setup function to configure the grid based on the specified boundary type
void CellularAutomata::setup_boundaries()
{
    if (boundaries == PERIODIC)
    {
        // Periodic boundary logic setup
        for (int i = 0; i < rows; ++i)
        {
            for (int j = 0; j < cols; ++j)
            {
                grid[i][j] = grid[(i + rows) % rows][(j + cols) % cols];
            }
        }
    }
    else if (boundaries == FIXED)
    {
        // Fixed boundary logic setup
        int fixed_state = 1; // Replace with the desired fixed state
        for (int j = 0; j < cols; ++j)
        {
            grid[0][j] = grid[rows - 1][j] = fixed_state;
        }
        for (int i = 0; i < rows; ++i)
        {
            grid[i][0] = grid[i][cols - 1] = fixed_state;
        }
    }
    else if (boundaries == NO_BOUNDARIES)
    {
        // No boundaries logic setup
        // No specific setup needed for no boundaries
    }
}

// Setup function to establish the neighborhood relationships for each cell.
void CellularAutomata::setup_neighborhood()
{
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            int neighbor_north, neighbor_south, neighbor_east, neighbor_west,
                neighbor_north_east, neighbor_south_east, neighbor_south_west, neighbor_north_west;

            if (neighborhood == VON_NEUMANN)
            {
                // Von Neumann logic setup
                neighbor_north = grid[(i - 1 + rows) % rows][j];
                neighbor_south = grid[(i + 1) % rows][j];
                neighbor_east = grid[i][(j + 1) % cols];
                neighbor_west = grid[i][(j - 1 + cols) % cols];
            }
            else if (neighborhood == MOORE)
            {
                // Moore logic setup
                // Same 4 neighbors as Von Neumann
                neighbor_north = grid[(i - 1 + rows) % rows][j];
                neighbor_south = grid[(i + 1) % rows][j];
                neighbor_east = grid[i][(j + 1) % cols];
                neighbor_west = grid[i][(j - 1 + cols) % cols];
                // 4 additional diagonal neighbors
                neighbor_north_east = grid[(i - 1 + rows) % rows][(j + 1) % cols];
                neighbor_south_east = grid[(i + 1) % rows][(j + 1) % cols];
                neighbor_south_west = grid[(i + 1) % rows][(j - 1 + cols) % cols];
                neighbor_north_west = grid[(i - 1 + rows) % rows][(j - 1 + cols) % cols];
            }
        }
    }
}

// Setup function to apply the specified rule to update the grid's state
void CellularAutomata::setup_rule()
{
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            int neighbor_north, neighbor_south, neighbor_east, neighbor_west;

            if (rule == STRAIGHT_CONDITIONAL)
            {
                // Straight conditional transition logic setup
                int state_condition = k; // Replace with the desired state condition
                int new_state = kprime;       // Replace with the desired new state
                if (grid[i][j] == state_condition)
                    grid[i][j] = new_state;
            }
            else if (rule == CONDITIONAL_TRANSITION)
            {
                // Conditional transition rule on a neighbor logic setup
                int state_condition = k;         // Replace with the desired state condition
                int neighbor_condition = kprime;     // Replace with the desired neighbor condition
                if (grid[i][j] == state_condition && neighbor_south == neighbor_condition)
                    grid[i][j] = neighbor_south;
            }
            else if (rule == MAJORITY_RULE)
            {
                // Majority rule logic setup
                int sum_neighbors = neighbor_north + neighbor_south + neighbor_east + neighbor_west;
                int majority_state = (sum_neighbors >= 2) ? 1 : 0;
                grid[i][j] = majority_state;
            }
        }
    }
}

// Setup functions to set and get state "k" to be used on compute step
void CellularAutomata::set_k(int k_state)
{
    k = k_state;
}

int CellularAutomata::get_k() const
{
    return k;
}

// Setup functions to set and get state "k'" to be used on compute step
void CellularAutomata::set_kprime(int kprime_state)
{
    kprime = kprime_state;
}

int CellularAutomata::get_kprime() const
{
    return kprime;
}

// Function to be able to add rules in vector for models that utilize multiple rules
void CellularAutomata::add_rule(RuleFunction rule)
{
    rules.push_back(rule);
}

// Compute function for 1-Dimension/Rule 1
// Updates grid based on Straight Conditional
void CellularAutomata::onedim_rule1(int k, int kprime)
{
    if (dimensions == ONE_DIMENSIONAL && rule == STRAIGHT_CONDITIONAL)
    {
        for (int j = 0; j < cols; ++j)
        {
            // Directly apply rule based on current state
            if (grid[0][j] == k)
            {
                grid[0][j] = kprime; // Change state: k -> k'
            }
        }
    }
}

// Compute function for 1-Dimension/Rule 2
// Updates grid based on Conditional Transition
// Note: Von Neumann and Moore are the same in 1D space (left/right neighbors)
void CellularAutomata::onedim_rule2(int k, int kprime)
{
    std::vector<std::vector<int>> temp_grid = grid;

    for (int j = 0; j < cols; ++j)
    {
        int current_state = grid[0][j];
        int left_neighbor, right_neighbor;

        // PERIODIC BOUNDARIES
        if (boundaries == PERIODIC)
        {
            left_neighbor = grid[0][(j - 1 + cols) % cols];
            right_neighbor = grid[0][(j + 1) % cols];
        }
        else
        {
            // FIXED/NO BOUNDARIES
            left_neighbor = (j == 0) ? ((boundaries == FIXED) ? k : current_state) : grid[0][j - 1];
            right_neighbor = (j == cols - 1) ? ((boundaries == FIXED) ? k : current_state) : grid[0][j + 1];
        }

        // Apply Conditional Transition
        if (current_state == k && (left_neighbor == kprime || right_neighbor == kprime))
        {
            temp_grid[0][j] = kprime;
        }
    }

    grid = temp_grid;
}

// Compute function for 1-Dimension/Rule 3
// Updates grid based on Majority Rule
// Note: Von Neumann and Moore are the same in 1D space (left/right neighbors)
void CellularAutomata::onedim_rule3(int k, int kprime)
{
    // Temp_grid is the current grid
    std::vector<std::vector<int>> temp_grid = grid;

    for (int j = 0; j < cols; ++j)
    {
        int current_state = grid[0][j];
        int left_neighbor, right_neighbor;

        // PERIODIC BOUNDARIES
        if (boundaries == PERIODIC)
        {
            left_neighbor = grid[0][(j - 1 + cols) % cols];
            right_neighbor = grid[0][(j + 1) % cols];
        }
        else
        {
            // FIXED/NO BOUNDARIES
            left_neighbor = (j == 0) ? ((boundaries == FIXED) ? k : current_state) : grid[0][j - 1];
            right_neighbor = (j == cols - 1) ? ((boundaries == FIXED) ? k : current_state) : grid[0][j + 1];
        }

        // Sum states of the neighbors
        int neighbors_sum = left_neighbor + right_neighbor;

        // Apply Majority Rule: If the cell's state is k and neighbors sum >= 1, update to kprime
        if (current_state == k)
        {
            temp_grid[0][j] = (neighbors_sum >= 1) ? kprime : current_state;
        }
    }

    // Grid is the newly updated grid
    grid = temp_grid;
}

// Compute function for 2-Dimension/Rule 1
// Updates grid based on Straight Conditional
void CellularAutomata::twodim_rule1(int k, int kprime)
{
    if (dimensions == TWO_DIMENSIONAL && rule == STRAIGHT_CONDITIONAL)
    {
        for (int i = 0; i < rows; ++i)
        {
            for (int j = 0; j < cols; ++j)
            {
                // Directly apply rule based on current state
                if (grid[i][j] == k)
                {
                    grid[i][j] = kprime; // Change state: k -> k'
                }
            }
        }
    }
}

// Compute function for 2-Dimension/Rule 2
// Updates grid based on Conditional Transition
// Periodic Boundaries: The grid wraps around, and the neighbors of edge cells are calculated as if the grid is a torus
// Fixed Boundaries: The edge cells use their current state or a predefined state for out-of-bound indices
// No Boundaries: The out-of-bound indices are not wrapped around, and edge cells have fewer neighbors to consider
// (treated as if they have the same state as the current cell or a predefined state)
void CellularAutomata::twodim_rule2(int k, int kprime)
{
    std::vector<std::vector<int>> temp_grid = grid;

    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            int current_state = grid[i][j];
            std::vector<int> neighbors;

            // Calculate indices for orthogonal neighbors (VON NEUMANN)
            int north = (boundaries != FIXED || i > 0) ? (i - 1 + rows) % rows : i;
            int south = (boundaries != FIXED || i < rows - 1) ? (i + 1) % rows : i;
            int east = (boundaries != FIXED || j < cols - 1) ? (j + 1) % cols : j;
            int west = (boundaries != FIXED || j > 0) ? (j - 1 + cols) % cols : j;

            // Add orthogonal neighbors (VON NEUMANN)
            neighbors.push_back(grid[north][j]);
            neighbors.push_back(grid[south][j]);
            neighbors.push_back(grid[i][east]);
            neighbors.push_back(grid[i][west]);

            // Include diagonal neighbors (IF MOORE)
            if (neighborhood == MOORE)
            {
                int northeast = (north * cols + east) % (rows * cols);
                int northwest = (north * cols + west) % (rows * cols);
                int southeast = (south * cols + east) % (rows * cols);
                int southwest = (south * cols + west) % (rows * cols);

                neighbors.push_back(grid[northeast / cols][northeast % cols]);
                neighbors.push_back(grid[northwest / cols][northwest % cols]);
                neighbors.push_back(grid[southeast / cols][southeast % cols]);
                neighbors.push_back(grid[southwest / cols][southwest % cols]);
            }

            // Apply Conditional Transition
            bool condition_met = false;
            for (int neighbor_state : neighbors)
            {
                if (neighbor_state == kprime)
                {
                    condition_met = true;
                    break;
                }
            }

            if (current_state == k && condition_met)
            {
                temp_grid[i][j] = kprime;
            }
        }
    }

    // Current grid -> updated grid
    grid = temp_grid;
}

// Compute function for 2-Dimension/Rule 3
// Updates grid based on Majority Rule
// For periodic boundaries, the grid wraps around
// For fixed boundaries, edge cells assume a fixed state (k)
// For no boundaries, edge cells are treated as having the same state as the cell itself
void CellularAutomata::twodim_rule3(int k, int kprime)
{
    std::vector<std::vector<int>> temp_grid = grid;

    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            int current_state = grid[i][j];
            int neighbors_sum = 0;

            // Calculate indices for orthogonal neighbors (periodic boundaries + VN)
            int north = (i - 1 + rows) % rows;
            int south = (i + 1) % rows;
            int east = (j + 1) % cols;
            int west = (j - 1 + cols) % cols;

            // Handle boundaries for orthogonal neighbors (fixed boundaries + VN)
            north = (i == 0 && boundaries != PERIODIC) ? ((boundaries == FIXED) ? k : current_state) : north;
            south = (i == rows - 1 && boundaries != PERIODIC) ? ((boundaries == FIXED) ? k : current_state) : south;
            east = (j == cols - 1 && boundaries != PERIODIC) ? ((boundaries == FIXED) ? k : current_state) : east;
            west = (j == 0 && boundaries != PERIODIC) ? ((boundaries == FIXED) ? k : current_state) : west;

            // Add orthogonal neighbors to the sum
            neighbors_sum += grid[north][j];
            neighbors_sum += grid[south][j];
            neighbors_sum += grid[i][east];
            neighbors_sum += grid[i][west];

            // Include diagonal neighbors for Moore neighborhood
            if (neighborhood == MOORE)
            {
                // Calculate indices for diagonal neighbors (periodic boundaries + M)
                int northeast = (north * cols + east) % (rows * cols);
                int northwest = (north * cols + west) % (rows * cols);
                int southeast = (south * cols + east) % (rows * cols);
                int southwest = (south * cols + west) % (rows * cols);

                // Handle boundaries for diagonal neighbors (fixed boundaries + M)
                if (boundaries != PERIODIC)
                {
                    northeast = ((north == i) ? i : north) * cols + ((east == j) ? j : east);
                    northwest = ((north == i) ? i : north) * cols + ((west == j) ? j : west);
                    southeast = ((south == i) ? i : south) * cols + ((east == j) ? j : east);
                    southwest = ((south == i) ? i : south) * cols + ((west == j) ? j : west);
                }

                neighbors_sum += grid[northeast / cols][northeast % cols];
                neighbors_sum += grid[northwest / cols][northwest % cols];
                neighbors_sum += grid[southeast / cols][southeast % cols];
                neighbors_sum += grid[southwest / cols][southwest % cols];
            }

            // Calculate threshold based on the neighborhood type
            int threshold = (neighborhood == VON_NEUMANN) ? 2 : 5;

            // Apply Majority Rule only if the cell's current state is k
            if (current_state == k)
            {
                temp_grid[i][j] = (neighbors_sum >= threshold) ? kprime : current_state;
            }
        }
    }

    // Current Grid -> Updated Grid
    grid = temp_grid;
}