#include "SortedSetIterator.h"
#include <exception>

using namespace std;

SortedSetIterator::SortedSetIterator(const SortedSet& m) : multime(m), currentNode(-1) {
}

void SortedSetIterator::first() {
    currentNode = multime.root;
    while (multime.nodes[currentNode].left != -1) {
        currentNode = multime.nodes[currentNode].left;
    }
}

void SortedSetIterator::next() {
    if (!valid()) {
        throw std::exception();
    }
    if (multime.nodes[currentNode].right != -1) {
        currentNode = multime.nodes[currentNode].right;
        while (multime.nodes[currentNode].left != -1) {
            currentNode = multime.nodes[currentNode].left;
        }
    } else {
        int parent = -1;
        int node = multime.root;
        while (node != currentNode) {
            if (multime.relation(multime.nodes[currentNode].value, multime.nodes[node].value)) {
                parent = node;
                node = multime.nodes[node].left;
            } else {
                node = multime.nodes[node].right;
            }
        }
        currentNode = parent;
    }
}

TElem SortedSetIterator::getCurrent() {
    if (!valid()) {
        throw std::exception();
    }
    return multime.nodes[currentNode].value;
}

bool SortedSetIterator::valid() const {
    return currentNode != -1;
}

