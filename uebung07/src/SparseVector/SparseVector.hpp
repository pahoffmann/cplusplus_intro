
class SparseVector{

private:

	struct node{
	
		int index;
		int value;
		node *next;


		node(int idx,int val, node *nxt):
		index(idx), value(val), next(nxt){}

	};


	int size;
	int actSize;

	struct node *start;

	void clear();

	void copy(const SparseVector &other);

	void io() const;
	
	void setNonzeroElem(int index, int value);
	
	void removeElem(int index);
	

public:

	SparseVector(int size);
	
	SparseVector(const SparseVector &other);	
	
	int getElem(int index) const;
	
	void setElem(int index,int value);
	
	int getSize() const;
	
	SparseVector& operator=(const SparseVector &other);
	bool operator==(const SparseVector& rhs) const;

	bool operator!=(const SparseVector& rhs) const;
	
	//SparseVector& operator[](int);
	//const SparseVector& operator[](int) const;
	
	
	
	
	~SparseVector();
	


};




