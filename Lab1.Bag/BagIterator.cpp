#include <exception>
#include "BagIterator.h"
#include "Bag.h"

using namespace std;


BagIterator::BagIterator(const Bag& c): bag(c), currentPosition(0), currentFrequency(0), elementsVisited(0)
{
	//TODO - Implementation
}

void BagIterator::first() {
	//TODO - Implementation
    currentPosition = 0;
    currentFrequency = 0;
    elementsVisited = 0;
}


void BagIterator::next() {
	//TODO - Implementation
    if (!valid()) {
        throw std::exception();
    }

    ++currentFrequency;
    ++elementsVisited;

    if (currentFrequency >= bag.elements[currentPosition].second) {
        ++currentPosition;
        currentFrequency = 0;
    }
}


bool BagIterator::valid() const {
	//TODO - Implementation
    if(currentPosition < bag.n && elementsVisited < bag.size())
        return true;
    else
	    return false;
}



TElem BagIterator::getCurrent() const
{
	//TODO - Implementation
    if (!valid()) {
        throw std::exception();
    }

    return bag.elements[currentPosition].first;
}
