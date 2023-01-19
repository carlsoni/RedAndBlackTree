//************************************************************************
// ASU CSE310 Assignment #6 Fall 2022
// Author: Ian Carlson
// ASU ID: 1223065376
// Description: Red black tree implementation. See RedBlackTree.h
//              for the Red Black Tree definition
//************************************************************************

//include the relevant header file
//----
#include "RedBlackTree.h"
#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <string>
using namespace std;

//*******************************************************************
//constructor
RedBlackTree::RedBlackTree()
{
      root = NULL;
      nil = NULL;
      rootnil = NULL;
}

//*******************************************************************
//destructor
RedBlackTree::~RedBlackTree()
{
      int nodeSize = deleteNode(root);
	cout << "The number of nodes deleted: " << nodeSize << endl;
}

//**************************************************************
//Accessor for the root of the red-black tree

//gets the root
Node* RedBlackTree::getRoot(){
      return root;
}

//*******************************************************************
//delete the sub-tree rooted at 'node' and return number of nodes deleted
//This should be defined as a recursive function

int RedBlackTree::deleteNode(Node* node){
      int val1 = 0;
      int val2 = 0;
      int val3 = 0;
      if(node != nil && node != rootnil){
            val1 = deleteNode(node->leftChild);
            val2 = deleteNode(node->rightChild);
            val3 = 1;
      }
      return val1 + val2 + val3;
}

//****************************************************************
//This is the general BST insertion operation.
//It does not care about the color of the newly added node.

//moves the node around to the appropriate spot in the tree
void RedBlackTree::insertNode(Node* node){
      Node * y = NULL;
      Node * x = root;

      string key = to_string(node->vin) + node->model + node->make;

      while(x != nil && x != NULL){
            y = x;
            if(node->vin < x->vin || (node->vin == x->vin && compareNodes(x, key) > 0)){
                  x = x->leftChild;
            }
            else{
                  x = x->rightChild;
            }
      }
      node->parent = y;
      // initializes the root node and the rootnil node which is the nodes parent
      if(y == NULL){

            rootnil = new Node();
            rootnil->make = "";
            rootnil->model = "";
            rootnil->vin = -1;
            rootnil->leftChild = root;
            rootnil->rightChild = root;
            rootnil->parent = rootnil;
            rootnil->color = "BLACK";

            root = node;
            root->parent = rootnil;
            root->leftChild = nil;
            root->rightChild = nil;
            
      }
      else if(node->vin < y->vin || (node->vin == y->vin && compareNodes(y, key) > 0)){
            y->leftChild = node;
      }
      else{
            y->rightChild = node;
      }
      
      fixUp(node);  
      
      
}

//*******************************************************************
//At beginning, each newly added node will always be RED,
//this may violate the red-black tree property #4. fixUp()
//function will restore the property.

void RedBlackTree::fixUp(Node *node){
      Node *y;
      while(node->parent->color == "RED"){
           //the new nodes parrent is a left chiled
            if(node->parent == node->parent->parent->leftChild){
                  //cout << "I got here" << endl;
                  //y is the uncle of the new node
                  y = node->parent->parent->rightChild;

                  //case 1 
                  if(y->color == "RED"){
                        node->parent->color = "BLACK";
                        y->color = "BLACK";
                        node->parent->parent->color = "RED";
                        node = node->parent->parent;
                  }
                  else {
                        if(node == node->parent->rightChild){
                              node = node->parent;
                              leftRotate(node);
                        }
                        node->parent->color = "BLACK";
                        node->parent->parent->color = "RED";
                        rightRotate(node->parent->parent);
                  }
            }
            // the new nodes parent is a right child
            else if(node->parent == node->parent->parent->rightChild){
                  // set y to the uncle of the new node
                  y = node->parent->parent->leftChild;
                  // the uncles color is red case 1
                  if(y->color == "RED"){
                        node->parent->color = "BLACK";
                        y->color = "BLACK";
                        node->parent->parent->color = "RED";
                        node = node->parent->parent;  
                  }
                  // the uncles color is black
                  else{
                        // node is a left child
                        if(node == node->parent->leftChild){
                              node = node->parent;
                              rightRotate(node);
                        }
                        node->parent->color = "BLACK";
                        node->parent->parent->color = "RED";
                        leftRotate(node->parent->parent);
                  }
            }
      }
      root->color = "BLACK";
}

//*****************************************************
//This function print the pre-order traversal of the
//subtree rooted at 'node'.It's a recursive function

void RedBlackTree::preOrderTraversal(Node * node){
       if(node != nil && node != rootnil){
            print(node);
            preOrderTraversal(node->leftChild);
            preOrderTraversal(node->rightChild);
      }
}

//**************************************************
//This function print the in-order traversal of the
//subtree rooted at 'node'.It's a recursive function

void RedBlackTree::inorderTraversal(Node* node){
      if(node != nil && node != rootnil){
            inorderTraversal(node->leftChild);
            print(node);
            inorderTraversal(node->rightChild);
      }
}

//**************************************************
//This function print the post-order traversal of the
//subtree rooted at 'node'.It's a recursive function

void RedBlackTree::postOrderTraversal(Node *node){
       if(node != nil && node != rootnil){
            postOrderTraversal(node->leftChild);
            postOrderTraversal(node->rightChild);
            print(node);
      }
}

//**************************************************************
//This function returns a pointer points to the minimum node from
//the current sub-tree rooted at 'node'. It should be designed as
//a recursive function

Node* RedBlackTree::findMinimumNode(Node* node){

      while (node->leftChild != nil)
      {
            node = node->leftChild;
      }      
      return node;
}

//**************************************************************
//This function returns a pointer points to the maximum node from
//the current sub-tree rooted at 'node'. It should be designed as
//a recursive function

Node* RedBlackTree::findMaximumNode(Node* node){
      while(node->rightChild != nil){
            node = node->rightChild;
      }
      return node;
}

//**************************************************************
//This function search the tree for a given key of a Car
//Note: key is the combination of vin, model and make of the Car
//It returns a pointer points to the node if founded; otherwise it returns NULL

Node* RedBlackTree::treeSearch(int vin, string model, string make){
      Node * n = root;
      string key = to_string(vin) + model + make;

      while(n != nil && compareNodes(n, key) != 0){
            if(vin < n->vin || (n->vin == vin && compareNodes(n, key) < 0)){
                  n = n->leftChild;
            }
            else{
                  n = n->rightChild;
            }
      }
      if(n == nil){
            cout << left;
             cout << setw(8)  << vin
              << setw(12) << model
              << setw(12) << make
              << setw(10) << fixed << setprecision(2) << "is NOT FOUND." << endl;
         }
         else{
            cout << left;
             cout << setw(8)  << vin
              << setw(12) << model
              << setw(12) << make
              << setw(10) << fixed << setprecision(2) << "is FOUND." << endl;
            }
      return n;
}

//****************************************************
//This function left-rotate the BST rooted at 'node'

void RedBlackTree::leftRotate(Node* node){
      Node * y = node->rightChild;
      node->rightChild = y->leftChild;

      if(y->leftChild != nil){
            y->leftChild->parent = node;
      }

      y->parent = node->parent;

      if(node->parent == rootnil){
            root = y;
      }
      else if(node == node->parent->leftChild){
            node->parent->leftChild = y;
      }
      else{
            node->parent->rightChild = y;
      }
      
      y->leftChild = node;
      node->parent = y;
}


//***************************************************
//This function right-rotate the BST rooted at 'node'

void RedBlackTree::rightRotate(Node * node){
      Node *y = node->leftChild;
      node->leftChild = y->rightChild;
 
      if (y->rightChild != nil){
            y->rightChild->parent = node;
      }

      y->parent = node->parent;
 
      if (node->parent == rootnil){
            root = y;
      }
      else if (node == node->parent->leftChild){
            node->parent->leftChild = y;
      }
      else{
            node->parent->rightChild = y;
      }

      y->rightChild = node;
      node->parent = y;
}


//**************************************************************
//This function finds the predecessor of the given 'node'
//it prints the relevant predecessor info. on screen and also
//return a pointer that points to the predecessor

Node* RedBlackTree::findPredecessorNode(Node* node){
      if(node->leftChild != nil){
            return findMaximumNode(node->leftChild);
      }

      Node * y = node->parent;

      while(y != nil && node == y->leftChild){
            node = y;
            y = y->parent;
      }
      return y;
}

//**************************************************************
//This function finds the successor of the given 'node'
//it prints the relevant successor info. on screen and also return
//a pointer that points to the successor node

Node* RedBlackTree::findSuccessorNode(Node* node){
      
      if(node->rightChild != nil){
            return findMinimumNode(node->rightChild);
      }

      Node* y = node->parent;

      while(y != nil && node == y->rightChild){
            node = y;
            y = y->parent;
      }
      return y;
}
//****************************************************************
//This function find the minimum node of the entire red-black tree
//It print out the minimum node info. on screen if tree is not empty
//or print Tree is empty. No Minimum. message on screen.

void RedBlackTree::treeMinimum(){
      if(root == NULL){
            cout << "No Mninmum" << endl;
      }
      else{
            Node* n = findMinimumNode(root);
            print(n);
      }
}

//**************************************************************
//This function find the maximum node of the entire red-black tree
//It print out the maximum node info. on screen if tree is not empty
//or print Tree is empty. No Maximum. message on screen.

void RedBlackTree::treeMaximum(){
      if(root == NULL){
            cout << "No maximum" << endl;
      }
      else{
            Node* n = findMaximumNode(root);
            print(n);
      }
}

//****************************************************************************
//This function print out the pre-order traversal of the entire red-black tree

void RedBlackTree::treePreorder(){
      preOrderTraversal(root);
}

//***************************************************************************
//This function print out the in-order traversal of the entire red-black tree

void RedBlackTree::treeInorder(){
      inorderTraversal(root);
}

//*****************************************************************************
//This function print out the post-order traversal of the entire red-black tree

void RedBlackTree::treePostorder(){
      postOrderTraversal(root);
}

//******************************************************************
//Given a Car key, this function first check whether the
//Car is inside the tree or not, if it is inside, it will print
//its predecessor info. on screen, if not, it print an error message

void RedBlackTree::treePredecessor(int vin, string model, string make){
      Node * n = treeSearch(vin, model, make);
      Node * x = findPredecessorNode(n);

      if(x == nil || x == rootnil){
            cout << "Its Predecessor does NOT EXIST" << endl;
      }
      else{
            cout << "Its Predecessor is:" << endl;
            print(x);
      }
}

//******************************************************************
//Given a Car key, this function first check whether the
//Car is inside the tree or not, if it is inside, it will print
//its successor info. on screen, if not, it print an error message

void RedBlackTree::treeSucessor(int vin, string model, string make){
      Node* n = treeSearch(vin, model, make);
      Node *x = findSuccessorNode(n);

      if(x == nil || x == rootnil){
            cout << "Its Successor does NOT EXIST" << endl;
      }
      else{
            cout << "Its Successor is:" << endl;
            print(x);
      }
}

//**************************************************************
//This function create a node from the given info., then insert
//the node inside the red-black tree. Note: at beginning, the newly
//added node should always be 'RED'

void RedBlackTree::treeInsert(int vin, string model, string make, double price){
      Node * newNode = new Node();
      if(root == NULL){
            nil = new Node();
            nil->make = "";
            nil->model = "";
            nil->vin = -1;
            nil->leftChild = nil;
            nil->rightChild = nil;
            nil->parent = nil;
            nil->color = "BLACK";
      }
      newNode->color = "RED";

      newNode->make = make;
      newNode->model = model;
      newNode->vin = vin;
      newNode->price = price;
      newNode->parent = nil;
      newNode->rightChild = nil;
      newNode->leftChild = nil;

      insertNode(newNode);

}


//******************************************************************
//Given a 'node', this function prints all the node information on screen
void RedBlackTree::print(Node *node)
{
      cout << left;
      cout << setw(8)  << node->vin
           << setw(12) << node->model
           << setw(12) << node->make
           << setw(10) << fixed << setprecision(2) << node->price;
      cout << right << setw(7) << node->color << endl;
}

//**************************************************************
//Given a Node 'node1', this function compares it with another
//node's key.
//key is a string combination of vin + model + make
//It returns a negative number if in alphabetical order, key2 is
//in front of 'node1'; otherwise it returns a positive number

// returns 1 if key is greater than k2
int RedBlackTree::compareNodes(Node *node, string key){
      string k2 = to_string(node->vin) + node->model + node->make;
      return key.compare(k2);
}