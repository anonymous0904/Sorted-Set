#include "SortedSet.h"
#include "SortedSetIterator.h"
#include <iostream>
using namespace std;

SortedSet::SortedSet(Relation r) {
	setSize=0;
    capacity=10;
    head=-1;
    tail=-1;
    firstEmpty=0;
    nodes=new DLLANode[capacity];
    relation=r;
    for(int i=0;i<capacity-1;i++){
        nodes[i].next=i+1;
    }
    nodes[capacity-1].next=-1;
    for(int i=0;i<capacity;i++){
        nodes[i].prev=i-1;
    }
}

SortedSet::SortedSet(const SortedSet &original) {
    this->setSize=original.setSize;
    this->capacity=original.capacity;
    this->head=original.head;
    this->tail=original.tail;
    this->firstEmpty=original.firstEmpty;
    this->nodes=new DLLANode[this->capacity];
    auto current=original.head;
    while(current!=-1){
        this->nodes[current]=original.nodes[current];
        current=nodes[current].next;
    }
    current=firstEmpty;
    while(current!=-1){
        this->nodes[current]=original.nodes[current];
        current=nodes[current].next;
    }
}

void SortedSet::resize() {
    auto*aux=new DLLANode[capacity*2];

    for(int i=0;i<capacity;i++){
        aux[i]=nodes[i];
    }
    delete[]nodes;
    nodes=aux;
    if(firstEmpty==-1){
        firstEmpty=capacity;
    }
    capacity*=2;
    for(int i=firstEmpty;i<capacity-1;i++){
        nodes[i].next=i+1;
    }
    nodes[capacity-1].next=-1;
    nodes[firstEmpty].prev=-1;
    for(int i=firstEmpty+1;i<capacity;i++){
        nodes[i].prev=i-1;
    }
}

bool SortedSet::add(TComp e) {
    if(isEmpty()){
        nodes[firstEmpty].info=e;
        nodes[firstEmpty].prev=-1;
        head=tail=firstEmpty;
        firstEmpty=nodes[firstEmpty].next;
        nodes[head].next=-1;
        setSize++;
        return true;
    }

    int current=head;
    int prevPos=-1;
    while(current!=-1 and relation(nodes[current].info,e)){
        if(nodes[current].info==e){
            return false;
        }
        prevPos=current;
        current=nodes[current].next;//search the correct position of e in the array
    }
    if(current!=-1 and nodes[current].info==e){//e is already in the array
        return false;
    }

    if(firstEmpty==-1){//the array is full
        resize();
    }

    int aux = firstEmpty;
    firstEmpty = nodes[firstEmpty].next;
    nodes[aux].info=e;

    if(current==head){//add at the beginning
        nodes[aux].prev=-1;
        nodes[aux].next=head;
        nodes[head].prev=aux;
        head=aux;
    }
    else {
        if (current != -1) {//add in the middle
            nodes[aux].prev=prevPos;
            nodes[aux].next=current;
            nodes[current].prev=aux;
            nodes[prevPos].next=aux;

        } else {//add at the end
            nodes[tail].next = aux;
            nodes[aux].prev = tail;
            nodes[aux].next = -1;
            tail = aux;
        }
    }
    setSize++;
    return true;

}

bool SortedSet::remove(TComp elem) {
    int current = head;
    while (current != -1 and nodes[current].info != elem) {
        if (not relation(nodes[current].info, elem)) {
            return false;
        }
        current = nodes[current].next;
    }

    if (current == -1) {
        return false;
    }

    if (current == head) {
        head = nodes[current].next;
        if(head!=-1) {
            nodes[head].prev = -1;
        }
    } else {
        int prevNode = nodes[current].prev;
        int nextNode = nodes[current].next;
        if (prevNode != -1) {
            nodes[prevNode].next = nextNode;
        }
        if (nextNode != -1) {
            nodes[nextNode].prev = prevNode;
        }
    }
    nodes[current].prev = -1;
    nodes[current].next = firstEmpty;
    firstEmpty = current;
    setSize--;
    return true;

}

bool SortedSet::search(TComp elem) const {
    int current=head;
    while(nodes[current].info!=elem and current!=-1){
        if(not relation(nodes[current].info,elem)){
            break;
        }
        current=nodes[current].next;
    }
    if(current!=-1 and nodes[current].info==elem){
        return true;
    }
    return false;
}


int SortedSet::size() const {
	return setSize;
}


bool SortedSet::isEmpty() const {
	if(setSize==0){
        return true;
    }
	return false;
}

SortedSetIterator SortedSet::iterator() const {
	return SortedSetIterator(*this);
}


void SortedSet::printSet() {
    auto current=head;
    cout<<endl;
    while(current!=-1){
        cout<<nodes[current].info<<' ';
        current=nodes[current].next;
    }
    cout<<endl;
}

SortedSet::~SortedSet() {
	delete[]nodes;
}

