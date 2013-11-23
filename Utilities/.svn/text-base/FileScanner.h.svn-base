#include <fstream>
#include "Scanner.h"

#ifndef ___FILESCANNER___
#define ___FILESCANNER___

/**
 * The utilities namespace holds the basic utilities for scanning strings
 * and files into tokens and retrieving data.
 */
namespace Utilities
{
	/**
	 * The FileScanner class is used to scan a text file and retrieve tokens
	 * based on a specific delimiter or retrieved specific forms of data
	 * delimited by the provided delimiter.
	 */
	class FileScanner : public Scanner
	{
	private:
		std::ifstream file;

	protected:

	public:

		/**
		 * Creates a FileScanner that can be used to scan multiple files.
		 */
		FileScanner();

		/**
		 * Copy Constructor for the FileScanner class. Since ifstreams cannot
		 * be coppied it should be noted that copying this class does not
		 * copy the reference to any open file.
		 *
		 * @param other The other FileScanner to copy data from.
		 */
		FileScanner(const FileScanner& other);

		/**
		 * Default destructor. If this FileScanner has an open file when the destructor
		 * is called, the file will automatically be closed.
		 */
		~FileScanner();

		/**
		 * Opens the text file at the specified string path. This function must
		 * be called before any information about a file can be retrieved.
		 *
		 * @param string - The filename of the file to open.
		 * @return This function returns true if the file was sucessfully opened.
		 */
		bool open(std::string string);

		/**
		 * This function closes the currently open file. If open was not called before
		 * this function, then this function does nothing.
		 */
		void close();

		/**
		 * When retrieving data from a file the current position in the file is maintained.
		 * The history of each modification of the current position in the file is
		 * saved, allowing the user to undo any previous scanning events. For example
		 * if the token "Hello123" was read using getNextToken(), calling undoScan() would
		 * result in the next call to getTextToken() resolving to the same "Hello123" token.
		 */
		void undoScan();

		/**
		 * This funciton indicates when the end of the file has been reached. If the end
		 * of the file has been reached then this function will return true, otherwise
		 * it will return false. (eof = end of file)
		 */
		bool eof();

		/**
		 * This function returns the next token in the file based on the current delimiter.
		 * This function can be undone.
		 */
		std::string getNextToken();

		/**
		 * This function returns the next line of the file based on the standard library
		 * function getline()
		 * This function can be undone.
		 */
		std::string getNextLine();

		/**
		 * This function returns the next integer in the file based on the current delimiter.
		 * This function can be undone.
		 */
		int getNextInt();

		/**
		 * This function returns the next long in the file based on the current delimiter.
		 * This function can be undone.
		 */
		long getNextLong();

		/**
		 * This function return the next double in the file based on the current delimiter.
		 * This function can be undone.
		 */
		double getNextDouble();

		/**
		 * This function returns the next character in the file however does not modify the
		 * the current position in the file.
		 */
		char peek();

		/**
		 * This function returns the next character in the file.
		 * This function can be undone.
		 */
		char getNextChar();
	};
}

#endif