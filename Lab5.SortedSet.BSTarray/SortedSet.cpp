#include "SortedSet.h"
#include "SortedSetIterator.h"

SortedSet::SortedSet(Relation r) : relation(r), capacity(10), root(-1), firstEmpty(0), setSize(0) {
    nodes = new Node[capacity];
    for (int i = 0; i < capacity - 1; ++i) {
        nodes[i].left = i + 1;
    }
    nodes[capacity - 1].left = -1;
}

void SortedSet::resize() {
    Node* newNodes = new Node[capacity * 2];
    for (int i = 0; i < capacity; ++i) {
        newNodes[i] = nodes[i];
    }
    for (int i = capacity; i < capacity * 2 - 1; ++i) {
        newNodes[i].left = i + 1;
    }
    newNodes[capacity * 2 - 1].left = -1;
    firstEmpty = capacity;
    capacity *= 2;
    delete[] nodes;
    nodes = newNodes;
}

bool SortedSet::add(TComp elem) {
    if (root == -1) {
        root = firstEmpty;
        firstEmpty = nodes[firstEmpty].left;
        nodes[root].value = elem;
        nodes[root].left = nodes[root].right = -1;
        setSize++;
        return true;
    }
    int currentNode = root;
    int parent = -1;
    while (currentNode != -1) {
        parent = currentNode;
        if (nodes[currentNode].value == elem) {
            return false;
        } else if (relation(elem, nodes[currentNode].value)) {
            currentNode = nodes[currentNode].left;
        } else {
            currentNode = nodes[currentNode].right;
        }
    }
    int newNode = firstEmpty;
    if (newNode == -1) {
        resize();
        newNode = firstEmpty;
    }
    firstEmpty = nodes[firstEmpty].left;
    nodes[newNode].value = elem;
    nodes[newNode].left = nodes[newNode].right = -1;
    if (relation(elem, nodes[parent].value)) {
        nodes[parent].left = newNode;
    } else {
        nodes[parent].right = newNode;
    }
    setSize++;
    return true;
}

bool SortedSet::remove(TComp elem) {
    int currentNode = root;
    int parent = -1;
    while (currentNode != -1 && nodes[currentNode].value != elem) {
        parent = currentNode;
        if (relation(elem, nodes[currentNode].value)) {
            currentNode = nodes[currentNode].left;
        } else {
            currentNode = nodes[currentNode].right;
        }
    }
    if (currentNode == -1) {
        return false;
    }
    if (nodes[currentNode].left == -1 || nodes[currentNode].right == -1) {
        int child = (nodes[currentNode].left != -1) ? nodes[currentNode].left : nodes[currentNode].right;
        if (parent == -1) {
            root = child;
        } else if (currentNode == nodes[parent].left) {
            nodes[parent].left = child;
        } else {
            nodes[parent].right = child;
        }
    } else {
        int successorParent = currentNode;
        int successor = nodes[currentNode].right;
        while (nodes[successor].left != -1) {
            successorParent = successor;
            successor = nodes[successor].left;
        }
        nodes[currentNode].value = nodes[successor].value;
        if (successorParent == currentNode) {
            nodes[successorParent].right = nodes[successor].right;
        } else {
            nodes[successorParent].left = nodes[successor].right;
        }
    }
    nodes[currentNode].left = firstEmpty;
    firstEmpty = currentNode;
    setSize--;
    return true;
}

bool SortedSet::search(TComp elem) const {
    int currentNode = root;
    while (currentNode != -1) {
        if (nodes[currentNode].value == elem) {
            return true;
        } else if (relation(elem, nodes[currentNode].value)) {
            currentNode = nodes[currentNode].left;
        } else {
            currentNode = nodes[currentNode].right;
        }
    }
    return false;
}

int SortedSet::size() const {
    return setSize;
}

bool SortedSet::isEmpty() const {
    return setSize == 0;
}
SortedSetIterator SortedSet::iterator() const {
    return SortedSetIterator(*this);
}

SortedSet::~SortedSet() {
    delete[] nodes;
}


