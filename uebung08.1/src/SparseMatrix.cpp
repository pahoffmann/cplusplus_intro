#include "SparseMatrix.hpp"

	/// Builds a sparse rows x columns matrix
	SparseMatrix::SparseMatrix(int rows, int columns) 
	/*: rows(rows), columns(columns)*/{

		this->rows = rows;
		this->columns = columns;
		
		m_rows = new SparseVector[rows];
		SparseVector* objectptr;
		for(int i = 0; i < rows; i++){
			objectptr = new SparseVector(columns);
			m_rows[i] = *objectptr;
		}
	}

	/// Returns the sparse vector at the given row
	const SparseVector& SparseMatrix::operator[](const int row) const{
		return m_rows[row];
	}
	
	/// Inserts the value at given row and column into the matrix
	void SparseMatrix::insert(const int& row, const int& column, const int& value){
		
		m_rows[row].setElem(column,value);
		
	}
	
	/// Destructor
	SparseMatrix::~SparseMatrix(){
		for(int i = 0; i < rows;i++){
			//delete &m_rows[i];
		}
		delete[] m_rows;
	}
