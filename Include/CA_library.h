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


class CellularAutomata
{
    private:
        // Member variables to store CA attributes
        DimensionType dimensions;
        NeighborhoodType neighborhood;
        BoundaryType boundaries;
        RuleType rule;
        int rows;                               // number of rows in the grid
        int cols;                               // number of columns in the grid
        int neighborhood_radius;                // radius of neighborhood
        int states;                             // number of states every cell in CA model can be in
        int k;                                  // state k to be used in rules
        int kprime;                             // state k' to be used in rules
        std::vector<std::vector<int>> grid;     // grid of the CA
        using RuleFunction = void (CellularAutomata::*)(); // Define a function pointer type for rules
        std::vector<RuleFunction> rules;                   // Vector to store rule functions

    public:
        CellularAutomata();         // Default constructor
        ~CellularAutomata();        // Default destructor

        // Setter methods for CA attributes
        void set_dimensions(DimensionType dimensions);
        void set_neighborhood(NeighborhoodType neighborhood);
        void set_boundaries(BoundaryType boundaries);
        void set_rule(RuleType rule);
        void set_grid_size(int rows, int cols);
        void set_neighborhood_radius(int neighborhood_radius);
        void set_states(int states);
        void set_grid(const std::vector<std::vector<int>>& grid);
        void set_k(int k_state);
        void set_kprime(int kprime_state);
        void add_rule(RuleFunction rule);

        // Getter methods for CA attributes
        DimensionType get_dimensions() const;
        NeighborhoodType get_neighborhood() const;
        BoundaryType get_boundaries() const;
        RuleType get_rule() const;
        int get_grid_rows() const;
        int get_grid_cols() const;
        int get_neighborhood_radius() const;
        int get_states() const;
        const std::vector<std::vector<int>>& get_grid() const;
        int get_k() const;
        int get_kprime() const;

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
};