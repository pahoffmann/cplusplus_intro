
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

	void setNonzeroElem(int index, int value);

	void removeElem(int index);

public:

	SparseVector(int size);

	SparseVector(const SparseVector &other);

	int getSize();

	/** Warum ist diese Funktion nicht auf dem Aufgabenblatt gefordert???
	 * @brief returns value of element listed at index
	 */
	int getElem(int index);

	void setElem(int index, int value);

	SparseVector& operator=(const SparseVector &other);

	bool operator==(const SparseVector &first, const SparseVector &second);

	bool operator!=(const SparseVector &first, const SparseVector &second);

	~SparseVector();



};
