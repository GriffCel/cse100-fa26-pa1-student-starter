/**
 * TODO: add file header
 */
#ifndef BST_HPP
#define BST_HPP
#include <iostream>
#include <queue>
#include <vector>
#include "BSTIterator.hpp"
#include "BSTNode.hpp"
using namespace std;

/**
 * TODO: add class header
 */
template <typename Data>
class BST {
  protected:
    // pointer to the root of this BST, or 0 if the BST is empty
    BSTNode<Data>* root;

    // number of Data items stored in this BST.
    unsigned int isize;

    // height of this BST.
    int iheight;

  public:
    /** Define iterator as an aliased typename for BSTIterator<Data>. */
    typedef BSTIterator<Data> iterator;

    /**
     * Default constructor.
     * Initialize an empty BST.
     */
    BST() : root(0), isize(0), iheight(-1) {}

    /**
    */
    BST(const BST<Data>& bst) : root(0), isize(0), iheight(-1) {
        vector<Data> ordered_bst = bst.inorder();
        ordered_bst.shrink_to_fit();
        root = create_balanced_bst(ordered_bst, nullptr);
        iheight = calculate_height(root);
    }

    //Currently causing segmentation faults
    ~BST() {
        deleteAll(root);
        isize = 0;
        iheight = -1;
    }

    bool insert(const Data& item) {
        if(root == nullptr){
            root = new BSTNode<Data>(item);
        }else{
            BSTNode<Data>* curr = root;
            while(true){
                if(item < curr->getData()){
                    if(curr->left == nullptr){
                        BSTNode<Data>* inserted = new BSTNode<Data>(item);
                        inserted->parent = curr;
                        curr->left = inserted;
                        break;
                    }else{
                        curr = curr->left;
                    }
                }else if(curr->getData() < item){
                    if(curr->right == nullptr){
                        BSTNode<Data>* inserted = new BSTNode<Data>(item);
                        inserted->parent = curr;
                        curr->right = inserted;
                        break;
                    }else{
                        curr = curr->right;
                    }
                }else{
                    return false;
                }
            }
        }
        isize++;
        iheight = calculate_height(root);
        return true;
    }

    iterator find(const Data& item) const {
        BST<Data>::iterator itr = begin();
        BST<Data>::iterator fin = end();
        //Changing so that it doesn't care if the tree is sorted so that it can help with the deleteNode function's two-child case
        //Two things are equal when one of them is neither smaller than or greater than the other. As long as 1 is true, we keep looking
        while(*itr < item || item < *itr){
            itr++;
            if(itr == fin){
                return fin;
            }
        }
        return itr;
    }

    bool deleteNode(const Data& item) {
        if(root == nullptr){
            return false;
        }

        BST<Data>::iterator itr = find(item);
        if(itr == end()){
            return false;
        }

        BSTNode<Data>* curr = first(root);
        Data curr_data = curr->getData();
        //Moves curr to the node we want to delete, can safely do this because we previously confirmed the data is in the tree
        while(curr_data < item || item < curr_data){
            curr = curr->successor();
            curr_data = curr->getData();
        }
        //This is only reached if we have found the Node with the data we want to delete,
        //Four cases: 0 child, left only, right only, 2 child
        if(curr->left == nullptr){
            //Here we can handle the cases where the delete node has at most a right child
            if(curr->right == nullptr){
                //deleting root from a size 1 tree
                if(curr->parent == nullptr){
                    delete curr;
                    isize--;
                    iheight = calculate_height(root);
                    return true;
                }
                if(curr == curr->parent->left){
                    curr->parent->left = nullptr;
                }else{
                    curr->parent->right = nullptr;
                }
                delete curr;
                isize--;
                iheight = calculate_height(root);
                return true;
            }else{
                if(curr->parent == nullptr){
                    root = curr->right;
                    delete curr;
                    isize--;
                    iheight = calculate_height(root);
                    return true;
                }
                if(curr == curr->parent->left){
                    curr->parent->left = curr->right;
                }else{
                    curr->parent->right = curr->right;
                }
                delete curr;
                isize--;
                iheight = calculate_height(root);
                return true;
            }
        }else{
            //Here we handle the cases where curr has at least a left child
            if(curr->right == nullptr){
                if(curr->parent == nullptr){
                    root = curr->left;
                    delete curr;
                    isize--;
                    iheight = calculate_height(root);
                    return true;
                }
                if(curr == curr->parent->left){
                    curr->parent->left = curr->left;
                }else{
                    curr->parent->right = curr->left;
                }
                delete curr;
                isize--;
                iheight = calculate_height(root);
                return true;
            }else{
                //Node to delete has two children, potentially more generations.
                //We swap it with its successor, then call the delete function on it again.
                BSTNode<Data>* temp_node = curr->successor();
                Data temp = curr->getData();
                curr->setData(temp_node->getData());
                temp_node->setData(temp);
                //We now call the function again to delete it where it has been swapped to.
                return deleteNode(item);
            }
        }
        return false;
    }

    unsigned int size() const { return isize; }

    int height() const { return iheight; }

    bool empty() const { return isize == 0; }

    //Works
    iterator begin() const {
        BSTNode<Data>* f_node = first(root);
        if(f_node == nullptr){
            return end();
        }else{
            return typename BST<Data>::iterator(f_node);
        }
    }

    /** Return an iterator pointing past the last item in the BST. */
    iterator end() const { return typename BST<Data>::iterator(0); }

    //Works
    vector<Data> inorder() const {
        BST<Data>::iterator itr = begin();
        BST<Data>::iterator fin = end();
        vector<Data> ordered;
        while(itr != fin){
            ordered.push_back(*itr);
            itr++;
        }
        return ordered;
    }

    /**
     * DO NOT CHANGE THIS METHOD
     * Prints a tree, including its structure to an
     * output stream to help with grading and debugging.
     */
    void print(ostream* out) {
        if (empty()) {
            *out << "(Empty tree)" << endl;
            return;
        }

        // Using a queue to traverse a tree is otherwise
        // known as a breadth first traversal of the tree.
        // It's useful here to show which nodes are on which
        // level.
        queue<BSTNode<Data>*> toVisit;
        toVisit.push(root);
        int nodesPerLevel = 1;
        int totalSpacing = 1 << iheight;

        for (int i = 0; i <= iheight; i++) {
            for (int j = 0; j < nodesPerLevel; j++) {
                BSTNode<Data>* curr = toVisit.front();
                toVisit.pop();
                if (curr == nullptr) {
                    *out << "X";
                    // If we have an entire missing subtree, we
                    // would like to print X's in place of all
                    // nodes because it avoids ambiguity
                    toVisit.push(nullptr);
                    toVisit.push(nullptr);
                } else {
                    *out << curr->getData();
                    toVisit.push(curr->left);
                    toVisit.push(curr->right);
                }
                for (int k = 0; k < totalSpacing / nodesPerLevel; k++) {
                    *out << "\t";
                }
            }
            *out << endl;
            nodesPerLevel *= 2;
        }
    }

  private:
  //Works
    static BSTNode<Data>* first(BSTNode<Data>* root) {
        if(root == nullptr){
            return root;
        }else{
            BSTNode<Data>* curr = root;
            while(curr->left != nullptr){
                curr = curr->left;
            }
            return curr;
        }
    }

    //Currently causing segmentation faults
    static void deleteAll(BSTNode<Data>* n) {
        /* Pseudocode:
           if current node is null: return;
           recursively delete left sub-tree
           recursively delete right sub-tree
           delete current node
        */
        if(n == nullptr){
            return;
        }
        deleteAll(n->left);
        deleteAll(n->right);
        delete n;
    }

    //Works as long as the balancing helper method works
    BSTNode<Data>* buildSubtree(vector<Data>& data, int start, int end,
                                int depth) {
        std::vector<Data> needed_values(data.begin() + start, data.begin() + end);
        if(needed_values.empty()){
            return nullptr;
        }else{
            return create_balanced_bst(needed_values, nullptr);
        }
    }

    // Add more helper functions below
    /**
     * Helper function that returns the height of the tree starting at some node by recursively checking all possible routes to leaf nodes.
     * To account for the standard row numbering of BSTs as 0, 1, 2, etc., the base case returns -1;
     */
    int calculate_height(BSTNode<Data>* root){
        if(root == nullptr){
            return -1;
        }else{
            return 1 + max(calculate_height(root->left), calculate_height(root->right));
        }
    }

    /**method for recursively creating a BST through binarily splitting a vector of data values
     * In theory, should work in this way: Given a parent node (use nullptr when calling initially for the root) and a vector of ordered data, choose 
     * the middle element, defaulting to the larger element in the case of an even number of elements. Create a new node with that element, make its
     * parent the node that was passed (which should always be the previously created node), then call the function again to create its children.
     * Base case is when there is a single value left in the data, to avoid weird things happening with the iterator-based constructors.
     */
    BSTNode<Data>* create_balanced_bst(const vector<Data>& ordered_data, BSTNode<Data>* parent_node){
        if(ordered_data.size() == 0){
            return nullptr;
        }
        if(ordered_data.size() == 1){
            BSTNode<Data>* temp = new BSTNode<Data>(ordered_data.at(0));
            temp->parent = parent_node;
            temp->left = nullptr;
            temp->right = nullptr;
            isize++;
            return temp;
        }else{
            int middle_index = ordered_data.size()/2;
            vector<Data> first_half;
            vector<Data> second_half;
            for(int i = 0; i < middle_index; i++){
                first_half.push_back(ordered_data[i]);
            }
            for(int i = middle_index+1; i < (int)(ordered_data.size()); i++){
                second_half.push_back(ordered_data[i]);
            }
            Data to_add = ordered_data.at(middle_index);
            BSTNode<Data>* temp = new BSTNode<Data>(to_add);
            temp->parent = parent_node;
            first_half.shrink_to_fit();
            second_half.shrink_to_fit();
            temp->left = create_balanced_bst(first_half, temp);
            temp->right = create_balanced_bst(second_half, temp);
            isize++;
            return temp;
        }
    }
};

#endif  // BST_HPP
