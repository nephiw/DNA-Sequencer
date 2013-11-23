#include "Alignment.h"

namespace Sequencing
{
	Alignment::Alignment()
	{

	}

	Alignment::Alignment(std::vector<Sequence> sequences)
	{
		this->sequences = sequences;
	}

	Alignment::Alignment(const Alignment& alignment)
	{
		this->sequences = alignment.sequences;
	}

	Alignment::~Alignment()
	{

	}

	int Alignment::size()
	{
		return this->sequences.size();
	}

	void Alignment::addSequence(Sequence& sequence)
	{
		this->sequences.push_back(sequence);
	}

	Sequence Alignment::getSequence(unsigned int index)
	{
		if ( index < 0 || index >= this->sequences.size() )
			return Sequence();
		return this->sequences.at(index);
	}

	Alignment& Alignment::operator = (const Alignment& alignment)
	{
		this->sequences = alignment.sequences;
		return *this;
	}
}