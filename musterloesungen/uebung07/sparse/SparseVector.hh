#include <cassert>

class SparseVector {

struct node
{
  int index; // Element number, in the range [0, size]
  int value; // The value of this element.
  node *next; // A pointer to the next node in the linked-list.
  // Node constructor - simply initializes the data-members.
  node(int idx, int val, node *nxt) : index(idx), value(val), next(nxt) { }
  node(const node &c) : index(c.index), value(c.value), next(c.next) { }
};
  
public:

  SparseVector(int s);
  SparseVector(const SparseVector &c);
  ~SparseVector();

  void setElem(int i, int val);
  int getElem(int i) const;
  int getSize() const;

  SparseVector & operator=(const SparseVector &b);    
  bool operator==(const SparseVector &b) const;  
  bool operator!=(const SparseVector &b) const; 


private:

  node *start;
  int size;
  static const double epsilon = 0.00001;

  void clear();
  void copy(const SparseVector &c);

  void setNonzeroElem(int index, int value);
  void removeElem(int index);

  node *getPrevElem(int i) const;
  
};
