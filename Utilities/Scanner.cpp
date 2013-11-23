#include <algorithm>
#include <iostream>
#include "Scanner.h"

namespace Utilities
{
	Scanner::Scanner()
	{
		this->delimiter = this->DEFAULT_DELIMITER;
		this->end_of_file = false;
	}

	Scanner::~Scanner() {}

	void Scanner::setDelimiter(char new_delimiter)
	{
		this->delimiter = new_delimiter;
	}

	char Scanner::getDelimiter()
	{
		return this->delimiter;
	}

	std::string Scanner::getNextToken(std::istream& stream, int& total_reads)
	{
		std::string token;
		char current_character = this->getNextChar();
		while ( current_character == this->delimiter || current_character == this->NEW_LINE )
		{
			total_reads++;
			current_character = this->getNextChar();
		}

		while ( !stream.eof() && current_character != this->delimiter && current_character != this->NEW_LINE )
		{
			token += current_character;
			total_reads++;
			current_character = this->getNextChar();
		}

		total_reads++;

		if ( stream.eof() == true )
			this->end_of_file = true;

		return token;
	}

	std::string Scanner::getNextLine(std::istream& stream)
	{
		std::string line;
		std::getline(stream, line);
		return line;
	}

	int Scanner::getNextInt(std::istream& stream, int& total_reads)
	{
		std::string number = this->getNextToken(stream, total_reads);
		if ( number.length() == 1 )
		{
			if ( !isdigit(number.at(0)) )
				return (int)number.at(0);
		}
		return atoi(number.c_str());
	}

	long Scanner::getNextLong(std::istream& stream, int& total_reads)
	{
		std::string number = this->getNextToken(stream, total_reads);
		if ( number.length() == 1 )
		{
			if ( !isdigit(number.at(0)) )
				return (int)number.at(0);
		}
		return atol(number.c_str());
	}

	double Scanner::getNextDouble(std::istream& stream, int& total_reads)
	{
		std::string number = this->getNextToken(stream, total_reads);
		if ( number.length() == 1 )
		{
			if ( !isdigit(number.at(0)) )
				return (int)number.at(0);
		}
		return atof(number.c_str());
	}

	char Scanner::peek(std::istream& stream)
	{
		return stream.peek();
	}

	char Scanner::getNextChar(std::istream& stream)
	{
		char c;
		stream.get(c);
		return c;
	}

	void Scanner::undoScan(std::istream& stream, int character_count)
	{
		for ( int i = 0; i < character_count; i++ )
		{
			stream.unget();
			if ( stream.fail() == true )
			{
				stream.clear();
				this->end_of_file = false;
				stream.seekg(-(--character_count), std::ios::end);
				return;
			}
		}
	}

	bool Scanner::eof(std::istream& stream)
	{
		int total_reads = 0;
		std::string token = this->getNextToken(stream, total_reads);
		this->undoScan(stream, total_reads);
		if ( token == "" )
			return true;
		return this->end_of_file;
	}
}