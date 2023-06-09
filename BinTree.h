#ifndef BinTree_h
#define BinTree_h

//importing required libraries
#include <iostream>
#include <string>
#include "Node.h"


//template class BinTree
template <typename T>
class BinTree
{
private:
    //instance variable declaration
    Node<T>* root;
    
    //private helper methods
    Node<T>* insertRecursive(Node<T>* curr, Node<T>* newNode); //recursive helper method to insert a new node in the BST
    Node<T>* searchRecurive(Node<T>* curr, Node<T>* node); //recursive helper method to search for a node in the BST
    Node<T>* removeRecursive(Node<T>* node, Node<T>* curr); //recursive helper method to remove a node in the BST
    Node<T>* leftMax(Node<T>* baseNode); //method that returns the righmost child (max value) in the left subtree of the node
    void deleteHelper(Node<T>* treeNode);   //helper method that deletes all the nodes in the BST
    
public:
    //empty constructor
    BinTree(){root = nullptr;}
    
    //overloaded constructor
    BinTree(Node<T>* n){root = n;}
    
    //accessor method for the root of the BST
    Node<T>* getRoot(){return root;}
    
    //mutator method for the root of the BST
    void setRoot(Node<T>* n){root = n;}
        
    //method to insert a new object in a node in the BST
    void insert(T obj);
    
    //method to search for an object in any nodes in the BST
    Node<T>* search(T obj){return searchRecurive(getRoot(), new Node<T>(obj));}
    
    //method to remove a node containing an object from the BST
    Node<T>* remove(T obj){return removeRecursive(new Node<T>(obj), getRoot());}
    
    //prints the BST in in-order
    void inorder(Node<T>* treeNode);
    
    //method to delete the BST
    void deleteBST(){deleteHelper(getRoot());}
    
};

//method that takes in the object and then creates a node with that object and inserts that in the BST
template <typename T>
void BinTree<T>::insert(T obj)
{
    //creating a node to contain the object to be inserted
    Node<T>* newNode = new Node<T>(obj);
    //if the tree is not empty
    if (getRoot())
    {
        //calling the recursive function with the root and the new node to be inserted as the arguments
        insertRecursive(getRoot(), newNode);
    }
    //if the tree is empty
    else
    {
        //setting the root pointer to the new node containg the object to be inserted
        setRoot(newNode);
    }
}

//recursive helper method for insert method that takes in the current node and the new node to be inserted as parameters and inserts the new node in the BST
template <typename T>
Node<T>* BinTree<T>::insertRecursive(Node<T>* curr, Node<T>* newNode)
{
    //if the new node is less than the current node and the current node has a left node
    if ((*newNode < *curr) && (curr->getLeft()))
    {
        //calls the function recursively with the left child of the current node and the new node as the arguments
        insertRecursive(curr->getLeft(), newNode);
    }
    //if the new node is greater than the current node and the current node has a right child
    else if ((*newNode > *curr) && (curr->getRight()))
    {
        //calls the function recursively with the right child of the current node and the new node as the arguments
        insertRecursive(curr->getRight(), newNode);
    }
    //if the new node is greater than the current node and the current node does not have a right child
    //or the new node is less than the current node and the current node does not have a left child
    else
    {
        //if the new node is less than the current node
        if (*newNode < *curr)
        {
            //inserting the new node as the left child of the current node and returning the pointer to that node
            curr->setLeft(newNode);
            return curr->getLeft();
        }
        //if the new node is greater than the current node
        else
        {
            //inserting the new node as the right child of the current node and returning the pointer to that node
            curr->setRight(newNode);
            return curr->getRight();
        }
    }
    //returning current node
    return curr;
}

//recursive search funtion function that takes in the current node and the node we are searching for as the parameters and searches the BST for that node
template <typename T>
Node<T>* BinTree<T>::searchRecurive(Node<T>* curr, Node<T>* node)
{
    //if the current node is a nullptr or the content in the current node is equal to the content in the node we are searching for
    if (curr == nullptr)
    {
        //return the pointer to the current node

        return curr;
    }
    else if (*node == *curr)
    {
        return curr;
    }
    //if the node we are searching for is less than the current node
    else if (*node < *curr)
    {
        //calls the function recursively with the left child of the current node and the node we are searching for as the arguments
        return searchRecurive(curr->getLeft(), node);
    }
    //if the node we are searching for is greater than the current node
    else
    {
        //calls the function recursively with the right child of the current node and the node we are searching for as the arguments
        return searchRecurive(curr->getRight(), node);
    }
}


//recursive remove function that takes in the node to be removed and the current node as the parameters
template <typename T>
Node<T>* BinTree<T>::removeRecursive(Node<T>* node, Node<T>* curr)
{
    //if the current node is a nullptr
    if (curr == nullptr)
    {
        //returning nullptr to denote that such a node does not exist in the BST
        return nullptr;
    }
    //if the node to be removed less than the current node
    else if (*node < *curr)
    {
        //calling the function recursively with the node to be removed and the left child of the current node as arguments and making the return value of that function the left child of the current node
        curr->setLeft(removeRecursive(node, curr->getLeft()));
    }
    //if the node to be removed greater than the current node
    else if (*node > *curr)
    {
        //calling the function recursively with the node to be removed and the right child of the current node as arguments and making the return value of that function the right child of the current node
        curr->setRight(removeRecursive(node, curr->getRight()));
    }
    //if the current node is the node that we want to remove
    else
    {
        //if the current node has 2 child nodes
        if (curr->getRight() && curr->getLeft())
        {
            //storing the rightmost child in the left subtree of the current node in temp1
            Node<T>* temp1 = leftMax(curr);
            //setting the data of the current node to the data of leftMax (rightmost child in the left subtree of the current node in temp1)
            curr->setData(temp1->getData());
            //calling the function recursively with temp1 and the left child of the current node as the arguments and storing the return value as the left node of the current node
            curr->setLeft(removeRecursive(temp1, curr->getLeft()));
        }
        //if the current node only has a left child
        else if (curr->getLeft())
        {
            //storing the left child of the current node in temp
            Node<T>* temp = curr->getLeft();
            //deleting the current node and returning the pointer to the node that was removed to be swapped with the other node in the recursion
            delete curr;
            return temp;
        }
        //if the current node only has a right child
        else if (curr->getRight())
        {
            //storing the right child of the current node in temp
            Node<T>* temp = curr->getRight();
            //deleting the current node and returning the pointer to the node that was removed to be swapped with the other node in the recursion
            delete curr;
            return temp;
        }
        //if the current node has no child node
        else
        {
            //delete the current node and return nullptr
            delete curr;
            curr = nullptr;
            return curr;
        }
    }
    //return the current node
    return curr;
}

//method to find the rightmost child in the left subtree of the base node, which takes in the base node as the parameter
template <typename T>
Node<T>* BinTree<T>::leftMax(Node<T>* baseNode)
{
    //curr pointing to the left child of the bast node
    Node<T>* curr = baseNode->getLeft();
    //loop runs until the current node has a right child and stops when the node does not have a right child
    while (curr->getRight())
    {
        curr = curr->getRight();
    }
    //return the right most child of the left subtree
    return curr;
}

//method to output the contents of the BST using in-order traversal
template <typename T>
void BinTree<T>::inorder(Node<T>* treeNode)
{
    //if the node is not nullptr
    if(treeNode)
    {
        //calls the function recursively with the right child first
        inorder(treeNode->getRight());
        //outputting the current node
        std::cout << treeNode << std::endl;
        //calls the function recursively with the left child
        inorder(treeNode->getLeft());
    }
}

//helper method to delete the BST using post-order traversal
template <typename T>
void BinTree<T>::deleteHelper(Node<T>* treeNode)
{
    //if the node is not nullptr
    if(treeNode)
    {
        //calls the function recursively with the left child first
        deleteHelper(treeNode->getLeft());
        //calls the function recursively with the right child
        deleteHelper(treeNode->getRight());
        //deletes the current node
        delete treeNode;
    }
}

#endif /* BinTree_h */
