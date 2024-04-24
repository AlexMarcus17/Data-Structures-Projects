#include "SMMIterator.h"
#include "SortedMultiMap.h"
#include <iostream>
#include <vector>
#include <exception>
using namespace std;


Node::Node(TElem e, PNod urm) : e(e), nextNode(urm) {}

TElem Node::element() {
    return e;
}

PNod Node::next() {
    return nextNode;
}

//bc - Theta(1)
//wc - Theta(n) - add, search, remove, size, destructor   Theta(1) - others
//overall case - O(n) - add, search, remove, size, destructor   Theta(1) - others


SortedMultiMap::SortedMultiMap(Relation r): first(nullptr), relation(r) {
	//TODO - Implementation
}

void SortedMultiMap::add(TKey c, TValue v) {
	//TODO - Implementation
    PNod newNode = new Node(TElem(c, v), nullptr);
    if (first == nullptr || relation(c, first->element().first)) {
        newNode->nextNode = first;
        first = newNode;
    } else {
        PNod current = first;
        while (current->next() != nullptr && !relation(c, current->next()->element().first)) {
            current = current->next();
        }
        newNode->nextNode = current->next();
        current->nextNode = newNode;
    }
}

vector<TValue> SortedMultiMap::search(TKey c) const {
	//TODO - Implementation
    vector<TValue> values;
    PNod current = first;
    while (current != nullptr && relation(current->element().first, c)) {
        if (current->element().first == c) {
            values.push_back(current->element().second);
        }
        current = current->next();
    }
    return values;
}

bool SortedMultiMap::remove(TKey c, TValue v) {
	//TODO - Implementation
    bool found = false;
    PNod current = first;
    PNod previous = nullptr;
    while (current != nullptr && relation(current->element().first, c)) {
        if (current->element().first == c && current->element().second == v) {
            found = true;
            if (previous == nullptr) {
                first = current->next();
            } else {
                previous->nextNode = current->next();
            }
            delete current;
            break;
        }
        previous = current;
        current = current->next();
    }
    return found;
}


int SortedMultiMap::size() const {
	//TODO - Implementation
    int count = 0;
    PNod current = first;
    while (current != nullptr) {
        count++;
        current = current->next();
    }
    return count;
}

bool SortedMultiMap::isEmpty() const {
	//TODO - Implementation
    return first == nullptr;
}

SMMIterator SortedMultiMap::iterator() const {
    return SMMIterator(*this);
}

SortedMultiMap::~SortedMultiMap() {
	//TODO - Implementation
    while (first != nullptr) {
        PNod temp = first;
        first = first->next();
        delete temp;
    }
}
