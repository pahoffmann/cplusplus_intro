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
	if(!other.start){
                this->start = 0;
        }
        else if(this != &other){

		start = 0;

		size = other.size;
		actSize = other.actSize;

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


void SparseVector::setNonzeroElem(int index, int value){

	//if(actSize <= size){

		node *insert;
		node *pos = start;

		//Debug
		//std::cout << "Debug" << std::endl;
		for (int i = 0; i < actSize+1; i ++){
		//	std::cout << "Debug2" << std::endl;

			if(start == 0){

				start = new node(index,value,0);
				actSize++;
				//Debug
				//std::cout << "new: " << start->index << " " << start->value << std::endl;

				break;

			} else if (pos->index >= index){

				insert = new node(index, value, pos);
				start = insert;
				//Debug
				//std::cout << "debug(is smaller): " << insert->value << std::endl;
				actSize++;
				break;

			} else if(pos->index <= index){
				insert = new node(index, value, pos->next);
				//Debug
				//std::cout << "debug(is larger): " << insert->value << std::endl;
				actSize++;
				pos->next = insert;
				break;
			} else if(!pos->next){
				insert = new node(index, value, 0);
				actSize++;
				pos->next = insert;
				break;
			}

			pos = pos->next;
		}
}

void SparseVector::removeElem(int index){
	node *pos;
	node *deleter;
	bool found=false;

	while(pos){
		if(pos->next->index == index){
			found = true;
			deleter = pos->next;
			pos->next = pos->next->next;
			delete deleter;
			break;
		}

	}
	if(!found){
		//std::cerr<<"Could not find an Element at position " << index << std::endl;
	}

}




/**public**
*         *
**********/


/* constructor with size */
SparseVector::SparseVector(int size) /*: start(0,0,0)*/{
	this->size = size;
	actSize = 0;
	start = NULL;
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

bool SparseVector::operator==(const SparseVector& rhs) const{
	node *pos = this->start;
	node *otherpos = rhs.start;
	bool equal = true;

	while(pos && otherpos){
		if(pos -> index != otherpos->index || pos->value != otherpos->value){
			equal = false;
		}
		pos = pos->next;
		otherpos=otherpos->next;

	}
	if(!(!pos && !otherpos)){
		equal = false;
	}

	return equal;
}

bool SparseVector::operator!=(const SparseVector& rhs) const{

	return !(*this==rhs);

}

void SparseVector::setElem(int index, int value){
	/*
	if(value == 0){
		removeElem(index);
	}
	else {
		setNonzeroElem(index,value);
	}
	*/
	setNonzeroElem(index, value);
}


int SparseVector::getElem(int index) const{
	node *pos = start;
	//std::cout << pos->value << std::endl;
	for(int i = 0; i < actSize; i++){
		if(pos == 0){
			//Debug
			//std::cout << "pos is 0" << std::endl;
			break;
		}
		if(pos->index == index){
			//Debug
			//std::cout << pos->value << " " << pos->index << std::endl;
			return pos->value;

			break;
		} else {
			pos = pos->next;
		}
	}
	return 0;
}

int SparseVector::getSize() const{
	return size;
}


SparseVector::~SparseVector(){

	clear();
}
