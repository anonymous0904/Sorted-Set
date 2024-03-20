#pragma once
#include "SortedSet.h"

class SortedSetIterator
{
	friend class SortedSet;
private:
	const SortedSet& ss;
	SortedSetIterator(const SortedSet& m);
    int currentElement;


public:
    //iterator moves on the first position of the list
	void first();

    //iterates over the next position in the list
    void next();

    //returns the element at the current position of the iterator
	TElem getCurrent();

    //returns true if the current position of the iterator in the list is pointing to a valid element, false otherwise
	bool valid() const;
};

