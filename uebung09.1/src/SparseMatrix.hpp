#ifndef __SPARSE_VECTOR_HPP__
#define __SPARSE_VECTOR_HPP__

#include "SparseVector.cpp"

template<class T>
/**
 * @brief Representation of a sparse matrix
 */
class SparseMatrix
{
    /// Array of sparse vectors to represent the columns
    SparseVector<T>** m_rows;

    /// Number of colums of the matrix
    int m_numRows;

    /// Number of rows of the matrix
    int m_numColumns;

    /// Helper to copy a sparse matrix
    void copy(const SparseMatrix<T>& other);

    /// Helper to delete all contends of a sparse matrix
    void clear();

public:

    /**
     * Default constructor. Initializes all values with zero.
     */
    SparseMatrix<T>();

    /**
     * Copy constructor.
     */
    SparseMatrix<T>(const SparseMatrix& other);

    /**
     * Constructs a matrix with \ref rows rows and \ref columns columns
     */
    SparseMatrix<T>(const int &rows, const int& cols);
    

    /**
     * Destructor
     */
    ~SparseMatrix();

    /**
     * Assignment operator
     */
    SparseMatrix<T>& operator=(const SparseMatrix<T>& other);

    /**
     * Inserts an integer \ref value at given \ref row and \ref column
     *
     * @param row y position
     * @param col x position
     * @param value new tileindex
     */
    void insert(const int& row, const int& col, const T& value);
    /**
     * @brief getNumRows number rows
     * @return m_numRows
     */
    int getNumRows() const {return m_numRows;}
    /**
     * @brief getNumCols number columns
     * @return m_numColumns
     */
    int getNumCols() const {return m_numColumns;}
    
    /// Returns the sparse vector at given \ref row
    SparseVector<T>& operator[](int row) const;

};


#endif
