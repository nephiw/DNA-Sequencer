#include "Sequence.h"

namespace Sequencing
{
	Sequence::Sequence()
	{
		
	}

	Sequence::Sequence(std::string sequence)
	{
		this->name = "Sequence";
		this->sequence = sequence;
	}

	Sequence::Sequence(std::string name, std::string sequence)
	{
		this->name = name;
		this->sequence = sequence;
	}

	Sequence::Sequence(const Sequence& sequence)
	{
		this->name = sequence.name;
		this->sequence = sequence.sequence;
	}

	Sequence::~Sequence()
	{

	}

	void Sequence::append(const char nucleotide)
	{
		this->sequence += nucleotide;
	}

	void Sequence::prepend(const char nucleotide)
	{
		this->sequence = nucleotide + this->sequence;
	}

	bool Sequence::isGapped()
	{
		return this->gapped;
	}

	int Sequence::length() const
	{
		return this->sequence.length();
	}

	char Sequence::operator [] (unsigned int index) const
	{
		if ( index < 0 || index >= this->sequence.length() )
			return 0;
		return this->sequence[index];
	}

	Sequence& Sequence::operator = (const Sequence& other)
	{
		this->sequence = other.sequence;
		this->gapped = other.gapped;
		return *this;
	}

	void Sequence::operator += (const char nucleotide)
	{
		this->sequence += nucleotide;
	}

	const char* Sequence::c_str() const
	{
		return this->sequence.c_str();
	}

	std::ostream& operator << (std::ostream& out, const Sequence& sequence)
	{
		out << sequence.c_str();
		return out;
	}
}