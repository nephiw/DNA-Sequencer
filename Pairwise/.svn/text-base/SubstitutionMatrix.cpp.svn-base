#include <fstream>
#include <iostream>
#include "SubstitutionMatrix.h"

namespace Pairwise
{
	SubstitutionMatrix::SubstitutionMatrix()
	{
		this->matrix_has_corner = false;
	}

	SubstitutionMatrix::SubstitutionMatrix(std::vector<std::vector<MatrixDataType> >& input_matrix)
	{
		this->matrix = input_matrix;
		this->matrix_has_corner = false;
	}

	SubstitutionMatrix::~SubstitutionMatrix() {}

	bool SubstitutionMatrix::load(std::string filename)
	{
		this->matrix = std::vector<std::vector<MatrixDataType> >();
		Utilities::FileScanner fileScanner = Utilities::FileScanner();
		std::string currentLine;

		if ( !fileScanner.open(filename) )
		{
			std::cout << "[Error] Substitution matrix file not found: Given[" << filename << "]" << std::endl;
			return false;
		}

		this->scanComments(fileScanner);
		this->scanMatrix(fileScanner);
		return true;
	}

	void SubstitutionMatrix::scanComments(Utilities::FileScanner& fileScanner)
	{
		std::string currentLine;
		this->comments = std::vector<std::string>();
		while ( (currentLine = fileScanner.getNextLine()).at(0) == COMMENT_SYMBOL )
			this->comments.push_back(currentLine);
		fileScanner.undoScan();
	}

	void SubstitutionMatrix::scanMatrix(Utilities::FileScanner& fileScanner)
	{
		std::string currentLine;
		while ( !fileScanner.eof() )
		{
			currentLine = fileScanner.getNextLine();
			std::vector<MatrixDataType> row = this->scanMatrixLine(currentLine);
			static int last_row_length = row.size();
			if ( last_row_length != row.size() )
				std::cout << "[Warning] Substitution matrix row lengths varry: Expected[len:" << last_row_length << "] Found[len:" << row.size() << "]" << std::endl;
			this->matrix.push_back(row);
		}
	}

	std::vector<MatrixDataType> SubstitutionMatrix::scanMatrixLine(std::string line)
	{
		Utilities::StringScanner stringScanner = Utilities::StringScanner();
		stringScanner.open(line);
		std::vector<MatrixDataType> row = std::vector<MatrixDataType>();

		if ( this->matrix_has_corner == false )
		{
			row.push_back(UNKNOWN_SYMBOL);
			this->matrix_has_corner = true;
		}

		while ( !stringScanner.eof() )
			row.push_back(toupper(stringScanner.getNextInt()));

		stringScanner.close();
		return row;
	}

	void SubstitutionMatrix::print(std::ostream& stream)
	{
		for ( unsigned int i = 0; i < this->comments.size(); i++ )
			stream << this->comments.at(i) << std::endl;

		for ( unsigned int i = 0; i < this->matrix.size(); i++ )
		{
			for ( unsigned int j = 0; j < this->matrix[i].size(); j++ )
			{
				if ( i == 0 || j == 0 )
					stream << (char)(this->matrix[i][j]) << "\t";
				else
					stream << this->matrix[i][j] << "\t";
			}
			stream << std::endl;
		}
	}

	int SubstitutionMatrix::getColumnCount() const
	{
		return this->matrix.size();
	}

	int SubstitutionMatrix::getRowCount() const
	{
		return this->matrix[0].size();
	}

	MatrixDataType SubstitutionMatrix::get(int i, int j) const
	{
		return this->matrix[i][j];
	}

	int SubstitutionMatrix::score(const char nucleotide1, const char nucleotide2) const
	{
		int nucleotideIndex1 = 0;
		int nucleotideIndex2 = 0;

		for ( unsigned int i = 0; i < this->matrix.size(); i++ )
			if ( (char)(this->matrix[0][i]) == toupper(nucleotide1) )
				nucleotideIndex1 = i;

		if ( nucleotideIndex1 == 0 )
			return 0;

		for ( unsigned int i = 0; i < this->matrix.size(); i++ )
			if ( (char)(this->matrix[i][0]) == toupper(nucleotide2) )
				nucleotideIndex2 = i;

		if ( nucleotideIndex2 == 0 )
			return 0;

		int score = this->matrix[nucleotideIndex2][nucleotideIndex1];

		return score;
	}

	char SubstitutionMatrix::getGapCharacter() const
	{
		return this->GAP_CHARACTER;
	}
}