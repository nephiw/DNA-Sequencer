/**
 * This is undefined to remove the requirement of the python32_d.lib library.
 * Undefining this identifier forces the pyconfig.h to include the python32.lib
 * that is included in the default Python3.2 libs directory.
 */
#undef _DEBUG

// If __DEBUG__ is defined the module code can be built in Visual Studio 2010 in "Debug" mode.
// If __DEBUG__ is not defined the module code can be built in Visual Studio 2010 in "Release" mode.

//#define __DEBUG__ 
#ifndef __DEBUG__

#include <python.h>
#include <vector>
#include "../Pairwise/SubstitutionMatrix.h"
#include "../Pairwise/PairwiseAlignment.h"
#include "../Sequencing/Alignment.h"
#include "../Pairwise/LinearSequencer.h"
#include "../Pairwise/AffineSequencer.h"
#include "../Sequencing/Sequence.h"
#include "../NeighborJoin/NeighborJoin.h"
#include "../MultipleAlignment/Msa.h"

using Pairwise::MatrixDataType;
using Pairwise::SubstitutionMatrix;
using Pairwise::LinearSequencer;
using Pairwise::AffineSequencer;
using Pairwise::PairwiseAlignment;
using Sequencing::Sequence;
using Sequencing::Alignment;
using MultipleSequencing::MultipleSequenceAlignment;

/**
 * This function constructs the string representation of a Phylogenetic tree in the
 * newick tree format. This tree is constructed from a distance matrix that contains
 * the pairwise sequencing scores between all possible sequence combinations. This 
 * function uses the NeighborJoining algorithm to construct the tree from the given
 * distance matrix.
 * Neighbor Joining: http://en.wikipedia.org/wiki/Neighbor-joining
 *
 * The following example illustrates a typical Phylogenetic tree and its newick 
 * representation.
 *
 *  |---A
 *  |
 * F|-----B
 *  |        |---C
 *  |-------E|
 *           |----D
 *
 * The newick format for the tree above: (A,B,(C,D)E)F;
 *
 * Newick: http://en.wikipedia.org/wiki/Newick_format
 *
 * @param PyObject* self The Python reference to the calling object.
 * @param PyObject* args The arguments provided to this function used to create the
 * newick tree. The arguments include the following:
 *     Input Matrix - The distance matrix composed of n*n pariwise comparisons made
 *     between n sequences.
 * @return The newick tree constructed from the distance matrix provided. The newick
 * tree is provided in the form of a string.
 */
static PyObject* Sequencing_constructNewickTree(PyObject* self, PyObject* args)
{
	PyObject* input_matrix;
	std::vector<std::vector<double> > matrix;
	PyObject* sequence_names;
	std::vector<std::string> sequences;

	if ( !PyArg_ParseTuple(args, "OO", &input_matrix, &sequence_names) )
		return NULL;

	int sequence_names_size = PyList_Size(sequence_names);
	sequences = std::vector<std::string>();

	for ( int i = 0; i < sequence_names_size; i++ )
	{
		PyObject* pyObject = PyList_GetItem(sequence_names, i);
		PyObject* ascii = PyUnicode_AsASCIIString(pyObject);
		const char* cur_string = PyBytes_AsString(ascii);
		std::string s = std::string(cur_string);
		sequences.push_back(s);
	}

	int column_list_size = PyList_Size(input_matrix);
	int row_list_size = 0;

	if ( column_list_size == 0 )
		return NULL;
	else
	{
		PyObject* row_list = PyList_GetItem(input_matrix, 0);
		row_list_size = PyList_Size(row_list);
	}
	
	matrix = std::vector<std::vector<double> >(column_list_size, std::vector<double>(row_list_size, 0));
	
	for ( int i = 0; i < column_list_size; i++ )
	{
		PyObject* row_list = PyList_GetItem(input_matrix, i);
		if ( !PyList_Check(row_list) )
			return NULL;
		
		for ( int j = 0; j < row_list_size; j++ )
		{
			PyObject* matrix_cell_contents = PyList_GetItem(row_list, j);
			int score = PyLong_AsLong(matrix_cell_contents);
			matrix[i][j] = score;
		}
	}

	NeighborJoin nj = NeighborJoin();
	std::string newick_tree = nj.construct_tree(matrix, sequences);
	return Py_BuildValue("s", newick_tree.c_str());
}

/**
 * This function loads a substitution matrix given a specific filename. The
 * substitution matrix is then returned as a list of lists. (A 2 dimensional array)
 * The substitution matrix should have the following form:
 *
 * # Comments begin with the # character and are only contained above the matrix
 * # Each label of every matrix column and row must be unique characters: 
 *    A  C  G  T
 * A  1 -1 -1 -1
 * C -1  1 -1 -1
 * G -1 -1  1 -1
 * T -1 -1 -1  1
 *
 * Substitution Matrix: http://en.wikipedia.org/wiki/Substitution_matrix
 *
 * @param PyObject* self The Python reference to the calling object.
 * @param PyObject* args The arguments provided to this function used to create the
 * newick tree. The arguments include the following:
 *     Filename - The name of the file that contains the substitution matrix. This file
 *     should have the form of a properly constructed substitution matrix.
 * @return This function returns a list of lists (A 2 dimensional array) of the
 * substitution matrix loaded from the given filename.
 */
static PyObject* Sequencing_loadSubstitutionMatrix(PyObject* self, PyObject* args)
{
	const char* filename;
	if ( !PyArg_ParseTuple(args, "s", &filename) )
		return NULL;

	SubstitutionMatrix substitution_matrix = SubstitutionMatrix();
	substitution_matrix.load(filename);

	int column_count = substitution_matrix.getColumnCount();
	int row_count = substitution_matrix.getRowCount();

	PyObject* matrix = PyList_New(column_count);
	for ( int i = 0; i < column_count; i++ )
	{
		PyObject* row = PyList_New(row_count);
		for ( int j = 0; j < row_count; j++ )
			PyList_SetItem(row, j, PyFloat_FromDouble(substitution_matrix.get(i, j)));
		PyList_SetItem(matrix, i, row);
	}
	return matrix;
}

/**
 * This function is used to align two sequences based on the linear scoring method. The
 * linear scoring method simply lowers the score of the alignment based on a linear
 * increment of a fixed gap score. The two algorithms used to implement the linear
 * scoring method are:
 *
 *     Needleman–Wunsch algorithm: http://en.wikipedia.org/wiki/Needleman%E2%80%93Wunsch_algorithm
 *     Smith–Waterman: http://en.wikipedia.org/wiki/Smith%E2%80%93Waterman_algorithm
 *
 * @param PyObject* self The Python reference to the calling object.
 * @param PyObject* args The arguments provided to this function used to create the
 * newick tree. The arguments include the following:
 *     Global - This value indicates whether or not the linear scoring algorithm
 *	       should global or local. Global alignments result in the best alignment
 *         between the two provided sequences for the length of the longest sequence.
 *         Local alignments result in the best alignment between the two provided
 *         sequences for any length.
 *     Gap Penalty - The gap penalty is used to lower the score between mismatching
 *         charactesr in the provided sequences.
 *     Matrix - The substitution matrix is required to calculate the score of the
 *	       alignment.
 *     Sequence 1 - The first sequence to align.
 *     Sequence 2 - The second sequence to align.
 * @return The return value of this function is a composite object that includes both
 * aligned sequences with gaps inserted followed by the score that the alignment achieved.
 */
static PyObject* Sequencing_linearSequence(PyObject* self, PyObject* args)
{
	PyObject* input_matrix;
	int input_global;
	int input_gap_penalty;
	const char* input_sequence1;
	const char* input_sequence2;
	std::vector<std::vector<MatrixDataType> > matrix;
	std::string sequence1;
	std::string sequence2;

	if ( !PyArg_ParseTuple(args, "iiOss", &input_global, &input_gap_penalty, &input_matrix, &input_sequence1, &input_sequence2) )
		return NULL;

	if ( !PyList_Check(input_matrix) )
		return NULL;

	int column_list_size = PyList_Size(input_matrix);
	int row_list_size = 0;

	if ( column_list_size == 0 )
		return NULL;
	else
	{
		PyObject* row_list = PyList_GetItem(input_matrix, 0);
		row_list_size = PyList_Size(row_list);
	}
	
	matrix = std::vector<std::vector<MatrixDataType> >(column_list_size, std::vector<MatrixDataType>(row_list_size, 0));
	
	for ( int i = 0; i < column_list_size; i++ )
	{
		PyObject* row_list = PyList_GetItem(input_matrix, i);
		if ( !PyList_Check(row_list) )
			return NULL;
		
		for ( int j = 0; j < row_list_size; j++ )
		{
			PyObject* matrix_cell_contents = PyList_GetItem(row_list, j);
			int score = PyLong_AsLong(matrix_cell_contents);
			matrix[i][j] = score;
		}
	}
	
	sequence1 = std::string(input_sequence1);
	sequence2 = std::string(input_sequence2);
	bool global = input_global;

	SubstitutionMatrix substitution_matrix = SubstitutionMatrix(matrix);

	LinearSequencer ds = LinearSequencer(input_gap_penalty);
	PairwiseAlignment alignment = ds.sequence(global, substitution_matrix, sequence1, sequence2);
	return Py_BuildValue("ssi", alignment.getSequence(0).c_str(), alignment.getSequence(1).c_str(), alignment.getScore());
}

/**
 * This function is used to align two sequences based on the affine scoring method. The
 * affine scoring method is used to create alignments based on high penalties for gaps.
 * The affine scoring method uses an open gap penalty as well as an extend gap penalty.
 *
 * @param PyObject* self The Python reference to the calling object.
 * @param PyObject* args The arguments provided to this function used to create the
 * newick tree. The arguments include the following:
 *     Global - This value indicates whether or not the linear scoring algorithm
 *	       should global or local. Global alignments result in the best alignment
 *         between the two provided sequences for the length of the longest sequence.
 *         Local alignments result in the best alignment between the two provided
 *         sequences for any length.
 *     Open Gap Penalty - The open gap penalty is the cost of opening a gap in the
 *         aligned sequences.
 *     Extend Gap Penalty - The extend gap penalty is the cost of extending a gap in the
 *         aligned sequences.
 *     Matrix - The substitution matrix is required to calculate the score of the
 *	       alignment.
 *     Sequence 1 - The first sequence to align.
 *     Sequence 2 - The second sequence to align.
 * @return The return value of this function is a composite object that includes both
 * aligned sequences with gaps inserted followed by the score that the alignment achieved.
 */
static PyObject* Sequencing_affineSequence(PyObject* self, PyObject* args)
{
	PyObject* input_matrix;
	int input_global;
	int input_open_gap_penalty;
	int input_extend_gap_penalty;
	const char* input_sequence1;
	const char* input_sequence2;
	std::vector<std::vector<MatrixDataType> > matrix;
	std::string sequence1;
	std::string sequence2;

	if ( !PyArg_ParseTuple(args, "iiiOss", &input_global, &input_open_gap_penalty, &input_extend_gap_penalty, &input_matrix, &input_sequence1, &input_sequence2) )
		return NULL;

	if ( !PyList_Check(input_matrix) )
		return NULL;

	int column_list_size = PyList_Size(input_matrix);
	int row_list_size = 0;

	if ( column_list_size == 0 )
		return NULL;
	else
	{
		PyObject* row_list = PyList_GetItem(input_matrix, 0);
		row_list_size = PyList_Size(row_list);
	}
	
	matrix = std::vector<std::vector<MatrixDataType> >(column_list_size, std::vector<MatrixDataType>(row_list_size, 0));
	
	for ( int i = 0; i < column_list_size; i++ )
	{
		PyObject* row_list = PyList_GetItem(input_matrix, i);
		if ( !PyList_Check(row_list) )
			return NULL;
		
		for ( int j = 0; j < row_list_size; j++ )
		{
			PyObject* matrix_cell_contents = PyList_GetItem(row_list, j);
			int score = PyLong_AsLong(matrix_cell_contents);
			matrix[i][j] = score;
		}
	}
	
	sequence1 = std::string(input_sequence1);
	sequence2 = std::string(input_sequence2);
	bool global = input_global;

	SubstitutionMatrix substitution_matrix = SubstitutionMatrix(matrix);

	AffineSequencer as = AffineSequencer(input_open_gap_penalty, input_extend_gap_penalty);
	PairwiseAlignment alignment = as.sequence(global, substitution_matrix, sequence1, sequence2);
	return Py_BuildValue("ssi", alignment.getSequence(0).c_str(), alignment.getSequence(1).c_str(), alignment.getScore());
}

static PyObject* Sequencing_alignMultipleSequences(PyObject* self, PyObject* args)
{
	PyObject* input_distance_matrix;
	PyObject* input_substitution_matrix;
	PyObject* sequences_list;
	std::vector<std::vector<double> > distance_matrix;
	std::vector<std::vector<MatrixDataType> > substitution_matrix;
	std::vector<Sequence> sequences;

	if ( !PyArg_ParseTuple(args, "OOO", &input_distance_matrix, &input_substitution_matrix, &sequences_list) )
		return NULL;

	// Load the sequences
	sequences = std::vector<Sequence>();
	int sequence_count = PyList_Size(sequences_list);
	for ( int i = 0; i < sequence_count; i++ )
	{
		PyObject* current_sequence = PyList_GetItem(sequences_list, i);
		PyObject* ascii = PyUnicode_AsASCIIString(current_sequence);
		const char* cur_string = PyBytes_AsString(ascii);
		Sequence newSequence = Sequence(std::string(cur_string));
		sequences.push_back(newSequence);
	}

	// load the substitution matrix
	int column_list_size = PyList_Size(input_substitution_matrix);
	int row_list_size = 0;

	if ( column_list_size == 0 )
		return NULL;
	else
	{
		PyObject* row_list = PyList_GetItem(input_substitution_matrix, 0);
		row_list_size = PyList_Size(row_list);
	}
	
	substitution_matrix = std::vector<std::vector<MatrixDataType> >(column_list_size, std::vector<MatrixDataType>(row_list_size, 0));
	
	for ( int i = 0; i < column_list_size; i++ )
	{
		PyObject* row_list = PyList_GetItem(input_substitution_matrix, i);
		if ( !PyList_Check(row_list) )
			return NULL;
		
		for ( int j = 0; j < row_list_size; j++ )
		{
			PyObject* matrix_cell_contents = PyList_GetItem(row_list, j);
			int score = PyLong_AsLong(matrix_cell_contents);
			substitution_matrix[i][j] = score;
		}
	}
	
	// load the distance matrix
	int distance_column_list_size = PyList_Size(input_distance_matrix);
	int distance_row_list_size = 0;

	if ( distance_column_list_size == 0 )
		return NULL;
	else
	{
		PyObject* distance_row_list = PyList_GetItem(input_distance_matrix, 0);
		distance_row_list_size = PyList_Size(distance_row_list);
	}
	
	distance_matrix = std::vector<std::vector<double> >(distance_column_list_size, std::vector<double>(distance_row_list_size, 0));
	
	for ( int i = 0; i < distance_column_list_size; i++ )
	{
		PyObject* distance_row_list = PyList_GetItem(input_distance_matrix, i);
		if ( !PyList_Check(distance_row_list) )
			return NULL;
		
		for ( int j = 0; j < distance_row_list_size; j++ )
		{
			PyObject* matrix_cell_contents = PyList_GetItem(distance_row_list, j);
			int score = PyLong_AsLong(matrix_cell_contents);
			distance_matrix[i][j] = score;
		}
	}

	MultipleSequenceAlignment msa = MultipleSequenceAlignment();
	
	Alignment alignment = msa.align_sequences(distance_matrix, sequences, substitution_matrix);

	PyObject* py_alignment = PyList_New(alignment.size());

	for ( int i = 0; i < alignment.size(); i++ )
	{
		PyObject* py_string = PyUnicodeUCS2_FromString(alignment.getSequence(i).c_str());
		PyList_SetItem(py_alignment, i, py_string);
	}

	return py_alignment;
}

/**
 * This array defines the functions that will be avaliable in the Python module.
 * The following interfaces for these functions in Python are as follows:
 * 
 *     linearSequence(bool global, int gap, listoflists substitution_matrix, string sequence1, string sequence2)
 *     affineSequence(bool global, int open_gap, int extend_gap, listoflists subsitution_matrix, string sequence1, sequence2)
 *     loadSubstitutionMatrix(string filename)
 *     constructNewickTree(listoflists distance_matrix)
 */
static PyMethodDef Sequencing_Methods[] = {
	{"linearSequence", Sequencing_linearSequence, METH_VARARGS, "Linear Sequencing of two Sequences"},
	{"loadSubstitutionMatrix", Sequencing_loadSubstitutionMatrix, METH_VARARGS, "Loads a Substitution Matrix"},
	{"affineSequence", Sequencing_affineSequence, METH_VARARGS, "Affine Sequencing of two Sequnces"},
	{"constructNewickTree", Sequencing_constructNewickTree, METH_VARARGS, "Constructs a Newick tree from a distance Matrix"},
	{"alignMultipleSequences", Sequencing_alignMultipleSequences, METH_VARARGS, "Aligns multiple sequences"},
	{NULL, NULL}
};

/**
 * This structure defines the name of the python module and the methods that
 * are associated with this module.
 */
struct PyModuleDef Sequencing_Definition = 
{
	PyModuleDef_HEAD_INIT,
	"Sequencing",
	NULL,
	-1,
	Sequencing_Methods,
	NULL,
	NULL,
	NULL,
	NULL
};

/**
 * This function is required by Python to initialize the module.
 *
 */
PyMODINIT_FUNC PyInit_Sequencing()
{
	return PyModule_Create(&Sequencing_Definition);
}

#endif