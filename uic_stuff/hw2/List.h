#ifndef LIST_H
#define LIST_H

#include <algorithm>
#include <iostream>

// using namespace std;

template <typename T>
class List
{
 
  private:    
  
    // struct for singly-linked list nodes
    struct Node
    {
      T      data;
      Node   *next;

      Node( const T & d = T{}, Node * n = nullptr)
        : data{ d },  next{ n } { }

    };


  public:
    int len; 
    // constructors
    List( ) { 
      init( );
    }

    ~List( ) {
      clear( );
    }
    /**
     * Disclaimer:  C++ conventions tell us that we should have a couple
     * of additional constructors here (a copy constructor, assignment operator
     * etc.)
     *
     * However, to keep things simple for now we will ignore that convention
     * (since the exposure to C++ is pretty variable it seems -- some students
     * having taken 141 before last semester; some students coming from 107,
     * etc.)
     */


    /**
     * function: clear
     * desc:  makes the calling list empty (but the list still
     *        exists).
     */
    void clear(){
      Node * p = front;
      Node *pnext;

      while(p != nullptr) {
        pnext = p->next;
        delete p;
        p = pnext;
      }
      front = back = nullptr;
    }





    /**
     * TODO
     *
     * function: length
     * desc:  returns the length of the calling list
     *        
     * REQUIREMENTS:  this is a working implementation, but
     *   it takes linear time.
     *
     *   Your job (todo):  make modifications so that this
     *     operation becomes constant time (O(1)).
     *
     *   This task is different from most others in that most of
     *       the "real" work you do to make this work
     *	in O(1) time will be in _other_ functions which affect
     *	the length of lists.
     *
     *	HINT:  you are free to add data members to the List class...
     *	       maybe for "bookkeeping"??
     */
    int length( ) const {
      /*Node *p = front;
      int n=0;

      while(p != nullptr) {
        n++;
        p = p->next;
      }
      */
      return this->len;
    }


  public:

    // Return true if the list is empty, false otherwise.
    bool is_empty( ) const {
      return front == nullptr;
    }


    void print() const {
      Node *p = front;

      std::cout << "[ "; 
      while(p != nullptr) {
        std::cout << p->data << " ";
        p = p->next;
      }
      std::cout << "]\n";
    }

    void push_front(const T & data) {
      front = new Node(data, front);
      len++;
      if(back == nullptr)
        back = front;
    }

    bool pop_front(T &val) {
      Node *tmp;

      if(front==nullptr)
        return false;
      val = front->data;
      len--;
      tmp = front;
      front = front->next;
      delete tmp;
      if(front==nullptr)
        back = nullptr;
      return true;
    }

    void push_back(const T & val) {
      Node *tmp = new Node(val, nullptr);
      len++;
      if(front == nullptr) {
        front = back = tmp;
      }
      else {
        back->next = tmp;
        back = tmp;
      }
    }

    bool remove_first(const T &x) {
      Node *p, *tmp;
      T dummy;

      if(front==nullptr) return false;
      if(front->data == x) {
        pop_front(dummy);
	len--;
	return true;
      }
      p = front;
      while(p->next != nullptr) {
        if(x == p->next->data) {
          tmp = p->next;
          p->next = tmp->next;
          if(tmp == back)
            back = p;
          delete tmp;
	  len--;
          return true;
        }
        p = p->next;
      }
      return false;
    }

    int slow_remove_all(const T &x) {
      int n=0;

      while(remove_first(x))
        n++;
      return n;
    }

    bool is_sorted() const {
      Node *p = front;

      while(p!=nullptr && p->next != nullptr) {
        if(p->data > p->next->data)
          return false;
        p = p->next;
      }
      return true;
    }





    /** TODO
     *    function:  count
     *     description:  Counts number of occurrences 
     *     		of x in the list and returns that count.
     *
     *  REQUIRMENT:  Linear runtime (O(n) where n is the length 
     *    of the list.)
     */
    int count(const T &x) const {
      int c = 0; //this is counter
      Node* cur = front;
      while(cur != nullptr){
	if(cur->data == x){
	  c++;
        }
        cur = cur->next;
      }
      
      std::cout<<"count " << c << std::endl;
      return c;
      
    }

    /* TODO 
     *    
     *  function:  pop_back
     *
     *  if list is empty, we do nothing and return false 
     *  otherwise, the last element in the list is removed, its
     *      value (data field) is assigned to the reference parameter 
     *      data (so the removed element can be 'passed-back' to the
     *      caller) and true is returned.
     *
     *  REQUIRMENT:  Linear runtime (O(n) where n is the length 
     *    of the list.)
     *
     */
    bool pop_back(T &data) {
      Node* cur;
      if (len == 0){return false;}
      else if (len == 1){
        cur = front;
	data = front->data; 
	delete back;
        front = back = cur = NULL;
	
	return true;
      }
      else{
        cur = front;
        while (cur->next->next != NULL) {
          cur = cur->next;
        }
        data = back->data;
        back  = cur;
	
        delete back->next;
        back->next = NULL;
        --len;
        return true;
      }
      
      return false;

    }

    /**
     * TODO:  
     *   function:  equal_to 
     *   description:  returns true if calling List and parameter 
     *      List other contain exactly the same sequence of values.
     *      Returns false otherwise.
     *
     *  REQUIRMENT:  Linear runtime (O(n) where n is MIN(len1,len2)
     *    and len1 and len2 are the respective lengths of the two lists.
     **/
    bool equal_to(const List<T> &other) const {
      Node* cur1 = this->front;
      Node* cur2 = other.front;
      while(cur1 != NULL && cur2 !=NULL){
        if(cur1->data != cur2->data){
          return false;
        }
        cur1 = cur1->next;
        cur2 = cur2->next;
      }
      if(cur1 == nullptr && cur2 == nullptr){
	return true; 
      }
      //this is to take care of lists that are not the same size
      return false;  // placeholder
    }

    /**
     * TODO:  print in reverse order 
     *
     * Try to do without looking at notes!
     * Hints:  recursive helper function
     *
     *  REQUIRMENT:  Linear runtime (O(n) where n is the length 
     *    of the list.)
     */
    void print_rev() const {
      Node* cur = this->front; 
      if(cur  == NULL){
        return;
      }
      //Node* cur = this->front; 
      printr(cur);      
    }

    void printr(Node* n)const{
      if (n == NULL)
	return;
      
      printr(n->next);
      std::cout<< n->data<< std::endl; 
    }
    
    /* TODO
     *  For full credit, you cannot allocate any new memory!
     *
     *  description:  self-evident 
     *
     *  REQUIRMENT:  Linear runtime (O(n) where n is the length 
     *    of the list.)
     */
    void reverse() {

      Node *current =front;
      Node *prev = NULL, *next = NULL;
      
      
      while (current != NULL)
        {
          // Store next
          next = current->next;
	  
          // Reverse current node's pointer
          current->next = prev;
	  
          // Move pointers one position ahead.
          prev = current;
          current = next;
        }
      front = prev;
    }


    /** TODO
     *   function:  fast_remove_all
     *   description:  same behavior/semantics as
     *      slow_remove_all.  However, this function
     *      must guarantee linear time worst case 
     *      runtime (hence, "fast").
     *
     *   REQUIREMENT:  linear worst-case runtime.
     *
     *   Note:  your solution may be either recursive or 
     *   iteratieve.
     **/
    int fast_remove_all(const T &x) {
      int count = 0 ;//number of deletions
      if(front == nullptr) {return 0;}
      Node* cur;
      Node* tmp; 
      cur = front;
      while(cur->next != nullptr){
	if(cur->data == x){
	  if(cur == front){
	    delete front; 
	    front = cur->next;
	    len--;
	    count++;
	    cur = cur->next; 
	  }
	  else{
	    tmp = cur->next->next;
	    Node* c = cur;
	    len--;
	    count++;
	    cur = cur->next;
	    delete cur;
	    cur = c;
	    cur->next = tmp; 
	  }
	}
	
	else{
	  cur = cur ->next;
	}
      }
      return count;
    }
    
    /** TODO
     * function:  insert_sorted
     *
     * description:  assumes given list is already in sorted order from
     *     smallest to largest and inserts x into the appropriate position
     * 	   retaining sorted-ness.
     * Note 1:  duplicates are allowed.
     *
     * Note 2:  if given list not sorted, behavior is undefined/implementation
     * 		dependent.  We blame the caller.
     * 		So... you don't need to check ahead of time if it is sorted.
     *
     *
     * REQUIREMENTS:
     *
     *   O(n) runtime
     */
    void insert_sorted(const T &x) {
      Node* cur;
      Node* tmp; 
      //bool in = false;
      if(front == nullptr){
	front = back = new Node(x, nullptr);
	len++;
	return;
      }
      cur = front;
      if(front->data > x){
	front = new Node(x, cur);
	len++;
	return; 
      }
      while(cur->next){
	if(cur->next->data > x && cur->data <= x){
	  tmp = cur->next;
	  cur->next = new Node(x, tmp);
	  
	}
	cur - cur ->next; 
      }
      back->next = new Node(x, nullptr);
      back = back->next;
      len++;
      return; 
    }

    /** TODO
     * function:  merge_with
     *
     * description:  assumes both list a and b are in
     * 	sorted (non-descending) order and merges them
     * 	into a single sorted list with the same
     * 	elements.  
     *
     * 	This single sorted list is stored in a while
     * 	b becomes empty.
     *
     * 	if either of given lists are not sorted, 
     * 	we blame the caller and the behavior is
     * 	implementation dependent -- i.e., don't worry
     * 	about it!
     *
     *      Condition in which both parameters are the same
     *      list (not merely "equal"), the function simply 
     *      does nothing and returns.  This can be tested
     *      with simple pointer comparison.
     *
     * 	Example:
     *
     * 		a:  [2 3 4 9 10 30]
     * 		b:  [5 8 8 11 20 40]
     *
     * 		after call a.merge_with(b):
     *
     * 		  a:  [2 3 4 5 8 8 9 10 11 20 30 40]
     * 		  b:  []
     * 
     *
     * REQUIREMENTS:
     *
     * 	Runtime Must be linear in the length of the 
     * 	resulting merged list (or using variables above, 
     * 	O(a.length()+b.length()).
     *
     *  should not allocate ANY new list
     * 	nodes -- it should just re-link existing
     * 	nodes.
     */
    void merge_with(List<T> &other){
      other->back= other->front;
      this->back = this->front;
      //if first node needs to put before
      if(other->front->data < this->front->data){
	other->back = other->front->next; 
	other->front->next = this->front;
	this->front = other->front;
	other->front = other->back; 
      }
      while(other->back->next){
	if(this->back->data < other->front->data && this->back->next->data > other->front->data){
	  other->back->next = other->front;
	  other->back->next = this->back->next;
	  this->back->next = other->back;
	  other->back = other->front;
	  //this->back = this->back->next; 
	}
	this->back = this->back->next;
      }
      ///for the mergeing list to be shorter than the alist we are adding to 
      while(this->back->next){
	if(this->back->data < other->front->data && this->back->next->data > other->front->data){
	  other->back->next = other->front;
	  other->back->next = this->back->next;
	  this->back->next = other->back;
	  other->back = other->front;
	  
	  //this->back = this->back->next; 
	}
	this->back = back->next;
	
      }
      while(other->back->next){//to move other back to the back 
	other->back = other->back->next;	
      }
      //to make sure back is pointing at the rigt place
      if(other->front && other->back){
	this->back->next = other->front;
	this->back = other->back; 
      }
      //after that then take care of rest of nodes if there are any
      //unsure
      
    }

    /**
     * TODO
     * function:  clone
     *
     * description:  makes a "deep copy" of the given list a
     *   and returns it (as a List pointer).
     *
     * NOTE:  this functionality would normally be folded into
     *  a "copy constructor"
     *
     */
    List<T> * clone() const {
      //need to know syntax better
      List<T>* p = new List<T>;
      if(this->front == nullptr){
	p->front = p-> back =  nullptr;
	return p;
	
      }
      p->front = new Node(this->front->data, nullptr);
      p->len++;
      Node* cur2 = p->front; 
      Node* cur1 = this->front->next;
      while(cur1->next){
	cur2->next = new Node(cur1->data, nullptr);
	cur2 = cur2->next;
	cur1= cur1->next;
	p->len++; 
      }
      cur2->next = new Node(cur1->data, nullptr);
      p->back = cur2->next;
      p->len++; 
      return p; 
      
    }

    /**
     * TODO
     * function:  prefix
     *
     * description:  removes the first k elements from the
     *               calling list which are used to form a new list
     *		            which is then returned.
     *
     *		if n is the length of the given list, we have the
     *		following boundary conditions:
     *
     *		  if k==0:
     *			    calling list unchanged and an empty list returned
     *		  if k>=n:
     *			    calling becomes empty and a list containing
     *			    all elements previously in lst is returned.
     *
     *		examples:
     *
     *		  EX1:  lst:  [2, 3, 9, 7, 8]
     *			k:    3
     *
     *			call:
     *
     *			  List<int> * pre = lst.prefix(3);
     *
     *			after call:
     *			   lst:  [7, 8]
     *			   returned list (prefix):  [2, 3, 9]
     *
     *		  EX2  lst:  [2, 3, 9, 7, 8]
     *			k:    0
     *
     *		  call:
     *
     *			  List<int> * pre = lst.prefix(3);
     *
     *			after call:
     *			   lst:  [2, 3, 9, 7, 8]  (unchanged)
     *			   returned list:  []
     *
     *		  EX3  lst:  [2, 3, 9, 7, 8]
     *			k:    5
     *
     *		  call:
     *
     *			  List<int> * pre = lst.prefix(5);
     *
     *			after call:
     *			   lst:  []
     *			   returned list:  [2, 3, 9, 7, 8]
     *
     * REQUIREMENTS:
     *
     *	RUNTIME:  THETA(n) worst case where n is the length of the given list
     *
     *       ORDERING:  the ordering of the returned prefix should be the same as
     *                  in the given list
     *
     *       MEMORY:    for full credit, no new nodes should be 
     *                  allocated or deallocated; you should just 
     *                  "re-use" the existing nodes.  HOWEVER, you will
     *		               need to allocate a List object for the returned
     *		               prefix (but, again, the underlying Nodes should be
     *		               re-used from the calling list).
     */
    List<T> * prefix(unsigned int k) {
      //this almost works i just cannot get the new list to only be the ones i take out but the old is decreased well
      List<T> * p = new List<int>;
      if(k == 0){
	p->front = p->back = nullptr;
	return p; 
	
      }
      if(k == 1){
	p->front = p->back = this->front;
	return p;
      }
      p->front = p->back = this->front;
      k--;
      while(k){
	p->back = p->back->next;
	k--; 
      }
      this->front = p->back->next;
      p->back->next = nullptr;
      return p ;
      
    }

    /**
     * TODO
     * function:  filter_leq
     *
     * description:  removes all elements of the given list (lst) which
     *		are less than or equal to a given value (cutoff)
     *		
     *		A list containing the removed elements is returned.
     *
     * examples:
     *
     *	EX1: 	lst:  [4, 9, 2, 4, 8, 12, 7, 3]
     *		cutoff:  4
     *
     *		after call:
     *			lst:  [9, 8, 12, 7]
     *			returned list:  [4, 2, 4, 3]
     *
     *       -----------------------------------------
     *	EX2: 	lst:  [6, 5, 2, 1]
     *		cutoff:  6
     *
     *		after call:
     *			lst:  []
     *	 		returned list:  [6, 5, 2, 1]
     *
     * REQUIREMENTS:
     *
     *	RUNTIME:  THETA(n) where n is the length of the given list
     *
     *       ORDERING:  the ordering of the returned list should be the same as
     *                  in the given list
     *
     *       MEMORY:    for full credit, no new nodes should be allocated or deallocated;
     *		   you should just "re-use" the existing nodes.  HOWEVER, you will
     *		   need to allocate a LIST structure itself (i.e., for the returned
     *		   list).
     *			
     */
    List<T> * filter_leq(const T & cutoff) {
      List<T>* p = new List<T>;
      if(this->front <= cutoff){
	p->front = this->front;
	p->back = p->front;
	this->front = this->front->next;
      }
      this->back = this->front;
      
      while(this->back->next->next){
	if(!p->front && this->back->next <= cutoff){
	  p->front = this->back->next;
	  this->front->next = this->front->next->next;
	  p->back = p->front; 
	}
	else if(this->back->next->data <= cutoff){
	  p->back->next = this->back->next;
	  this->back->next = this->back->next->next;
	  p->back = p->back->next; 
	}
	this->back = this->back->next; 
      }
      if(this->back->next->data <= cutoff){
	p->back = this->back->next;
	this->back->next = nullptr; 
      }
      return p;

    }

    /**
     * TODO
     * function:  concat
     *
     * description:  concatenates the calling list with parameter list (other)
     *    The resulting concatenation is reflected the calling list; the 
     *    parameter list (other) becomes empty.
     *
     *    example:
     *
     *	EX1:  a: [2, 9, 1]
     *	      b: [5, 1, 2]
     *
     *	      call:  
     *	            a.concat(b);
     *
     *	after call:
     *
     *		a: [2, 9, 1, 5, 1, 2]
     *		b: []
     *
     * REQUIREMENTS:  
     *
     *     runtime:  O(1)
     *
     *     sanity:  this operation makes sense when a and b
     *		are distinct lists.  For example, we don't
     *		want/allow the caller to do something like
     *		this:
     *
     *			List<int> *my_list = new List<int>();;
     *
     *			my_list->push_front(my_lst, 4);
     *			my_list->push_front(my_lst, 2);
     *
     *			my_lst->concat(my_lst);
     *
     *		your implementation must detect if it is being
     *		called this way.  If so the function does nothing
     *		and (optionally) prints an error message to
     *		stderr.
     *	
     */
    void concat(List<T> &other) {

      if(this == &other) {
        std::cerr << "warning:  List::concat():  calling object same as parameter";
        std::cerr << "\n          list unchanged\n";
        return;
      }
      if(other.front == NULL && other.back == NULL){
	return;  
      }
      if(this->front == nullptr && this->back == nullptr){
	this->front = other.front;
	this->back = other.back;
	other.back = nullptr;
	other.front = nullptr; 
      }
      this->back->next = other.front;
      this->back = other.back;
      other.front = nullptr;
      other.back = nullptr; 
      std::cout << "List::concat(): no error...\n";
    }


    /**
     * TODO
     *
     * function:  compare_with
     * description: compares the calling list with parameter list (other)
     *    "LEXICALLY" (essentially a generalization of dictionary
     *    ordering).
     *
     *    link:  https://en.wikipedia.org/wiki/Lexicographical_order
     *
     *    Return Value:
     *
     *       o if the two lists are identical, 0 is returned.
     *       o if the calling list is lexically BEFORE the other list,
     *             -1 is returned
     *       o otherwise, the other list is lexically before the calling
     *             list and 1 (positive one) is returned.
     *
     *    Properties and examples:
     *
     *        The empty list is lexically before all non-empty lists
     *          (you can say it is "less than" all non-empty lists).
     *
     *        Examples (using mathematical notation):
     *
     *          [2 5 1] < [3 1 1 1 1]    (think dictionary ordering!)
     *
     *          [4 1 3] < [4 1 3 0 0 0]  (prefix: just like "car" is before
     *                                            "cartoon" in the dictionary).
     * 
     *          [4 5 6 1 2 3 9 9 9] < [4 5 6 1 4 0 0] 
     *                   ^                     ^
     *                      (they have a common prefix of length 4; but at
     *                      the fifth position they differ and the left list
     *                      is the winner (smaller) -- no need to look further)
     *
     *                      
     *        Templates?
     *
     *          Since List is a template class, the elements of a particular
     *          list need not be integers.  For example, we could have
     *          lists of strings.
     *
     *          Good news:  the exact same principle applies because 
     *          strings can be compared just like integers can be compared!
     *
     *          Great news:  you don't need to think about this at all!
     *          The exact same code you would write if you assumed the element
     *          type is integer will work for other types like strings.
     *
     *          Why?  Because, for example, all of these operators:
     *
     *                   <, <=, ==, > and >= 
     *
     *          all work on strings.  They are not 'built-in' to C++, but
     *          the class string has "overloaded" these operators (they 
     *          result in an appropriate function call).
     *
     *          (In a subsequent exercise, we will do this kind of 
     *          overloading ourselves!)
     *                                     
     *        Examples with lists of strings:
     *
     *          ["egg", "goat"] < ["egg", "globe", "apple"]
     *
     *          ["zebra", "fun"] < ["zebra", "funny"]
     *
     *        [Yes, the components of these lists are THEMSELVES compared
     *        lexically, but the string class is doing those comparisons)
     *
     */
    int compare_with(const List<T> &other) const {
      Node* cur1 = this->front;
      Node* cur2 = other.front;
      if(this->front == nullptr && other.front){return -1;}
      if(this->front && other.front == nullptr){return 1;}
      if(this->front == nullptr && other.front == nullptr){return 0;}
      
      while(cur1 && cur2){
	if(!(cur1->data == cur2->data)){
	  if(cur1->data < cur2->data){return -1;}
	  return 1;
	}
	cur1 = cur1->next;
	cur2 = cur2->next; 
      }
      if(cur1 == nullptr && cur2){return -1;}
      if(cur2 == nullptr && cur1){return 1;}
      return 0;

    }

    /*
     * TODO
     *
     * function:  suffix_maxes
     *
     * desc:  constructs a new list of the same length as the calling object
     *        with the value stored at position i of the new list is the MAXIMUM
     *        value in the suffix (or tail) of the calling list starting from
     *        position i.
     *
     *        This new list is returned and the calling list is unchanged.
     *
     *        Example:
     *
     *          Given List:  [6, -18, 12, 4, 1, 7, 2, 5  4]
     *                                    ^^^^^^^^^^^^^^^^
     *
     *          New list:    [12, 12, 12, 7, 7, 7, 5, 5, 4]
     *                                    ^
     *
     *              (as a sub-example, the marked entry in the new list
     *              (marked with '^') is the max of the marked suffix in the
     *              given list (marked with a bunch of '^'s).
     *
     * REQUIREMENTS:
     *
     *        Total Runtime:   O(n)
     *        Calling list is unchanged.
     *
     */
    List<T> * suffix_maxes() const{
      //need to do recursive
      List<T>* p = new List<T>;
      Node* cur = this->front;
      p->front = p->back = nullptr;
      // p->back = ;
      //p->back->next = 
      //if(cur == nupllptr){ return p;}
      return nullptr; 
    }


  private:
    Node *front;
    Node *back;

    void init( ) {
      front = nullptr;
      back = nullptr;
    }
};

#endif
