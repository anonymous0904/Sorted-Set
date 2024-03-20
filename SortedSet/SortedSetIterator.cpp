#include "SortedSetIterator.h"
#include <exception>

using namespace std;

SortedSetIterator::SortedSetIterator(const SortedSet& m) : ss(m)
{
	currentElement=ss.head;
}


void SortedSetIterator::first() {
	currentElement=ss.head;
}


void SortedSetIterator::next() {
    if(not valid()){
        throw exception();
    }
    currentElement = ss.nodes[currentElement].next;
}


TElem SortedSetIterator::getCurrent()
{
    if(not valid()){
        throw exception();
    }
    return ss.nodes[currentElement].info;
}

bool SortedSetIterator::valid() const {
	if(currentElement!=-1){
        return true;
    }
	return false;
}

