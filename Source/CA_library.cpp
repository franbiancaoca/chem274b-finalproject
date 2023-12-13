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
            int neighbor_north, neighbor_south, neighbor_east, neighbor_west;

            if (neighborhood == VON_NEUMANN)
            {
                // Von Neumann logic setup
                neighbor_east = grid[i][(j + 1) % cols];
                neighbor_west = grid[i][(j - 1 + cols) % cols];
                neighbor_north = grid[(i - 1 + rows) % rows][j];
                neighbor_south = grid[(i + 1) % rows][j];
            }
            else if (neighborhood == MOORE)
            {
                // Moore logic setup
                neighbor_north = grid[(i - 1 + rows) % rows][j];
                neighbor_south = grid[(i + 1) % rows][j];
                neighbor_east = grid[i][(j + 1) % cols];
                neighbor_west = grid[i][(j - 1 + cols) % cols];
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
                int state_condition = 1; // Replace with the desired state condition
                int new_state = 2;       // Replace with the desired new state
                if (grid[i][j] == state_condition)
                    grid[i][j] = new_state;
            }
            else if (rule == CONDITIONAL_TRANSITION)
            {
                // Conditional transition rule on a neighbor logic setup
                int state_condition = 1;         // Replace with the desired state condition
                int neighbor_condition = 3;     // Replace with the desired neighbor condition
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

// Compute function for 1-Dimension/Rule 1
// Updates grid based on Straight Conditional
void CellularAutomata::onedim_rule1()
{
    std::vector<std::vector<int>> temp_grid(rows, std::vector<int>(cols, 0));

    for (int j = 0; j < cols; ++j)
    {
        if (dimensions == ONE_DIMENSIONAL && rule == STRAIGHT_CONDITIONAL)
        {
            // Indices to be used for left/right neighbors in 1 dimension
            int left_neighbor_index = (j - 1 + cols) % cols;
            int right_neighbor_index = (j + 1) % cols;

            // Get current state of neighbors + current cell
            int current_state = grid[0][j];
            int left_neighbor = grid[0][left_neighbor_index];
            int right_neighbor = grid[0][right_neighbor_index];

            // VN NEIGHBORHOOD & PERIODIC BOUNDARIES
            if (neighborhood == VON_NEUMANN && boundaries == PERIODIC)
            {
                // If current state is k -> change to k'
                temp_grid[0][j] = (current_state == k) ? kprime : current_state;
            }

            // VN NEIGHBORHOOD & FIXED BOUNDARIES
            if (neighborhood == VON_NEUMANN && boundaries == FIXED)
            {
                // Cells at the boundaries maintain the fixed state 'k'
                temp_grid[0][j] = (j == 0 || j == cols - 1) ? k : (current_state == k) ? kprime
                                                                                       : current_state;
            }

            // VN NEIGHBORHOOD & NO BOUNDARIES
            if (neighborhood == VON_NEUMANN && boundaries == NO_BOUNDARIES)
            {
                // Neighbors beyond the grid considered same as the current state
                left_neighbor = (j == 0) ? current_state : grid[0][j - 1];
                right_neighbor = (j == cols - 1) ? current_state : grid[0][j + 1];
                temp_grid[0][j] = (current_state == k) ? kprime : current_state;
            }

            // M NEIGHBORHOOD & PERIODIC BOUNDARIES
            if (neighborhood == MOORE && boundaries == PERIODIC)
            {
                // For one-dimensional, M = VM
                temp_grid[0][j] = (current_state == k) ? kprime : current_state;
            }

            // M NEIGHBORHOOD & FIXED BOUNDARIES
            if (neighborhood == MOORE && boundaries == FIXED)
            {
                // Cells at the boundaries maintain the fixed state 'k'
                temp_grid[0][j] = (j == 0 || j == cols - 1) ? k : (current_state == k) ? kprime
                                                                                       : current_state;
            }

            // M NEIGHBORHOOD & NO BOUNDARIES
            if (neighborhood == MOORE && boundaries == NO_BOUNDARIES)
            {
                // For one-dimensional, M = VM with no boundaries
                left_neighbor = (j == 0) ? current_state : grid[0][j - 1];
                right_neighbor = (j == cols - 1) ? current_state : grid[0][j + 1];
                temp_grid[0][j] = (current_state == k) ? kprime : current_state;
            }
        }
    }
    grid = temp_grid;
}

// Compute function for 1-Dimension/Rule 2
// Updates grid based on Conditional Transition
void CellularAutomata::onedim_rule2()
{
    std::vector<std::vector<int>> temp_grid(rows, std::vector<int>(cols, 0));

    for (int j = 0; j < cols; ++j)
    {
        if (dimensions == ONE_DIMENSIONAL && rule == CONDITIONAL_TRANSITION)
        {
            // Indices to be used for left/right neighbors in 1 dimension
            int left_neighbor_index = (j - 1 + cols) % cols;
            int right_neighbor_index = (j + 1) % cols;

            // Get the current state and the neighbor's states
            int current_state = grid[0][j];
            int left_neighbor = grid[0][left_neighbor_index];
            int right_neighbor = grid[0][right_neighbor_index];

            // VN NEIGHBORHOOD & PERIODIC BOUNDARIES
            if (neighborhood == VON_NEUMANN && boundaries == PERIODIC)
            {
                // Apply conditional transition
                temp_grid[0][j] = (current_state == k && (left_neighbor == kprime || right_neighbor == kprime)) ? kprime : current_state;
            }

            // VN NEIGHBORHOOD & FIXED BOUNDARIES
            if (neighborhood == VON_NEUMANN && boundaries == FIXED)
            {
                // Boundary cells maintain the fixed state 'k'
                temp_grid[0][j] = (j == 0 || j == cols - 1) ? k : (current_state == k && (left_neighbor == kprime || right_neighbor == kprime)) ? kprime
                                                                                                                                                  : current_state;
            }

            // VN NEIGHBORHOOD & NO BOUNDARIES
            if (neighborhood == VON_NEUMANN && boundaries == NO_BOUNDARIES)
            {
                // No wrapping, edges have no neighbors beyond the boundary
                left_neighbor = (j == 0) ? current_state : grid[0][j - 1];
                right_neighbor = (j == cols - 1) ? current_state : grid[0][j + 1];

                // Apply the conditional transition rule
                temp_grid[0][j] = (current_state == k && (left_neighbor == kprime || right_neighbor == kprime)) ? kprime : current_state;
            }

            // M NEIGHBORHOOD & PERIODIC BOUNDARIES
            if (neighborhood == MOORE && boundaries == PERIODIC)
            {
                // For one-dimensional, M = VM
                temp_grid[0][j] = (current_state == k && (left_neighbor == kprime || right_neighbor == kprime)) ? kprime : current_state;
            }

            // M NEIGHBORHOOD & FIXED BOUNDARIES
            if (neighborhood == MOORE && boundaries == FIXED)
            {
                // Boundary cells maintain the fixed state 'k'
                temp_grid[0][j] = (j == 0 || j == cols - 1) ? k : (current_state == k && (left_neighbor == kprime || right_neighbor == kprime)) ? kprime
                                                                                                                                                  : current_state;
            }

            // M NEIGHBORHOOD & NO BOUNDARIES
            if (neighborhood == MOORE && boundaries == NO_BOUNDARIES)
            {
                // No wrapping, edges have no neighbors beyond the boundary
                left_neighbor = (j == 0) ? current_state : grid[0][j - 1];
                right_neighbor = (j == cols - 1) ? current_state : grid[0][j + 1];

                // Apply conditional transition
                temp_grid[0][j] = (current_state == k && (left_neighbor == kprime || right_neighbor == kprime)) ? kprime : current_state;
            }
        }
    }

    grid = temp_grid;
}

// Compute function for 1-Dimension/Rule 3
// Updates grid based on Majority Rule
void CellularAutomata::onedim_rule3()
{
    std::vector<std::vector<int>> temp_grid(rows, std::vector<int>(cols, 0));

    for (int j = 0; j < cols; ++j)
    {
        if (dimensions == ONE_DIMENSIONAL && rule == MAJORITY_RULE)
        {
            int current_state = grid[0][j];
            int neighbors_sum = 0; // Sum of the states of neighboring cells

            // Calculate the indices for the neighbors considering the boundaries
            int left_neighbor_index = (j - 1 + cols) % cols;
            int right_neighbor_index = (j + 1) % cols;

            int left_neighbor = grid[0][left_neighbor_index];
            int right_neighbor = grid[0][right_neighbor_index];

            // VN NEIGHBORHOOD & PERIODIC BOUNDARIES
            if (neighborhood == VON_NEUMANN && boundaries == PERIODIC)
            {
                // Sum states of the left and right neighbors
                neighbors_sum = left_neighbor + right_neighbor;
            }

            // VN NEIGHBORHOOD & FIXED BOUNDARIES
            if (neighborhood == VON_NEUMANN && boundaries == FIXED)
            {
                // Edge cells keep their original state
                neighbors_sum = (j == 0 || j == cols - 1) ? current_state : left_neighbor + right_neighbor;
            }

            // VN NEIGHBORHOOD & NO BOUNDARIES
            if (neighborhood == VON_NEUMANN && boundaries == NO_BOUNDARIES)
            {
                neighbors_sum = (j == 0 ? current_state : left_neighbor) + (j == cols - 1 ? current_state : right_neighbor);
            }

            // M NEIGHBORHOOD & PERIODIC BOUNDARIES
            if (neighborhood == MOORE && boundaries == PERIODIC)
            {
                // For one-dimensional, M = VM
                neighbors_sum = left_neighbor + right_neighbor;
            }

            // M NEIGHBORHOOD & FIXED BOUNDARIES
            if (neighborhood == MOORE && boundaries == FIXED)
            {
                // Edge cells keeps original state
                neighbors_sum = (j == 0 || j == cols - 1) ? current_state : left_neighbor + right_neighbor;
            }

            // M NEIGHBORHOOD & NO BOUNDARIES
            if (neighborhood == MOORE && boundaries == NO_BOUNDARIES)
            {
                neighbors_sum = (j == 0 ? current_state : left_neighbor) + (j == cols - 1 ? current_state : right_neighbor);
            }

            // Apply majority rule: if the sum of neighbors states is greater than or equal to 1, set to 1; else, set to 0
            temp_grid[0][j] = (neighbors_sum >= 1) ? 1 : 0;
        }
    }

    grid = temp_grid;
}

// Compute function for 2-Dimension/Rule 1
// Updates grid based on Straight Conditional
void CellularAutomata::twodim_rule1()
{
    std::vector<std::vector<int>> temp_grid(rows, std::vector<int>(cols, 0));

    if (dimensions == TWO_DIMENSIONAL && rule == STRAIGHT_CONDITIONAL)
    {
        for (int i = 0; i < rows; ++i)
        {
            for (int j = 0; j < cols; ++j)
            {
                int current_state = grid[i][j];

                // Calculate indices for neighbors
                int north = (i - 1 + rows) % rows;
                int south = (i + 1) % rows;
                int east = (j + 1) % cols;
                int west = (j - 1 + cols) % cols;

                // Calculate indices for diagonal neighbors (For Moore)
                int northeast = (north * cols + east) % (rows * cols);
                int northwest = (north * cols + west) % (rows * cols);
                int southeast = (south * cols + east) % (rows * cols);
                int southwest = (south * cols + west) % (rows * cols);

                // VN NEIGHBORHOOD & PERIODIC BOUNDARIES
                if (neighborhood == VON_NEUMANN && boundaries == PERIODIC)
                {
                    // If current state is k -> change to k'
                    temp_grid[i][j] = (current_state == k) ? kprime : current_state;
                }

                // VN NEIGHBORHOOD & FIXED BOUNDARIES
                if (neighborhood == VON_NEUMANN && boundaries == FIXED)
                {
                    // Cells at the edges of the grid maintain a fixed state
                    temp_grid[i][j] = (i == 0 || i == rows - 1 || j == 0 || j == cols - 1) ? k : (current_state == k) ? kprime
                                                                                                                    : current_state;
                }

                // VN NEIGHBORHOOD & NO BOUNDARIES
                if (neighborhood == VON_NEUMANN && boundaries == NO_BOUNDARIES)
                {
                    // In the no-boundary condition, edge cells do not wrap around
                    temp_grid[i][j] = (current_state == k) ? kprime : current_state;
                }

                // M NEIGHBORHOOD & PERIODIC BOUNDARIES
                if (neighborhood == MOORE && boundaries == PERIODIC)
                {
                    // Include diagonal neighbors for Moore neighborhood
                    int sum_diagonals = grid[northeast / cols][northeast % cols] +
                                        grid[northwest / cols][northwest % cols] +
                                        grid[southeast / cols][southeast % cols] +
                                        grid[southwest / cols][southwest % cols];

                    // Apply the rule based on the sum of orthogonal and diagonal neighbors
                    temp_grid[i][j] = (current_state == k) ? kprime : current_state; // Modify this logic as needed
                }

                // M NEIGHBORHOOD & FIXED BOUNDARIES
                if (neighborhood == MOORE && boundaries == FIXED)
                {
                    // In fixed boundaries, edge and corner cells maintain a fixed state
                    // Assuming the fixed state is 'k'
                    if (i == 0 || i == rows - 1 || j == 0 || j == cols - 1)
                    {
                        temp_grid[i][j] = k;
                    }
                    else
                    {
                        // Apply the rule for internal cells
                        temp_grid[i][j] = (current_state == k) ? kprime : current_state;
                    }
                }

                // M NEIGHBORHOOD & NO BOUNDARIES
                if (neighborhood == MOORE && boundaries == NO_BOUNDARIES)
                {
                    // For no boundaries, treat out-of-bound indices as if they have the same state as the current cell
                    if (i > 0 && i < rows - 1 && j > 0 && j < cols - 1)
                    {
                        // Apply the rule for internal cells
                        temp_grid[i][j] = (current_state == k) ? kprime : current_state;
                    }
                    else
                    {
                        // Edge and corner cells keep their current state
                        temp_grid[i][j] = current_state;
                    }
                }
            }
        }
    }
    grid = temp_grid;
}



// Compute function for 2-Dimension/Rule 2
// Updates grid based on Conditional Transition
void CellularAutomata::twodim_rule2()
{
    std::vector<std::vector<int>> temp_grid(rows, std::vector<int>(cols, 0));

    if (dimensions == TWO_DIMENSIONAL && rule == CONDITIONAL_TRANSITION)
    {
        for (int i = 0; i < rows; ++i)
        {
            for (int j = 0; j < cols; ++j)
            {
                int current_state = grid[i][j];

                // Calculate indices for orthogonal neighbors
                int north = (i - 1 + rows) % rows;
                int south = (i + 1) % rows;
                int east = (j + 1) % cols;
                int west = (j - 1 + cols) % cols;

                // Calculate indices for diagonal neighbors (For Moore)
                int northeast = (north * cols + east) % (rows * cols);
                int northwest = (north * cols + west) % (rows * cols);
                int southeast = (south * cols + east) % (rows * cols);
                int southwest = (south * cols + west) % (rows * cols);

                // Check neighbors for Von Neumann neighborhood
                bool vn_condition = grid[north][j] == k || grid[south][j] == k ||
                                    grid[i][east] == k || grid[i][west] == k;

                // Check neighbors for Moore neighborhood
                bool m_condition = vn_condition ||
                                   grid[northeast / cols][northeast % cols] == k ||
                                   grid[northwest / cols][northwest % cols] == k ||
                                   grid[southeast / cols][southeast % cols] == k ||
                                   grid[southwest / cols][southwest % cols] == k;

                // VN NEIGHBORHOOD & PERIODIC BOUNDARIES
                if (neighborhood == VON_NEUMANN && boundaries == PERIODIC)
                {
                    // Apply conditional transition
                    temp_grid[i][j] = vn_condition ? kprime : current_state;
                }

                // VN NEIGHBORHOOD & FIXED BOUNDARIES
                if (neighborhood == VON_NEUMANN && boundaries == FIXED)
                {
                    temp_grid[i][j] = (i == 0 || i == rows - 1 || j == 0 || j == cols - 1) ? current_state : (vn_condition ? kprime : current_state);
                }

                // VN NEIGHBORHOOD & NO BOUNDARIES
                if (neighborhood == VON_NEUMANN && boundaries == NO_BOUNDARIES)
                {
                    temp_grid[i][j] = vn_condition ? kprime : current_state;
                }

                // M NEIGHBORHOOD & PERIODIC BOUNDARIES
                if (neighborhood == MOORE && boundaries == PERIODIC)
                {
                    temp_grid[i][j] = m_condition ? kprime : current_state;
                }

                // M NEIGHBORHOOD & FIXED BOUNDARIES
                if (neighborhood == MOORE && boundaries == FIXED)
                {
                    temp_grid[i][j] = (i == 0 || i == rows - 1 || j == 0 || j == cols - 1) ? current_state : (m_condition ? kprime : current_state);
                }

                // M NEIGHBORHOOD & NO BOUNDARIES
                if (neighborhood == MOORE && boundaries == NO_BOUNDARIES)
                {
                    temp_grid[i][j] = m_condition ? kprime : current_state;
                }
            }
        }
    }

    grid = temp_grid;
}

// Compute function for 2-Dimension/Rule 3
// Updates grid based on Majority Rule
void CellularAutomata::twodim_rule3()
{
    std::vector<std::vector<int>> temp_grid(rows, std::vector<int>(cols, 0));

    if (dimensions == TWO_DIMENSIONAL && rule == MAJORITY_RULE)
    {
        for (int i = 0; i < rows; ++i)
        {
            for (int j = 0; j < cols; ++j)
            {
                int current_state = grid[i][j];

                // Calculate indices for orthogonal neighbors
                int north = (i - 1 + rows) % rows;
                int south = (i + 1) % rows;
                int east = (j + 1) % cols;
                int west = (j - 1 + cols) % cols;

                // Calculate indices for diagonal neighbors (For Moore)
                int northeast = (north * cols + east) % (rows * cols);
                int northwest = (north * cols + west) % (rows * cols);
                int southeast = (south * cols + east) % (rows * cols);
                int southwest = (south * cols + west) % (rows * cols);

                // Count the number of neighboring cells that are in state 1
                int sum_neighbors = grid[north][j] + grid[south][j] +
                                    grid[i][east] + grid[i][west];

                // Include diagonal neighbors for Moore neighborhood
                if (neighborhood == MOORE)
                {
                    sum_neighbors += grid[northeast / cols][northeast % cols] +
                                     grid[northwest / cols][northwest % cols] +
                                     grid[southeast / cols][southeast % cols] +
                                     grid[southwest / cols][southwest % cols];
                }

                // Apply majority rule based on the sum of neighbors
                int threshold = (neighborhood == VON_NEUMANN) ? 2 : 5;

                // VM NEIGHBORHOOD & PERIODIC BOUNDARIES
                if (neighborhood == VON_NEUMANN && boundaries == PERIODIC)
                {
                    temp_grid[i][j] = (sum_neighbors >= threshold) ? 1 : 0;
                }

                // VM NEIGHBORHOOD & FIXED BOUNDARIES
                if (neighborhood == VON_NEUMANN && boundaries == FIXED)
                {
                    temp_grid[i][j] = (i == 0 || i == rows - 1 || j == 0 || j == cols - 1) ? current_state : (sum_neighbors >= threshold) ? 1
                                                                                                                                          : 0;
                }

                // VM NEIGHBORHOOD & NO BOUNDARIES
                if (neighborhood == VON_NEUMANN && boundaries == NO_BOUNDARIES)
                {
                    temp_grid[i][j] = (sum_neighbors >= threshold) ? 1 : 0;
                }

                // M NEIGHBORHOOD & PERIODIC BOUNDARIES
                if (neighborhood == MOORE && boundaries == PERIODIC)
                {
                    temp_grid[i][j] = (sum_neighbors >= threshold) ? 1 : 0;
                }

                // M NEIGHBORHOOD & FIXED BOUNDARIES
                if (neighborhood == MOORE && boundaries == FIXED)
                {
                    temp_grid[i][j] = (i == 0 || i == rows - 1 || j == 0 || j == cols - 1) ? current_state : (sum_neighbors >= threshold) ? 1
                                                                                                                                          : 0;
                }

                // M NEIGHBORHOOD & NO BOUNDARIES
                if (neighborhood == MOORE && boundaries == NO_BOUNDARIES)
                {
                    temp_grid[i][j] = (sum_neighbors >= threshold) ? 1 : 0;
                }
            }
        }
    }

    grid = temp_grid;
}