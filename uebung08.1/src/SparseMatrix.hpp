#ifndef SRC_SPARSEMATRIX_HPP_
#define SRC_SPARSEMATRIX_HPP_

#include "SparseVector.hpp"

class SparseMatrix
{
	int columns;
	int rows;
	SparseVector* m_rows;
	public:

	/// Builds a sparse rows x columns matrix
	SparseMatrix(int rows, int columns);

	/// Returns the sparse vector at the given row
	const SparseVector& operator[](const int row) const;

	/// Inserts the value at given row and column into the matrix
	void insert(const int& row, const int& column, const int& value);

	/// Destructor
	~SparseMatrix();
};

#endif /* SRC_SPARSEMATRIX_HPP_ */
