#include "SMMIterator.h"
#include "SortedMultiMap.h"

SMMIterator::SMMIterator(const SortedMultiMap& map) : map(map), current(map.first) {
}

void SMMIterator::first() {
    current = map.first;
}

void SMMIterator::next() {
    if (!valid()) {
        throw exception();
    }
    if (valid()) {
        current = current->next();
    }
}

bool SMMIterator::valid() const {
    return current != nullptr;
}

TElem SMMIterator::getCurrent() const {
    if (!valid()) {
        throw exception();
    }

    return current->element();
}

//Theta(1) - all cases

