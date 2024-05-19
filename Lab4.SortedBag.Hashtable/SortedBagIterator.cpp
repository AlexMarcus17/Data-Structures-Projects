#include "SortedBagIterator.h"
#include "SortedBag.h"
#include <exception>

using namespace std;

SortedBagIterator::SortedBagIterator(const SortedBag& b) : bag(b), current(0), remainingFrequency(0) {
    sortedArray = new ElementFrequencyPair[b.size()];
    int index = 0;

    for (int i = 0; i < bag.m; ++i) {
        if (bag.e[i].element != -11111) {
            sortedArray[index++] = bag.e[i];
        }
    }

    for (int i = 0; i < index - 1; ++i) {
        for (int j = i + 1; j < index; ++j) {
            if (bag.relation(sortedArray[j].element, sortedArray[i].element)) {
                ElementFrequencyPair temp = sortedArray[i];
                sortedArray[i] = sortedArray[j];
                sortedArray[j] = temp;
            }
        }
    }

    current = 0;
}



TComp SortedBagIterator::getCurrent() {
    if (!valid()) {
        throw std::exception();
    }

    return sortedArray[current].element;
}

bool SortedBagIterator::valid() {
    return current < bag.size();
}

void SortedBagIterator::next() {
    if (!valid()) {
        throw std::exception();
    }

    ++current;


    while (valid() && (sortedArray[current].element == -11111 || remainingFrequency > 1)) {
        if (sortedArray[current].element != -11111) {
            --remainingFrequency;
        }
        ++current;
    }

    if (valid() && sortedArray[current].element != -11111) {
        remainingFrequency = sortedArray[current].frequency;
    }
}

void SortedBagIterator::first() {
    current = 0;

    if (valid() && sortedArray[current].element != -11111) {
        remainingFrequency = sortedArray[current].frequency;
    }
}

