#include "Bag.h"
#include "BagIterator.h"
#include <exception>
#include <iostream>
using namespace std;


// wc - Theta(1)
// bc - Theta(1)
// ac - Theta(1)


Bag::Bag() {
	//TODO - Implementation
    this->cp = 1;
    this->n = 0;
    this->elements = new ElementFrequencyPair[cp];
}
// wc - Theta(n)
// bc - Theta(1)
// ac - O(n)

void Bag::resize() {
    int newCapacity = 2 * cp;
    ElementFrequencyPair *newElements = new ElementFrequencyPair[newCapacity];

    for (int i = 0; i < n; ++i) {
        newElements[i] = elements[i];
    }

    cp = newCapacity;
    delete[] elements;
    elements = newElements;
}




void Bag::incrementFrequency(TElem elem) {
    for (int i = 0; i < n; ++i) {
        if (elements[i].first == elem) {
            ++elements[i].second;
            return;
        }
    }
}


void Bag::add(TElem elem) {
	//TODO - Implementation
    if (n == cp) {
        resize();
    }

    if (!search(elem)) {
        elements[n] = std::make_pair(elem, 1);
        ++n;
    } else {
        incrementFrequency(elem);
    }
}


bool Bag::remove(TElem elem) {
	//TODO - Implementation


    int index = -1;
    for (int i = 0; i < n; ++i) {
        if (elements[i].first == elem) {
            index = i;
            break;
        }
    }

    if (index != -1) {
        if (elements[index].second > 1) {
            --(elements[index].second);
        } else {
            elements[index] = elements[n - 1];
            --n;
        }
        return true;
    }

    return false;
}


bool Bag::search(TElem elem) const {
	//TODO - Implementation

    for (int i = 0; i < n; ++i) {
        if (elements[i].first == elem) {
            return true;
        }
    }

	return false; 
}

int Bag::nrOccurrences(TElem elem) const {
	//TODO - Implementation

    for (int i = 0; i < n; ++i) {
        if (elements[i].first == elem) {
            return elements[i].second;
        }
    }

	return 0; 
}


int Bag::size() const {
	//TODO - Implementation

    int totalElements = 0;
    for (int i = 0; i < n; ++i) {
        totalElements += elements[i].second;
    }
    if(totalElements>0)
        return totalElements;
    else
	    return 0;
}


bool Bag::isEmpty() const {
	//TODO - Implementation
    if(n==0)
        return 1;
    else
	    return 0;
}

BagIterator Bag::iterator() const {
	return BagIterator(*this);
}


Bag::~Bag() {
	//TODO - Implementation
    delete[] elements;
}

