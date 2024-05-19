#include <stdexcept>
#include "SortedBag.h"
#include "SortedBagIterator.h"
#include "cmath"

SortedBag::SortedBag(Relation r): m(MAX), firstEmpty(0), relation(r), lenght(0) {
	//TODO - Implementation
    for (int i = 0; i < m; ++i) {
        e[i].element = -11111;
        e[i].frequency = 0;
        urm[i] = -1;
    }
}


void SortedBag::add(TComp e) {
	//TODO - Implementation

    int position = h(e);

    if (this->e[position].element == -11111) {
        this->e[position].element = e;
        this->e[position].frequency = 1;
        this->lenght++;
        return;
    }

    if (this->e[position].element == e) {
        this->e[position].frequency++;
        this->lenght++;
        return;
    }


    this->e[firstEmpty].element = e;
    this->e[firstEmpty].frequency = 1;
    int i = position;
    while (this->urm[position] != -1)
        i = this->urm[i];
    this->urm[i] = this->firstEmpty;
    while (this->e[this->firstEmpty].element != -11111)
        this->firstEmpty++;


    this->lenght++;



}


bool SortedBag::remove(TComp e) {
	//TODO - Implementation
    if (!search(e))
        return false;
    int position = h(e);

    int i = position;
    int previous = -1;
    int nextPos = this->urm[i];
    while (this->e[i].element != e)
    {
        previous = i;
        i = nextPos;
        nextPos = this->urm[i];
    }
    if(this->e[i].frequency > 1) {
        this->e[i].frequency--;
    } else {

        if (nextPos == -1) {
            this->urm[previous] = -1;
            this->e[i].element = -11111;
            this->e[i].frequency = 0;
            if (this->firstEmpty > i)
                this->firstEmpty = i;
        } else {
            if (h(this->e[nextPos].element) == nextPos) {
                this->urm[previous] = nextPos;
                this->e[i].element = -11111;
                this->e[i].frequency = 0;
                this->urm[i] = -1;
                if (this->firstEmpty > i)
                    this->firstEmpty = i;
            } else {
                this->e[i].element = this->e[nextPos].element;
                this->e[i].frequency = this->e[nextPos].frequency;
                this->urm[i] = this->urm[nextPos];
                this->e[nextPos].element = -11111;
                this->e[nextPos].frequency = 0;
                this->urm[nextPos] = -1;
                if (this->firstEmpty > nextPos)
                    this->firstEmpty = i;
            }
        }
    }
    this->lenght--;

    return true;
}


bool SortedBag::search(TComp elem) const {
	//TODO - Implementation
    int position = h(elem);

    int i = position;
    if (this->e[i].element == elem)
        return true;
    while (this->urm[i] != -1)
    {
        i = this->urm[i];
        if (this->e[i].element == elem)
            return true;
    }
    return false;
}


int SortedBag::nrOccurrences(TComp elem) const {
	//TODO - Implementation

    int position = h(elem);

    int i = position;
    if (this->e[i].element == elem)
        return e[i].frequency;
    while (this->urm[i] != -1)
    {
        i = this->urm[i];
        if (this->e[i].element == elem)
            return e[i].frequency;
    }
    return 0;
}



int SortedBag::size() const {
	//TODO - Implementation
    return this->lenght;
}


bool SortedBag::isEmpty() const {
	//TODO - Implementation
    return size() == 0;
}


SortedBagIterator SortedBag::iterator() const {
	return SortedBagIterator(*this);
}


SortedBag::~SortedBag() {
	//TODO - Implementation
}

int SortedBag::h(TElem e) const {
    return abs(e) % m;
}
