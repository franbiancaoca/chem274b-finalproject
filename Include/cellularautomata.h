// Chem 274B: Software Engineering Fundamentals for
//            Molecular Sciences
// Creator: Francine Bianca Oca, Kassady Marasigan, Korede Ogundele
// Date Created: 11/23/23
// 
// Include file for our C++ implementations of the cellular automata that models and depicts changes in allele
// frequency over generations in a population.

#include <vector>

// Phenotypes represented by enum -> stands for "enumerated type" and is a convenient 
// way to associate constant values with names to make code more readable and maintainable
enum class Phenotype
{
    HomozygousDominant,     // Homozygous dominant phenotype (if both parents are dominant)
    Heterozygous,           // Heterozygous (if one parent is dominant and one parent is recessive)
    Recessive               // Recessive phenotype (if both parents are dominant)
};

// Operations that determine the phenotype of the offspring
Phenotype determine_phenotype(Phenotype parent1, Phenotype parent2);

// Initialization of population with a given starting allele frequency
std::vector<Phenotype> initialize_population(int size, double recessive_frequency);

// Simulates one generation and this is the
// implementation of the VON NEUMAN NEIGHBORHOOD!
std::vector<Phenotype> simulate_generation(const std::vector<Phenotype> &current_population);