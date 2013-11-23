#===============================================================================
# Object Oriented Design (Spring 20100)
# Project 1 Makefile
# Author: Shane Transue
# Date: February 26, 2011
#===============================================================================
compiler=g++

#===============================================================================
# The OUTPUT flag identifies the resulting name of the compiled application.
#===============================================================================
OUTPUT=bio-informatics

#===============================================================================
# The following files are those that should be compiled.
#===============================================================================
FILES=main.cpp NeighborJoin/GeneticTreeNode.cpp NeighborJoin/NeighborJoin.cpp Pairwise/AffineSequencer.cpp Pairwise/LinearSequencer.cpp Pairwise/PairwiseAlignment.cpp Pairwise/SubstitutionMatrix.cpp Sequencing/Alignment.cpp Sequencing/Sequence.cpp Utilities/FileScanner.cpp Utilities/Scanner.cpp Utilities/StringScanner.cpp

all:
	$(compiler) $(FILES) -o $(OUTPUT)