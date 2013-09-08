DNA-Sequencer
=============
# Introduction

A relatively small python 3.2 and pyd program for the parsing of relatively small DNA sequence segments. The program accepts sequences from fasta files, and outputs a tree in newick format. This can be launched with forester in order to better visualize the tree.

The algorithms used for the pairwise sequence analysis can be chosen at run time and the options are the Needleman-Wunsch algorithm (global), the Smith-Waterman algorithm (local) or an algorithm that uses affine scoring (affine). The multiple sequence alignment algorithm used is the Neighbor Joining algorithm.

This code was written by students of the Metropolitan State University of Denver, and we welcome anyone to download and experiment with our code. With that said, we don't guarantee that it works on all operating systems.
******
# Installation
This application is not installed, but is run via Python 3.2. To get this application on your computer, just download the latest release file, unzip it, and you are ready to run it. It is required that you have Python 3.2 installed, and it is preferable if you have mingw installed for windows. This program runs from the command line, navigate to the directory containing main.py, and run that file using python. If python is in your PATH, then the command would be: "python main.py"

# Input
When the program is running, the first thing you will see are three large text entry boxes, and a file browsing control. This is where you will insert your data. You can compare 2 strings and receive a pairwise sequence score and gaps. Or you can browse to a fasta formatted text file to run the multiple sequence alignment. If a file is chosen, the two text fields will be ignored, and MSA will run. Once the data has been set, you can run at any time by clicking the start button.

# Settings
There are several different ways to configure the comparison of strings. These settings will be applied to either the pairwise or the multiple sequence alignments.

# Open Archaeopteryx
At the very top is a check box to "Open Archaeopteryx when complete." Archaeopteryx is a program for graph visualization, and we can automatically open a specific version of it called forester once the MSA tree has been constructed. This setting does not have any impact on pairwise comparisons. To find out more information on forester, check out the google code page: http://code.google.com/p/forester/.

# Substituion Matrix
The next control is a drop down of substitution matrix files. There are some standard ones, and the default is "BLOSUM62." These files determine how the comparison between characters is scored. The kinds of data that can be compared is only limited by this file. Also, this application can not compare multiple character units. In other words "G", "C", "A", "T" and "U" are fine, but "P1", "P2", etc... would not be understood.

Alternately, if you have a different substitution matrix that you would like to use, you can browse to it with the next control. If this file path is set, the combo box of files will be ignored. These files are used for both MSA and Pairwise comparisons.

#Algorithms
## Gap Analysis Algorithm
The next combo box is the "Gap Analysis Algorithm" box. Your choices are "Local," "Global," and "Affine." These choose the algorithm that is used for the pairwise analysis. Changing to the affine analysis option will change settings available to you for the next setting. The default is "Local"

## Gap Penalty (Local/Global)
The Gap penalty is the score increase due to a gap in the sequence. The default is -1

## Open Gap Penalty and Extend Gap Penalty
When Affine is the chosen algorithm, then instead of simply gap penalty, you choose the open gap and extend gap penalty. This will allow you to customize how the sequence is analysed. The default open gap penalty is -4 and the default extend gap penalty is -1

# Results
The results of both pairwise and multiple sequence alignment will appear in this box. The output for pairwise is the first string with gaps inserted, the second string with gaps, and the score.

For MSA, you will see the entire score table of all of the results of the pairwise comparisons, and then the tree constructed in newick format. If you chose to open with Archaeopteryx, or didn't change the default setting, then this will open as well.

The results page is editable, so if the format does not work for you, you can copy and past (ctrl+c and ctrl+v) to move things around until you like how it looks.

# Example Files
If you would like to experiment with the program, there are example fasta files in the examples folder. blast2samples.fasta is a file of only two HIV sequences that only take seconds to run, blast.7759.fasta is a medium sized data set of HIV sequences that take 3 - 8 min to run, HumanGenome?.fasta has two 16,000 character sequences that take about 5 - 10 min to run, and then OregonPyrgulopsis?.fasta is a larger set of sequences and takes about 15 - 20 min to run.

The substitution matrix files can be found in the matrices folder, feel free to view and copy these files, but removing or editing them will result in the program not operating properly.

# Thanks
Thanks for using our program. Please post issues and feature requests. Feel free to download and inspect the source code.
