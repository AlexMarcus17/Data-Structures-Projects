#pragma once
#include "SortedBag.h"

class SortedBag;

class SortedBagIterator
{
	friend class SortedBag;

private:
	const SortedBag& bag;
	SortedBagIterator(const SortedBag& b);
    ElementFrequencyPair* sortedArray;
    int remainingFrequency;
    int current;

	//TODO - Representation

public:
	TComp getCurrent();
	bool valid();
	void next();
	void first();
};

