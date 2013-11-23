#include <algorithm>
#include "StringScanner.h"

namespace Utilities
{
	StringScanner::StringScanner()
	{
		this->delimiter = this->DEFAULT_DELIMITER;
		this->undo_buffer = std::vector<int>();
	}

	StringScanner::StringScanner(const StringScanner& other)
	{
		this->delimiter = other.delimiter;
	}

	StringScanner::~StringScanner()
	{

	}

	bool StringScanner::open(std::string string)
	{
		this->stream.str(string);
		return true;
	}

	void StringScanner::close()
	{
		this->stream.str("");
		this->end_of_file = false;
		this->undo_buffer.empty();
	}

	void StringScanner::undoScan()
	{
		Scanner::undoScan(this->stream, this->undo_buffer.back());
		this->undo_buffer.pop_back();
	}

	bool StringScanner::eof()
	{
		return Scanner::eof(this->stream);
	}

	std::string StringScanner::getNextToken()
	{
		int total_reads = 0;
		std::string token = Scanner::getNextToken(this->stream, total_reads);
		this->undo_buffer.push_back(total_reads);
		return token;
	}

	std::string StringScanner::getNextLine()
	{
		std::string line = Scanner::getNextLine(this->stream);
		this->undo_buffer.push_back(line.length() + 1); // + 1?
		return line;
	}

	int StringScanner::getNextInt()
	{
		int total_reads = 0;
		int value = Scanner::getNextInt(this->stream, total_reads);
		this->undo_buffer.push_back(total_reads);
		return value;
	}

	long StringScanner::getNextLong()
	{
		int total_reads = 0;
		long value = Scanner::getNextLong(this->stream, total_reads);
		this->undo_buffer.push_back(total_reads);
		return value;
	}

	double StringScanner::getNextDouble()
	{
		int total_reads = 0;
		double value = Scanner::getNextDouble(this->stream, total_reads);
		this->undo_buffer.push_back(total_reads);
		return value;
	}

	char StringScanner::peek()
	{
		return Scanner::peek(this->stream);
	}

	char StringScanner::getNextChar()
	{
		char c = Scanner::getNextChar(this->stream);
		this->undo_buffer.push_back(1);
		return c;
	}
}