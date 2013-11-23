#include <string>
#include <iostream>

#ifndef ___SEQUENCE___
#define ___SEQUENCE___

/**
 * The Sequencing namespace holds the basic sequencing classes that are
 * not specific to pairwise sequencing or multiple sequencing.
 */
namespace Sequencing
{
	/**
	 * The Sequence class represents a sequence of characters that can be used to
	 * represent a nucleotide sequence or protein sequence. Sequences also contain
	 * a name identifier as well as a flag to represent if the sequence contains
	 * gap characters.
	 */
	class Sequence
	{
	private:
		std::string name;
		std::string sequence;
		bool gapped;

	protected:

	public:
		/**
		 * Default Constructor.
		 */
		Sequence();

		/**
		 * Creates a new sequence from a string that represents the raw character
		 * data of the sequence.
		 *
		 * @param sequence The raw character data represented in a string to be
		 * stored in this Sequence object.
		 */
		Sequence(std::string sequence);

		/**
		 * Creates a new sequence from a string that represents the raw character data
		 * of the sequence as well as the sequence name.
		 *
		 * @param name The name of the new sequence
		 * @param sequence The raw character data represented in a string to be stored
		 * in this sequence object.
		 */
		Sequence(std::string name, std::string sequence);

		/**
		 * Copy Constructor
		 *
		 * @param sequence The sequence to be coppied.
		 */
		Sequence(const Sequence& sequence);

		/**
		 * Default Destructor.
		 */
		~Sequence();
		
		/**
		 * Appends the provided character to the end of this sequence object.
		 *
		 * @param nucleotide This character represents a nucleotide (or protein component)
		 * of the sequence.
		 */
		void append(const char nucleotide);

		/**
		 * Prepends the provided character to the end of this sequence object.
		 *
		 * @param nucleotide This character represents a nucleotide (or protein component)
		 * of the sequence.
		 */
		void prepend(const char nucleotide);

		/**
		 * This function returns true if the contained sequence is gapped.
		 * 
		 * @return If this sequence is gapped then this function will return
		 * true otherwise false.
		 */
		bool isGapped();

		/**
		 * This function returns the length of this Sequence.
		 *
		 * @return The length of the sequence.
		 */
		int length() const;

		/**
		 * This function returns the name of the Sequence.
		 *
		 * @return The name of the sequence.
		 */
		std::string getName() const { return name; };

		/**
		 * This function returns the string sequence.
		 *
		 * @return The sequence of the sequence.
		 */
		std::string getSequence() { return sequence; };

		/**
		 * This operator returns the specific nucleotide character at the provided
		 * index. 
		 *
		 * @param index The index of the nucleotide to return.
		 * @return The representational character of the nucleotide or protein sequence.
		 */
		char operator [] (unsigned int index) const;

		/**
		 * Assignment Operator
		 *
		 * @param other The sequence to be assigned.
		 */
		Sequence& operator = (const Sequence& other);

		/**
		 * This operator appends a representative nucleotide or protein character to
		 * the end of this sequence.
		 *
		 * @param nucleotide The representative nucleotide character to be appended
		 * to the end of this sequence.
		 */
		void operator += (const char nucleotide);

		/**
		 * This helper function provides the raw character pointer to the string
		 * representation of this sequence.
		 *
		 * @return Returns a character pointer to this sequence.
		 */
		const char* c_str() const;

		/**
		 * This operator allows this object to be placed in a simple cout stream.
		 */
		friend std::ostream& operator << (std::ostream& out, const Sequence& sequence);
	};
}

#endif