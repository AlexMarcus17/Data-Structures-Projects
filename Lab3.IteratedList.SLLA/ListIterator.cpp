#include "ListIterator.h"
#include "IteratedList.h"
#include "iostream"
#include <exception>
//Theta(1)
ListIterator::ListIterator(const IteratedList& list) : list(list), currentIndex(list.head) {
	//TODO - Implementation
}
//Theta(1)
void ListIterator::first() {
    currentIndex = list.head;
	//TODO - Implementation
}
//Theta(1)
void ListIterator::next() {
    //TODO - Implementation
    if (!valid()) {
        throw std::exception();
    }
    currentIndex = list.next[currentIndex];
}
//Theta(1)
bool ListIterator::valid() const {
	//TODO - Implementation
    return currentIndex != -1;
}
//Theta(1)
TElem ListIterator::getCurrent() const {
	//TODO - Implementation
    if (!valid()) {
        throw std::exception();
    }
    return list.elements[currentIndex];
}



