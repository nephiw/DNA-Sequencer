#include <vector>
#include <istream>
#include <string>

#ifndef ___SCANNER___
#define ___SCANNER___

/**
 * The utilities namespace holds the basic utilities for scanning strings
 * and files into tokens and retrieving data.
 */
namespace Utilities
{
	/**
	 * The Scanner class is used to scan a text file and retrieve tokens
	 * based on a specific delimiter or retrieved specific forms of data
	 * delimited by the provided delimiter.
	 */
	class Scanner
	{
	private:

	protected:
		/**
		 * The default constructor of a scanner is not directly acessible. This
		 * class must be extended to create a specific type of scanner implementation.
		 */
		Scanner();

		/**
		 * The default destructor.
		 */
		~Scanner();

		std::string getNextToken(std::istream& stream, int& total_reads);
		std::string getNextLine(std::istream& stream);
		int getNextInt(std::istream& stream, int& total_reads);
		long getNextLong(std::istream& stream, int& total_reads);
		double getNextDouble(std::istream& stream, int& total_reads);
		char peek(std::istream& stream);
		char getNextChar(std::istream& stream);
		void undoScan(std::istream& stream, int character_count);
		bool eof(std::istream& stream);
		int getSingleCharacterCode(std::string& string);

		std::vector<int> undo_buffer;
		char delimiter;
		bool end_of_file;

		static const char WHITE_SPACE = ' ';
		static const char NEW_LINE = '\n';
		static const char RETURN = '\r';
		static const char BACK = '\b';
		static const char TAB = '\t';
		static const char DEFAULT_DELIMITER = WHITE_SPACE;

	public:
		void setDelimiter(char new_delimiter);
		char getDelimiter();

		virtual bool open(std::string) = 0;
		virtual void close() = 0;
		virtual void undoScan() = 0;
		virtual bool eof() = 0;
		virtual std::string getNextToken() = 0;
		virtual std::string getNextLine() = 0;
		virtual int getNextInt() = 0;
		virtual long getNextLong() = 0;
		virtual double getNextDouble() = 0;
		virtual char peek() = 0;
		virtual char getNextChar() = 0;
	};
}

#endif
