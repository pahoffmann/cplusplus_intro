/**
 * A class representing a vector. Non-Zero Entries are saved in a linked list,
 *
 * @author Jan Elseberg
 */

#include "SparseVector.hpp"

#include <cmath>
#include <iostream>

using std::cout;
using std::endl;

template<class T>
SparseVector<T>::SparseVector(int s)
{
    m_size = s;
    m_start = new node(-1,0,0);
}

template<class T>
SparseVector<T>::SparseVector(const SparseVector<T> &c)
{
    copy(c);
}
template<class T>
SparseVector<T>::~SparseVector()
{
    clear();
}
template<class T>
void SparseVector<T>::setElem(int i, T val)
{
    if (i >= getSize())
    {
        return;
    }

    if (val != 0)
    {
        setNonzeroElem(i, val);
        return;
    }
    removeElem(i);
}
template<class T>
T SparseVector<T>::getElem(int i) const
{
    if (i >= getSize())
    {
        return 0.0;
    }

    node *elem = getPrevElem(i);

    if (elem != 0 && elem->next != 0 && elem->next->index == i)
    {
        return elem->next->value;
    }
    return 0.0;
}
template<class T>
int SparseVector<T>::getSize() const
{
    return m_size;
}
template<class T>
void SparseVector<T>::clear()
{
    node *elem;

    while (m_start != 0)
    {
        elem = m_start;
        m_start = m_start->next;
        delete elem;
    }
}
template<class T>
void SparseVector<T>::copy(const SparseVector<T> &c)
{
    m_size = c.getSize();
    node *celem = c.m_start;
    m_start = new node(*celem);
    node *elem = m_start;

    while (celem->next != 0)
    {
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
template<class T>
void SparseVector<T>::setNonzeroElem(int index, T value)
{
    node *elem = getPrevElem(index);

    // No preceeding element found!
    if (elem == 0)
    {
        return;
    }

    // element with index already exists
    if (elem->next != 0 && elem->next->index == index)
    {
        elem->next->value = value;
        return;
    }

    // create new node
    elem->next = new node(index, value, elem->next);
}

template<class T>
void SparseVector<T>::removeElem(int index)
{
    node *elem = getPrevElem(index);
    if (elem == 0 || elem->next == 0)
    {
        return;
    }
    node * tmp = elem->next;
    elem->next = elem->next->next;
    delete tmp;
}

template<class T>
typename SparseVector<T>::node * SparseVector<T>::getPrevElem(int i) const
{
    node *elem ;
    elem = m_start;

    while (elem != 0 && elem->next != 0 && elem->next->index < i)
    {
        elem = elem->next;
    }
    return elem;
}

template<class T>
SparseVector<T> & SparseVector<T>::operator=(const SparseVector<T> &b)
{
    // Check for Self-Assignement
    if (this == &b)
    {
        return *this;
    }

    // destroy old values
    clear();

    copy(b);

    return *this;
}  

template<class T>
bool SparseVector<T>::operator==(const SparseVector<T> &b) const
{
    if (getSize() != b.getSize())
    {
        return false;
    }

    node *elem = m_start;
    node *elemb = b.m_start;

    while (true)
    {
        if ( elem->index != elemb->index || elem->value != elemb->value)
        {
            return false;
        }

        // end of both SparseVectors
        if (elem->next == 0 && elemb->next == 0)
        {
            return true;
        }
        // only reached the end of one SparseVector
        if (elem->next == 0 || elemb->next == 0)
        {
            return false;
        }

        //iterate otherwise
        elem = elem->next;
        elemb = elemb->next;
    }
}
template<class T>
bool SparseVector<T>::operator!=(const SparseVector<T> &b) const
{
    return !(*this == b);
}



