// CHEM 274B: Software Engineering Fundamentals for Molecular Sciences
// Creator: Francine Bianca Oca, Kassady Marasigan, Korede Ogundele
//
// This file contains the C++ implementations that depict allele
// frequency changes over generations of a population. It utilizes a
// cellular automata general purpose library for representation.

#include <iostream>
#include <vector>
#include <random>
#include <functional>
#include "general_CA.h"

std::function<Phenotype(Phenotype, const std::vector<Phenotype> &)> get_generation_rule()
{
    return [](Phenotype self, const std::vector<Phenotype> &neighbors) -> Phenotype
    {
        // For simplicity, consider only the first neighbor
        if (neighbors.empty())
        {
            return self; // No change if there are no neighbors
        }

        // Random number generator
        static std::random_device rd;
        static std::mt19937 gen(rd());
        static std::uniform_real_distribution<> dis(0, 1);

        // Assuming neighbors[0] is the chosen neighbor
        Phenotype neighbor = neighbors[0];

        // Apply the logic of determine_phenotype
        if (self == Phenotype::HomozygousDominant && neighbor == Phenotype::HomozygousDominant)
        {
            return Phenotype::HomozygousDominant;
        }
        else if (self == Phenotype::HomozygousRecessive && neighbor == Phenotype::HomozygousRecessive)
        {
            return Phenotype::HomozygousRecessive;
        }
        else if ((self == Phenotype::HomozygousDominant && neighbor == Phenotype::HomozygousRecessive) ||
                 (self == Phenotype::HomozygousRecessive && neighbor == Phenotype::HomozygousDominant))
        {
            return Phenotype::Heterozygous;
        }
        else
        {
            // Randomly determine the phenotype for heterozygous cases
            double rand_value = dis(gen);
            if (rand_value < 0.5)
            {
                return Phenotype::Heterozygous;
            }
            else if (rand_value < 0.75)
            {
                return Phenotype::HomozygousDominant;
            }
            else
            {
                return Phenotype::HomozygousRecessive;
            }
        }
    };
}
