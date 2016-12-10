
class SparseVector{

private:

	struct node{
	
		int index;
		int value;
		node *next;


		node(int idx,int val, node *nxt){
			index=idx;
			value=val;
			next=nxt;
		}
	};


	int size;
	int actSize;

	struct node *start;

	void clear();

	void copy(const SparseVector &other);

public:

	SparseVector(int size);
	
	SparseVector(const SparseVector &other);	

	int getSize();
	
	SparseVector& operator=(const SparseVector &other);
	
	~SparseVector();
	


};
