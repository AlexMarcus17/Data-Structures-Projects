#include <exception>
#include <iostream>
#include "ListIterator.h"
#include "IteratedList.h"
//Theta(capacity)
IteratedList::IteratedList() {
    capacity = 10;
    elements = new TElem[capacity];
    next = new int[capacity];
    head = -1;
    firstEmpty = 0;
    for (int i = 0; i < capacity - 1; i++) {
        next[i] = i + 1;
    }
    next[capacity - 1] = -1;
}
//bc - Theta(1)
//wc - Theta(n)
//oc - O(n)
int IteratedList::size() const {
    int count = 0;
    int current = head;
    while (current != -1) {
        count++;
        current = next[current];
    }
    return count;
}
//Theta(1)
bool IteratedList::isEmpty() const {
    return head == -1;
}
//Theta(1)
ListIterator IteratedList::first() const {
    return ListIterator(*this);
}
//Theta(1)
TElem IteratedList::getElement(ListIterator pos) const {
    if (!pos.valid())
        throw std::exception();

    return elements[pos.currentIndex];
}
//bc - Theta(1)
//wc - Theta(n)
//ac - O(n)
TElem IteratedList::remove(ListIterator& pos) {
    if (!pos.valid())
        throw std::exception();

    int current = head;
    int previous = -1;
    while (current != pos.currentIndex) {
        previous = current;
        current = next[current];
    }

    if (previous == -1) {
        head = next[current];
    } else {
        next[previous] = next[current];
    }

    TElem removedElement = elements[current];
    next[current] = firstEmpty;
    firstEmpty = current;

    pos.currentIndex = next[pos.currentIndex];
    return removedElement;
}
//bc - Theta(1)
//wc - Theta(n)
//ac - O(n)
ListIterator IteratedList::search(TElem e) const {
    ListIterator it = first();
    while (it.valid()) {
        if (elements[it.currentIndex] == e)
            return it;
        it.next();
    }
    ListIterator invalidit = ListIterator(*this);
    invalidit.currentIndex = -1;
    return invalidit;
}
//bc - Theta(1)
//wc - Theta(1)
//ac - Theta(1)
TElem IteratedList::setElement(ListIterator pos, TElem e) {
    if (!pos.valid())
        throw std::exception();

    TElem oldElement = elements[pos.currentIndex];
    elements[pos.currentIndex] = e;
    pos.currentIndex = -1;
    return oldElement;
}
//bc - Theta(1)
//wc - Theta(1)
//ac - Theta(1)
void IteratedList::addToPosition(ListIterator& pos, TElem e) {
    if (!pos.valid())
        throw std::exception();

    int newNode = allocateNode(e);
    next[newNode] = next[pos.currentIndex];
    next[pos.currentIndex] = newNode;
    pos.currentIndex = newNode;
}
//bc - Theta(1)
//wc - Theta(1)
//ac - Theta(1)
void IteratedList::addToBeginning(TElem e) {
    int newNode = allocateNode(e);
    next[newNode] = head;
    head = newNode;
}
//bc - Theta(1)
//wc - Theta(n)
//ac - O(n)
void IteratedList::addToEnd(TElem e) {
    int newNode = allocateNode(e);
    if (head == -1) {
        head = newNode;
    } else {
        int current = head;
        while (next[current] != -1) {
            current = next[current];
        }
        next[current] = newNode;
    }
}
//Theta(1)
//Theta(1)
//Theta(1)
IteratedList::~IteratedList() {
    delete[] elements;
    delete[] next;
}
//bc - Theta(1)
//wc - Theta(1)
//ac - Theta(1)
int IteratedList::allocateNode(TElem e) {
    if (firstEmpty == -1) {
        resize();
    }

    int newNode = firstEmpty;
    firstEmpty = next[firstEmpty];

    elements[newNode] = e;
    next[newNode] = -1;
    return newNode;
}
//bc - Theta(1)
//wc - Theta(n)
//ac - O(n)
void IteratedList::resize() {
    int newCapacity = capacity * 2;

    TElem* newElements = new TElem[newCapacity];
    int* newNext = new int[newCapacity];

    for (int i = 0; i < capacity; ++i) {
        newElements[i] = elements[i];
        newNext[i] = next[i];
    }

    for (int i = capacity; i < newCapacity; ++i) {
        newNext[i] = i + 1;
    }
    newNext[newCapacity - 1] = -1;

    capacity = newCapacity;
    firstEmpty = capacity / 2;

    delete[] elements;
    delete[] next;
    elements = newElements;
    next = newNext;
}
