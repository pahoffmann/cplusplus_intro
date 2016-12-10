#include "SparseVector.hpp"
#include <iostream>


/**private**
*         *
**********/

void SparseVector::clear(){

	node *actual=start;
	node *next;
	while(actual){
		next = actual->next;
		delete actual;
		actual = next;
	}
}

void SparseVector::copy(const SparseVector &other){
	size = other.size;
	actSize = other.actSize;
	if(!other.start){
                this->start = 0;
        }
        else if(this != &other){

                node *copy = start;
                node *original = other.start;
                while(original){

                        copy = new node(original->index,original->value,0);
                        copy = copy->next;
                        original = original->next;

                }
        }else{
                this->start = other.start;
        }

}




/**public**
*         *
**********/


/* constructor with size */
SparseVector::SparseVector(int size) /*: start(0,0,0)*/{
	this->size = size;
	actSize = 1;
	start = new node (0,0,0);
}

/* Copy - Constructor */
SparseVector::SparseVector(const SparseVector &other){
	
	copy(other);
	
}


/* = operator */

SparseVector& SparseVector::operator=(const SparseVector &other){ 
	
	if(this != &other){
		clear();
		copy(other);
	}	
	return *this;
}



int SparseVector::getSize(){
	return size;
}


SparseVector::~SparseVector(){

	clear();
}
