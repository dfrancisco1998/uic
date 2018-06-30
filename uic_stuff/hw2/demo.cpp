#include "List.h"

#include <stdlib.h>
#include <iostream>
#include <string>

//need to write fileq, suffix  maxes, merge with , 
//test concat, compare with 

using namespace std;

List<int> * slow_list(int n) {

  // placeholder
  return nullptr;
}

int main(int argc, char *argv[]){
  List<int> *list = new List<int>();
  //List<int> *lista = new List<int>();
  //for(int i = 0; i < 4; i++){
  //lista->push_back(i + 1);
  //}
  
  List<string> *list2 = new List<string>();
  List<string> *list3 = new List<string>();
  int x;
  int n, ndel;

  n = 1000;

  if(argc == 2) {
    n = atoi(argv[1]);
  }


  for(x=1; x<=4; x++) {
    list->push_front(x);
  }
  list->print();

  for(x=1; x<=4; x++) {
    list->push_back(x);
  }
     
  list->print();
  //cout<<"doing fasr rem" << endl; 
  //int r = 1;
  //int c = list->fast_remove_all(r);
  //cout<< "rem " << c<< endl;
  //list->print();
  //cout<< " doing clone" << endl; 
  List<int>* l = list->clone();
  cout<< "old" << endl;
  list->print();
  cout<< "cloen" << endl; 
  l->print();
  List<int>* u = l->prefix(3);
  cout<< " pre " <<endl;
  u->print();
  cout<< "old" << endl;
  l->print(); 
  //l->push_back(5); 
  list->pop_front(x);
  cout << "popped " << x <<endl;
  list->print();
  //int y;
  //list->pop_back(y);
  //cout<< "pop back "<< y << endl;
  //list->print();
  //int l = list->length();
  //std::cout<< "length "<< l << std::endl; 
  list->slow_remove_all(2);
  cout << "after remove-all(2):\n";
  list->print();

  // string words[] = {"hello", "goodbye", "sunrise", "sunset"};
  string words[] = {"alice", "bob", "cathy", "donald"};


  for(int i=0; i<4; i++) {
      list2->push_front(words[i]);
      list3->push_back(words[i]);
  }
  list2->print();
  //list2->reverse();
  //list2->print_rev(); 
  list3->print();
  // bool e = list2->equal_to(list3);
  //xcout<<"equals " << e << endl;
   ///cout<<"comparing" << endl;
   // list2->concat(list3);
   list2->print(); 
   //int q = list->compare_with(l);
   //cout<< "comp "<< q << endl; 
  cout << "list  sorted?  " << list->is_sorted() << endl;
  cout << "list2 sorted?  " << list2->is_sorted() << endl;
  cout << "list3 sorted?  " << list3->is_sorted() << endl;


  // list2->front = NULL;
  
  delete l;
  delete u; 
  delete list;
  delete list2;
  delete list3;
  // delete pre; 
  /***  UNCOMMENT THIS CODE ONCE YOU HAVE WRITTEN YOUR
   *     slow_list FUNCTION

  list = slow_list(n);

  cout << "starting slow_remove_all (n=" << n << ")" << endl;
  ndel = list->slow_remove_all(0);
  cout << "slow_remove_all done!" << endl;
  cout << "    num-deleted:    " << ndel << endl;
  cout << "    list-len after: " << list->length()   << endl;

  delete list;

  ***/

  return 0;
}
