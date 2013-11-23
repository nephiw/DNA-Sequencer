#include <vector>
#include "Sequence.h"

#ifndef ___ALIGNMENT___
#define ___ALIGNMENT___

/**
 * The Sequencing namespace holds the basic sequencing classes that are
 * not specific to pairwise sequencing or multiple sequencing.
 */
namespace Sequencing
{
	/**
	 * The Alignment class is responsible for holding the results of an sequencing algorithm.
	 * An Alignment is characterised by the sequences that it contains.
	 */
	class Alignment
	{
	private:

	protected:
		std::vector<Sequence> sequences;

	public:
		/**
		 * Default Constructor.
		 */
		Alignment();

		/**
		 * Creates an Alignment object from the given sequences. The Alignment
		 * simply holds the aligned sequences.
		 * 
		 * @param sequences The vector of aligned sequences that this object
		 * will now represent.
		 */
		Alignment(std::vector<Sequence> sequences);

		/**
		 * Creates a copy of an Alignment.
		 *
		 * @param alignment The alignment to be coppied
		 */
		Alignment(const Alignment& alignment);

		/**
		 * Default Destructor.
		 */
		~Alignment();

		/**
		 * This function returns the number of sequences contained in this alignment.
		 */
		int size();

		/**
		 * Adds a new sequence to this alignment object.
		 */
		void addSequence(Sequence& sequence);

		/**
		 * Return the aligned sequence at the specified index.
		 * 
		 * @param index The index of the alignment to return.
		 */
		Sequence getSequence(unsigned int index);

		/**
		 * Assignment operator
		 *
		 * @param alignment The alignment to be assigned.
		 */
		Alignment& operator = (const Alignment& alignment);
	};
}

#endif