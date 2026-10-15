/**
 * TODO: add file header
 */
#ifndef BSTNODE_HPP
#define BSTNODE_HPP
#include <iomanip>
#include <iostream>
using namespace std;

/**
 * Class defining the creation of Nodes for a Binary Search Tree, their getters and setters, and a successor method.
 */
template <typename Data>
class BSTNode {
  private:
    Data data;

  public:
    BSTNode<Data>* left;
    BSTNode<Data>* right;
    BSTNode<Data>* parent;

    /** Initialize a BSTNode with the given data */
    BSTNode(const Data& d) : data(d) {
      left = right = parent = nullptr;
    }

    /** Set the value of data */
    void setData(const Data& d) { data = d; }

    /** Get the value of data */
    Data getData() {
      if(this == nullptr){
        return NULL;//This doesn't work because the end iterator calling it will return 0, which will match any data with a value of 0.
        //Update: Changed the iterator ==/!= to not use * (which returns curr->getData()), so this should be fine. Leaving here as a failsafe though
      }
      return data;
    }

    /** Returns the node in the BST that is ordered next after the calling node, or null if
     * the calling node is the end of the BST.
    */
    BSTNode<Data>* successor() {
      BSTNode<Data>* current;
      if(right == nullptr){
        current = this;
        while(current != nullptr){
          if(current->parent == nullptr){
            return nullptr;
          }else if(current != current->parent->left){
            current = current->parent;
          }else{
            return current->parent;
          }
        }
      }else{
        current = this->right;
        while(current->left != nullptr){
          current = current->left;
        }
      }
      return current;
    }
};

/**
 * DO NOT CHANGE THIS METHOD
 * Overload operator<< to print a BSTNode's fields to an ostream.
 */
template <typename Data>
ostream& operator<<(ostream& stm, const BSTNode<Data>& n) {
    stm << '[';
    stm << setw(10) << &n;                  // address of the BSTNode
    stm << "; p:" << setw(10) << n.parent;  // address of its parent
    stm << "; l:" << setw(10) << n.left;    // address of its left child
    stm << "; r:" << setw(10) << n.right;   // address of its right child
    stm << "; d:" << n.data;                // its data field
    stm << ']';
    return stm;
}

#endif  // BSTNODE_HPP
