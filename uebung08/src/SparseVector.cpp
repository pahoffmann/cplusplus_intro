/**
 * A class representing a vector. Non-Zero Entries are saved in a linked list,
 *
 * @author Jan Elseberg
 */

#include "SparseVector.hpp"

#include <cmath>

#include <new>

SparseVector::SparseVector(){
	size = 0;
	start = 0;
}


/**
 * Constructs an empty SparseVector of size s.
 *
 * @param s The size of this vector.
 */
SparseVector::SparseVector(int s) {
  size = s;
  start = new node(-1,0,0);
}

/**
 * Copy constructor, to make a deep copy of c.
 *
 * @param c The vector to be copied.
 */
SparseVector::SparseVector(const SparseVector &c) {
  copy(c);
}

/**
 * Destroys the vector.
 */
SparseVector::~SparseVector() {
  clear();
}

/**
 * Sets an Element to the given value.
 *
 * @param i The index of the entry to be set.
 * @param val The value to set.
 */
void SparseVector::setElem(int i, int val) {
  if (i >= getSize()) {
    return;
  }
  if (val != 0) {
    setNonzeroElem(i, val);
    return;
  }
  removeElem(i);  
}

/**
 * Gets the specified entry.
 *
 * @param i The index of the element to look up.
 * @return The value at i.
 */
int SparseVector::getElem(int i) const {
  if (i >= getSize()) {
    return 0.0;
  }
  
  node *elem = getPrevElem(i);

  if (elem != 0 && elem->next != 0 && elem->next->index == i) {
    return elem->next->value;
  }
  return 0.0;
}

/**
 * Gets the size of this vector.
 *
 * @return The size of this vector.
 */
int SparseVector::getSize() const {
  return size;
}

/**
 * Function to clear allocated memory.
 */
void SparseVector::clear() {
  node *elem;

  while (start != 0) {
    elem = start;
    start = start->next;
    delete elem;
  } 
}

/**
 * Function to help copy a SparseVector.
 *
 * @param c The vector to be copied.
 */
void SparseVector::copy(const SparseVector &c) {
  size = c.getSize();
  node *celem = c.start;
  start = new node(*celem);
  node *elem = start;

  while (celem->next != 0) {
    celem = celem->next;
    elem->next = new node(*celem);
    elem = elem->next;
  }
}

/**
 * Sets an element to a non-zero value.
 *
 * @param index The index of the entry.
 * @param value The non zero-value to set.
 */
void SparseVector::setNonzeroElem(int index, int value) {
  node *elem = getPrevElem(index);

  // No preceeding element found!
  if (elem == 0) {
    return;
  }

  // element with index already exists 
  if (elem->next != 0 && elem->next->index == index) {
    elem->next->value = value;
    return;
  }

  // create new node
  elem->next = new node(index, value, elem->next);  
}

/**
 * Deletes the node with the given index.
 *
 * @param index The index of the node to be removed.
 */
void SparseVector::removeElem(int index) {
  node *elem = getPrevElem(index);
  if (elem == 0 || elem->next == 0) {
    return;
  }
  node * tmp = elem->next;
  elem->next = elem->next->next;
  delete tmp;
}

/**
 * Gets the node directly preceeding i.
 *
 * @param i The index specifying the previous node. 
 *          Does not have to exist as a node
 * @return The node preceeding i.
 */
SparseVector::node * SparseVector::getPrevElem(int i) const {
  node *elem ;
  elem = start;

  while (elem != 0 && elem->next != 0 && elem->next->index < i) {
    elem = elem->next;
  }
  return elem;
}

/**
 * Assignment operator. Copies b to this Sparsvector.
 *
 * @param b The vector to be copied.
 * @return This SparseVector to correctly handle multiple assignments.
 */
SparseVector & SparseVector::operator=(const SparseVector &b) {
  // Check for Self-Assignement
  if (this == &b) {
    return *this;
  }

  // destroy old values
  clear();

  copy(b);
  
  return *this;
}  

/**
 * Checks whether the two vectors are equal.
 *
 * @param b The vector to compare.
 * @param true If both vectors are equal.
 */
bool SparseVector::operator==(const SparseVector &b) const {
  if (getSize() != b.getSize()) {
    return false;
  }

  node *elem = start;
  node *elemb = b.start;

  while (true) {
    if ( elem->index != elemb->index || 
      fabs(elem->value - elemb->value) > epsilon ) {
      return false;
    }
    
    // end of both SparseVectors
    if (elem->next == 0 && elemb->next == 0) {
      return true;
    }
    // only reached the end of one SparseVector
    if (elem->next == 0 || elemb->next == 0) {
      return false;
    }

    //iterate otherwise
    elem = elem->next;
    elemb = elemb->next;
  }
}

/**
 * Checks whether the two vectors are equal.
 *
 * @param b The vector to compare.
 * @param false If both vectors are equal.
 */
bool SparseVector::operator!=(const SparseVector &b) const {
  return !(*this == b);
}


//INDEXOPERATOR
const int SparseVector::operator[](const int index) const{
	
	/*if(index > this->getSize()){
		return 0;
	}
	else{
		node *pos = this->start;
		while(pos){
			if(pos->index == index){
				return 0;
			}
			pos = pos->next;
		}
		
		return 0;	
	}*/
	int tmp = getElem(index);
	return tmp;
	
	
}


