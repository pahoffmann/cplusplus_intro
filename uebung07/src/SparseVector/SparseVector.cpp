#include "SparseVector.hpp"
#include <iostream>


/**private**
*         *
**********/


/**
 * @brief adds a nonzero element to the list according to its index
 */
void SparseVector::setNonzeroElem(int index, int value){
	node *temp;
	node *next;
	temp = start;
	while(temp->next != NULL){
		if(temp->index > index){
			break;
		}

		next = temp->next;
		delete temp;
		temp = next;

	}

	if(temp->next == NULL){
		temp->next = new node(index, value, 0);
	} else {
		next = temp->next;
		temp->next = new node (index, value, next);
	}
}


/**
 * @brief removes an element from the list
 */
void SparseVector::removeElem(int index){
	node *temp;
	node *next;
	temp = start;

	while(temp){
		if (temp->index == index){
			next = temp->next;
			delete temp;
			temp = next;
		}
	}
}

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

	if (!other.start){
    	this->start = 0;
	} else if (this != &other){
	  node *copy = start;
	  node *original = other.start;

	  while(original){
		  copy = new node(original->index,original->value,0);
		  copy = copy->next;
		  original = original->next;
	  }
  } else {
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

int SparseVector::getElem(int index){
	if (this->actSize == 0){
		std::cerr << "No element in list" << std::endl;
		return 0;
	}

	node *temp;
	node *next;
	temp = start;
	while(temp){
		if(temp->index == index){
			return temp->value;
			break;
		}
		next = temp->next;
		delete temp;
		temp = next;
	}

	return -1;
}

void SparseVector::setElem(int index, int value){
	setNonzeroElem(index, value);
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

bool operator ==(const SparseVector &first, const SparseVector &second){

}

bool operator !=(const SparseVector &first, const SparseVector &second){
	
}


SparseVector::~SparseVector(){

	clear();
}
