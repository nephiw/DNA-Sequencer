#include <string>
#include <vector>
#include "../Utilities/FileScanner.h"
#include "../Utilities/StringScanner.h"

#ifndef ___SUBSTITUTIONMATRIX___
#define ___SUBSTITUTIONMATRIX___

/**
 * The pairwise namespace contains all of the data structures and
 * algorithms related to pairwise sequencing (The alignment of only
 * two nucleotide or protein sequences at a time)
 */
namespace Pairwise
{
	typedef int MatrixDataType;

	/**
	 * The SubstitutionMatrix class provides a centralized location for determining the
	 * match and mismatch scores between two nucleotide or protein characters contained
	 * in a sequence. The purpose of this class is to load the common substitution matrix
	 * file format and perform basic queries on the loaded matrix to determine the match
	 * or mismatch score between two sequence characters.
	 */
	class SubstitutionMatrix
	{
	private:
		static const char COMMENT_SYMBOL = '#';
		static const char UNKNOWN_SYMBOL = '*';
		static const char GAP_CHARACTER = '-';
		std::vector<std::vector<MatrixDataType> > matrix;
		std::vector<std::string> comments;
		bool matrix_has_corner;

		void scanComments(Utilities::FileScanner& fileScanner);
		void scanMatrix(Utilities::FileScanner& fileScanner);
		std::vector<MatrixDataType> scanMatrixLine(std::string line);

	public:
		/**
		 * Default Constructor.
		 */
		SubstitutionMatrix();

		/**
		 * Creates a substitution matrix from a vector of vectors.
		 *
		 * @param input_matrix The matrix to store in a new SubstitutionMatrix object.
		 */
		SubstitutionMatrix(std::vector<std::vector<MatrixDataType> >& input_matrix);

		/**
		 * Default Destructor.
		 */
		~SubstitutionMatrix();

		/**
		 * This function loads a substitution matrix from the provided text file name.
		 * The file must contain a valid substitution matrix of the following form:
		 * 
		 * # Comments start with the # character
		 * # Protein or nucleotide representative characters should be listed as single
		 * # characters:
		 *    A  C  G  T
		 * A  1 -1 -1 -1
		 * C -1  1 -1 -1
		 * G -1 -1  1 -1
		 * T -1 -1 -1  1
		 */
		bool load(std::string filename);
		
		/**
		 * Prints this substitution to the provided stream.
		 * 
		 * @param stream The stream to print this matrix to
		 */
		void print(std::ostream& stream);

		/**
		 * This function returns the number of columns in this substitution matrix.
		 *
		 * @return The number of columns in this substitution matrix.
		 */
		int getColumnCount() const;

		/**
		 * This function returns the number of rows in this substitution matrix.
		 *
		 * @return The number of rows in this substitution matrix.
		 */
		int getRowCount() const;

		/**
		 * This function returns the score value between two protein or nucleotide
		 * representative characters.
		 *
		 * @param i The column index.
		 * @param j The row index.
		 */
		MatrixDataType get(int i, int j) const;

		/**
		 * This function performs a basic query of the score between two nucleotides or
		 * protein representative characters.
		 *
		 * @param nucleotide1 The first representative character. This character must be in
		 * the substitution matrix for a valid result.
		 * @param nucleotide2 The second representative character. This character must be in
		 * the substitution matrix for a valid result.
		 * @return The match or mismatch score associated with the provided characters.
		 */
		int score(const char nucleotide1, const char nucleotide2) const;

		/**
		 * Returns the gap character associated with this substitution matrix.
		 *
		 * @return The gap character.
		 */
		char getGapCharacter() const;
	};
}
#endif