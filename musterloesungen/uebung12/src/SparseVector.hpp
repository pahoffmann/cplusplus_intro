#ifndef __SPARSEVECTOR_HPP__
#define __SPARSEVECTOR_HPP__

#include <cassert>

/***
 * A sparse vector representation for integer values
 */

namespace jumper
{

template<typename T>
class SparseVector
{

	/// Inner struct to represent a node in the sparse vector
	struct node
	{
		/// Element number, must be smaller than the vector's size
		int index;

		/// The value of this element
		T value; // The value of this element.

		/// A pointer to the next node in the list
		node *next; // A pointer to the next node in the linked-list.

		/***
		 * Constructor
		 *
		 * @param idx	Index of the node
		 * @param val	Value of the node
		 * @param nxt	Pointer to next node in list
		 */
		node(int idx, T val, node *nxt) : index(idx), value(val), next(nxt) { }

		/***
		 * Copy constructor
		 */
		node(const node &c) : index(c.index), value(c.value), next(c.next) { }
	};

public:
	/***
	 * Constructs a sparse vector with given size
	 * @param s 	Size of the vector
	 */
	SparseVector(int s);

	/**
	 * Copy constructor
	 */
	SparseVector(const SparseVector &c);
	~SparseVector();

	/**
	 * Assigns the given value the the ith component.
	 */
	void setElem(int i, T value);

	/**
	 * Returns the value of component i
	 */
	T getElem(int i) const;

	/**
	 * Returns the size of the vector
	 */
	int getSize() const;

	/**
	 * Assignment operator
	 */
	SparseVector& operator=(const SparseVector &b);

	/**
	 * Checks if two vectors are equal
	 */
	bool operator==(const SparseVector &b) const;

	/**
	 * Checks for inequality
	 */
	bool operator!=(const SparseVector &b) const;

	/**
	 * Returns the value of the ith component
	 */
	T operator[](int i) const {return getElem(i);}

private:

	/// List anchor
	node*		m_start;

	/// Size of the vector
	int 		m_size;

	/// Removes all non-zero elements
	void clear();

	/// Copies the contends of the other vector
	void copy(const SparseVector &other);

	/// Sets a value of an non-zero element, i.e., inserts a new
	/// node in the list
	void setNonzeroElem(int index, T value);

	/// Removes the element at given index
	void removeElem(int index);

	/// Returns a pointer to node in the list before \ref i
	node *getPrevElem(int i) const;

};

}

#include "SparseVector.tcc"

#endif
