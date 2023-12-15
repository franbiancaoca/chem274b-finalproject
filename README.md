# CHEM 274B: Software Engineering Fundamentals for Molecular Sciences
# This repository contains the final project by Kassady Marasigan, Francine Bianca Oca and Korede Ogundele

## In this project we implemented two cellular automata (CA) models: one general purpose and one specifically applied to an allele frequency model.

### Subdirectories in this repository are:

- Bin/
This directory contains test executables from our general purpose CA model and our allele frequency CA model.

- Include/
This directory contains header files for both CA models.

- Lib/
This directory contains our compiled library objects.

- Source/
This directory contains both cellular automata models and their implementations, including all input and compute functions.

- Tests/
The Test directory contains tests for the input and compute functions of both CA models.

- Utils/
This directory contains all plotting functions and data, including outputs from our compute functions

- Utils/Plots/
The Plots subdirectory contains all plotting functions. Unlike the rest of this repository, these are written in Python and displayed in a Jupyter Notebook. The output plots are also saved as .png and present within this repository. Please view the README of this directory for a more detailed description of each file.

- Utils/Plots/Data
Finally, this repository contains all data used by plotting functions. These are outputs from our compute functions that detail number of individuals of each state, changes in the cellular automata grid from step to step, and more.