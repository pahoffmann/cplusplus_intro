#include "SparseMatrix.hpp"

	/// Builds a sparse rows x columns matrix
	SparseMatrix::SparseMatrix(int rows, int columns){
		
		this -> rows = rows;
		this -> columns = columns;
		typedef SparseVector VectorPointer;
		m_rows = new VectorPointer[columns];
		for(int i = 0; i < columns; i++){
			m_rows[i] = new SparseVector(rows);
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
		for(int i = 0; i < columns;i++){
			delete[] &m_rows[i];
		}
		delete m_rows;
	}
