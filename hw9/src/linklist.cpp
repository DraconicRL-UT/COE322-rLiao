#include "linklist.hpp"
/*
 * Compute the length of a list recursively
 * See below for an iterative solution
 */
int List::length() {
  int count = 0;
  if (head==nullptr)
    return 0;
  else
    return head->length();
};

int Node::length() {
  if (!has_next())
    return 1;
  else
    return 1+next->length();
};

/*
 * Iterative alternative
 * to recursive computation
 */
int List::length_iterative() {
  int count = 0;
  if (head!=nullptr) {
    auto current_node = head;
    while (current_node->has_next()) {
      current_node = current_node->nextnode(); count += 1;
    }
  }
  return count;
};

/*
 * Auxiliary functions
 */
void Node::print() {
  cout << datavalue << ":" << datacount;
  if (has_next()) {
    cout << ", "; next->print();
  }
};

void List::print() {
  cout << "List:";
  if (head!=nullptr){ 
    cout << " => "; head->print();
  cout << '\n';
  }
};

/*
 * The homework stuff
 */

void Node::insert( int value, shared_ptr<Node> &head ) {
  if (head==nullptr) {
    datavalue = value;
    datacount++;
  }
  else if(datavalue==value){
    datacount++;
  }
  else if (value<datavalue){
    head = make_shared<Node>(value, head);
  }
  else{
    if(has_next()){
      next->insert(value,next);
    }
    else{
      next = make_shared<Node>(value);
    }
  }
};

void List::insert( int value ) {
  if (head==nullptr) {
    head = make_shared<Node>(value);
  }
  else{
    head->insert(value,head);
  }
};

bool List::contains_value( int value ) {
  if (head==nullptr) 
    return false;
  else
    return head->contains_value(value);
};

bool Node::contains_value( int value) {
  if (datavalue==value) 
    // if I contain this value, true
    return true;
  else if (next==nullptr)
    // else, 1. if not tail: false
    return false;
  else
    //       2. return: my tail contains this value
    return next->contains_value(value);
};

// ESC > : go to end of file
// ESC < : go to beginning of file
// C-v : one screen down
// ESC v : one screen up
