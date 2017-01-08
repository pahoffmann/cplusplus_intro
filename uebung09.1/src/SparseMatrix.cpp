#include "SparseMatrix.hpp"
#include <iostream>

template<class T>
SparseMatrix<T>::SparseMatrix(const int& rows, const int &cols)
{

    // Save width and height
    m_numRows = rows;
    m_numColumns = cols;
    m_rows = 0;
    

    if(m_numRows >0)
    {
        // Create rows
        m_rows = new SparseVector<T>*[rows];
        for(int i = 0; i < rows; i++)
        {
            m_rows[i] = new SparseVector<T>(cols);
        }   
    }

}
template<class T>
void SparseMatrix<T>::copy(const SparseMatrix<T>& other)
{
    if(&other != this)
    {

        // Check if rows was already used and free resources
        // if necessary.
        if(m_rows)
        {
            clear();
        }

        // Copy width and height
        m_numRows = other.m_numRows;
        m_numColumns = other.m_numColumns;

        // Create rows
        m_rows = new SparseVector<T>*[other.m_numRows];

        // Create sparse vectors for columns
        for(int i = 0; i < m_numRows; i++)
        {
            m_rows[i] = new SparseVector<T>(other[i]);
        }
    }

}
template<class T>
void SparseMatrix<T>::clear()
{

    if(m_rows)
    {
        for(int i = 0; i < m_numRows; i++)
        {
            delete m_rows[i];
        }

        delete[] m_rows;
    }
    m_rows = 0;

}
template<class T>
SparseMatrix<T>::SparseMatrix()
{
    m_numRows = 0;
    m_numColumns = 0;
    m_rows = 0;
}
template<class T>
SparseMatrix<T>::SparseMatrix(const SparseMatrix<T>& other)
{
    copy(other);
}
template<class T>
SparseMatrix<T>::~SparseMatrix()
{
    clear();
}

template<class T>
SparseMatrix<T>& SparseMatrix<T>::operator =(const SparseMatrix<T>& other)
{
    if(&other != this)
    {
        clear();
        copy(other);
    }
    return *this;
}
template<class T>
SparseVector<T>& SparseMatrix<T>::operator[](int index) const
{   
    
    return *m_rows[index];
}
template<class T>
void SparseMatrix<T>::insert(const int& row, const int& col, const T& value)
{

    m_rows[row]->setElem(col, value);


}

