from distutils.core import setup, Extension

SequencingModule = Extension('Sequencing',
    sources = ['PyLinearSequencer.cpp', '../Sequencing/Sequence.cpp', '../Sequencing/Alignment.cpp', '../Pairwise/SubstitutionMatrix.cpp', '../Pairwise/PairwiseAlignment.cpp', '../Pairwise/AffineSequencer.cpp', '../Pairwise/LinearSequencer.cpp', '../Utilities/Scanner.cpp', '../Utilities/FileScanner.cpp', '../Utilities/StringScanner.cpp', '../NeighborJoin/NeighborJoin.cpp', '../NeighborJoin/GeneticTreeNode.cpp', '../MultipleAlignment/Msa.cpp']
)

setup(name = "Sequencing",
    version = "1.0",
    description = "Sequencing Module",
    ext_modules = [SequencingModule],
)
