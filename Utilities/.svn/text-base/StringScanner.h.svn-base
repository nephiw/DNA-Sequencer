#include <sstream>
#include "Scanner.h"

#ifndef ___STRINGSCANNER___
#define ___STRINGSCANNER___

/**
 * The utilities namespace holds the basic utilities for scanning strings
 * and files into tokens and retrieving data.
 */
namespace Utilities
{
	/**
	 * The StringScanner class is used to scan a text string and retrieve tokens
	 * based on a specific delimiter or retrieved specific forms of data
	 * delimited by the provided delimiter.
	 */
	class StringScanner : public Scanner
	{
	private:
		std::stringstream stream;

	protected:

	public:
		/**
		 * Creates a FileScanner that can be used to scan multiple strings.
		 */
		StringScanner();

		/**
		 * Copy Constructor for the StringScanner class. Since stringstreams cannot
		 * be coppied it should be noted that copying this class does not
		 * copy the reference to the internal stringstream.
		 *
		 * @param other The other StringScanner to copy data from.
		 */
		StringScanner(const StringScanner& other);

		/**
		 * Default destructor.
		 */
		~StringScanner();

		/**
		 * Opens the scanner on the provided string. This function must
		 * be called before any information about a string can be retrieved.
		 *
		 * @param string - The string that will now be scanned.
		 * @return This function returns true if the stringstream was sucessfully created.
		 */
		bool open(std::string string);

		/**
		 * This function removes the currently loaded string.
		 */
		void close();

		/**
		 * When retrieving data from a string the current position in the string is maintained.
		 * The history of each modification of the current position in the string is
		 * saved, allowing the user to undo any previous scanning events. For example
		 * if the token "Hello123" was read using getNextToken(), calling undoScan() would
		 * result in the next call to getTextToken() resolving to the same "Hello123" token.
		 */
		void undoScan();

		/**
		 * This funciton indicates when the end of the string has been reached. If the end
		 * of the string has been reached then this function will return true, otherwise
		 * it will return false. (eof = end of file)
		 */
		bool eof();

		/**
		 * This function returns the next token in the string based on the current delimiter.
		 * This function can be undone.
		 */
		std::string getNextToken();

		/**
		 * This function returns the next line of the string based on the standard library
		 * function getline()
		 * This function can be undone.
		 */
		std::string getNextLine();

		/**
		 * This function returns the next integer in the string based on the current delimiter.
		 * This function can be undone.
		 */
		int getNextInt();

		/**
		 * This function returns the next long in the string based on the current delimiter.
		 * This function can be undone.
		 */
		long getNextLong();

		/**
		 * This function return the next double in the string based on the current delimiter.
		 * This function can be undone.
		 */
		double getNextDouble();

		/**
		 * This function returns the next character in the string however does not modify the
		 * the current position in the file.
		 */
		char peek();

		/**
		 * This function returns the next character in the string.
		 * This function can be undone.
		 */
		char getNextChar();
	};
}

#endif