#include <algorithm>
#include <iostream>
#include "FileScanner.h"

namespace Utilities
{
	FileScanner::FileScanner()
	{
		this->delimiter = this->DEFAULT_DELIMITER;
		this->undo_buffer = std::vector<int>();
	}

	FileScanner::FileScanner(const FileScanner& other)
	{
		this->delimiter = other.delimiter;
	}

	FileScanner::~FileScanner()
	{
		if ( this->file.is_open() == true )
			this->file.close();
	}

	bool FileScanner::open(std::string string)
	{
		this->file.open(string.c_str());

		if ( !file )
		{
			if ( this->file.is_open() == true )
				this->file.close();
			std::cout << "[Error] Cannot open file: " << string << std::endl;
			return false;
		}
		return true;
	}

	void FileScanner::close()
	{
		if ( this->file.is_open() == true )
			this->file.close();
		this->end_of_file = false;
		this->undo_buffer.empty();
	}

	void FileScanner::undoScan()
	{
		if ( this->file.is_open() == false )
			return;

		Scanner::undoScan(this->file, this->undo_buffer.back());
		this->undo_buffer.pop_back();
	}

	bool FileScanner::eof()
	{
		if ( this->file.is_open() == false )
			return true;

		return Scanner::eof(this->file);
	}

	std::string FileScanner::getNextToken()
	{
		if ( this->file.is_open() == false )
			return "";

		int total_reads = 0;
		std::string token = Scanner::getNextToken(this->file, total_reads);
		this->undo_buffer.push_back(total_reads);
		return token;
	}

	std::string FileScanner::getNextLine()
	{
		if ( this->file.is_open() == false )
			return "";

		std::string line = Scanner::getNextLine(this->file);
		this->undo_buffer.push_back(line.length() + 1);
		return line;
	}

	int FileScanner::getNextInt()
	{
		if ( this->file.is_open() == false )
			return 0;

		int total_reads = 0;
		int value = Scanner::getNextInt(this->file, total_reads);
		this->undo_buffer.push_back(total_reads);
		return value;
	}

	long FileScanner::getNextLong()
	{
		if ( this->file.is_open() == false )
			return 0;

		int total_reads = 0;
		long value = Scanner::getNextLong(this->file, total_reads);
		this->undo_buffer.push_back(total_reads);
		return value;
	}

	double FileScanner::getNextDouble()
	{
		if ( this->file.is_open() == false )
			return 0.0;

		int total_reads = 0;
		double value = Scanner::getNextDouble(this->file, total_reads);
		this->undo_buffer.push_back(total_reads);
		return value;
	}

	char FileScanner::peek()
	{
		if ( this->file.is_open() == false )
			return 0;

		return Scanner::peek(this->file);
	}

	char FileScanner::getNextChar()
	{
		if ( this->file.is_open() == false )
			return 0;

		char c = Scanner::getNextChar(this->file);
		this->undo_buffer.push_back(1);
		return c;
	}
}