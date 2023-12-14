// CHEM 274B: Software Engineering Fundamentals for Molecular Sciences
// Creator: Francine Bianca Oca, Kassady Marasigan, Korede Ogundele
//
// This file is the header file that contains the API linker
// for the general purpose cellular automata library.

#pragma once // Ensures that this file is only included once
             // during compilation
#include <string>
#include <iostream>
#include <vector>
#include <utility>
#include <random>
#include <functional>
using namespace std;

// Enum for dimension type
enum DimensionType
{
    ONE_DIMENSIONAL,
    TWO_DIMENSIONAL,
};

// Enum for neighborhood types
enum NeighborhoodType
{
    VON_NEUMANN,
    MOORE,
};

// Enum for boundary types
enum BoundaryType
{
    PERIODIC,
    FIXED,
    NO_BOUNDARIES,
};

// Enum for rule types
enum RuleType
{
    STRAIGHT_CONDITIONAL,
    CONDITIONAL_TRANSITION,
    MAJORITY_RULE,
};

enum class Allele_Genotype
{
    // Representing state of alleles
    HomozygousDominant = 1,
    Heterzygous = 2,
    Recessive = 3
};

class CellularAutomata
{
private:
    // Member variables to store CA attributes
    DimensionType dimensions;
    NeighborhoodType neighborhood;
    BoundaryType boundaries;
    RuleType rule;
    int rows;                                          // number of rows in the grid
    int cols;                                          // number of columns in the grid
    int neighborhood_radius;                           // radius of neighborhood
    int states;                                        // number of states every cell in CA model can be in
    int k;                                             // state k to be used in rules
    int kprime;                                        // state k' to be used in rules
    std::vector<std::vector<int>> grid;                // grid of the CA
    using RuleFunction = std::function<int(const std::vector<std::vector<int>> &, int, int)>; // Vector for rules
    std::vector<RuleFunction> rules;                   // Vector to store rule functions

public:
    CellularAutomata();  // Default constructor
    ~CellularAutomata(); // Default destructor

    // Setter methods for CA attributes
    void set_dimensions(DimensionType dimensions);
    void set_neighborhood(NeighborhoodType neighborhood);
    void set_boundaries(BoundaryType boundaries);
    void set_rule(RuleType rule);
    void set_grid_size(int rows, int cols);
    void set_neighborhood_radius(int neighborhood_radius);
    void set_states(int states);
    void set_grid(const std::vector<std::vector<int>> &grid);
    void set_k(int k_state);
    void set_kprime(int kprime_state);
    void add_rule(const RuleFunction &new_rule);
    void set_cell_state(int row, int col, int state);

    // Getter methods for CA attributes
    DimensionType get_dimensions() const;
    NeighborhoodType get_neighborhood() const;
    BoundaryType get_boundaries() const;
    RuleType get_rule() const;
    int get_grid_rows() const;
    int get_grid_cols() const;
    int get_neighborhood_radius() const;
    int get_states() const;
    const std::vector<std::vector<int>> &get_grid() const;
    int get_k() const;
    int get_kprime() const;
    std::vector<int> get_neighbors(int i, int j);

    // Functions to setup CA model
    void setup_dimensions();
    void setup_boundaries();
    void setup_neighborhood();
    void setup_rule();

    // Compute Functions
    void onedim_rule1(int k, int kprime);
    void onedim_rule2(int k, int kprime);
    void onedim_rule3(int k, int kprime);
    void twodim_rule1(int k, int kprime);
    void twodim_rule2(int k, int kprime);
    void twodim_rule3(int k, int kprime);

    // Update function to advance the CA model to the next generation
    void update();

    // 4th Rule Function for Our Specific Allele Model
    // This function is a specific rules function for our allele model of which
    // we were told to just include in the CA general purpose library.
    int determine_genotype(int cell_state1, int cell_state2);
};