//
// Created by aaron on 11/7/2020.
//

#ifndef BSTBASE_BINARYSEARCHTREE_H
#define BSTBASE_BINARYSEARCHTREE_H
#include <iostream>
#include <vector>
#include "TreeNode.h"
using namespace std;

template<typename T>
class BinarySearchTree{
public:
    BinarySearchTree(TreeNode<T>* r);
    void traverse(vector<T> &list) const;
    void addNode(TreeNode<T>* node);
    void clearContents();
    TreeNode<T>* find(T value);
    TreeNode<T>* remove(T value);
    TreeNode<T>* getRoot();
    void rebalance();
    void inOrder(TreeNode<T>* node, vector<T>& list) const;
    void postClear(TreeNode<T>* node);
private:
    TreeNode<T>* root;
};

template<typename T>
BinarySearchTree<T>::BinarySearchTree(TreeNode<T>* r){
    root = r;
}

template<typename T>
void BinarySearchTree<T>::inOrder(TreeNode<T>* node, vector<T>& list) const{
    if(node != nullptr){
        inOrder(node->getLeftChild(), list);
        list.push_back(node->getValue());
        inOrder(node->getRightChild(), list);
    }
}

template<typename T>
void BinarySearchTree<T>::traverse(vector<T> &list) const{
    vector<T> order;
    inOrder(root, order);

    for(int i = 0; i < order.size(); i++){
        list.push_back(order.at(i));
    }
}

template<typename T>
void BinarySearchTree<T>::addNode(TreeNode<T>* node){
    int value = node->getValue();
    TreeNode<T>* current = root;
    int found = 0;

    while(found == 0){
        if(value < current->getValue()){ //less than current
            if(current->getLeftChild() == nullptr){
                current->setLeft(node);
                node->setParent(current);
                found = 1;
            }else{
                current = current->getLeftChild();
            }
        }else{ //more than current
            if(current->getRightChild() == nullptr){
                current->setRight(node);
                node->setParent(current);
                found = 1;
            }else{
                current = current->getRightChild();
            }
        }
    }
}

template<typename T>
void BinarySearchTree<T>::postClear(TreeNode<T>* node){
    if(node == nullptr){
        return;
    }
    postClear(node->getLeftChild());
    postClear(node->getRightChild());

    node->setLeft(nullptr);
    node->setRight(nullptr);
    node->setParent(nullptr);
}

template<typename T>
void BinarySearchTree<T>::clearContents(){
    postClear(root);
}

template<typename T>
TreeNode<T>* BinarySearchTree<T>::find(T value){
    TreeNode<T>* current = root;
    if(current->getValue() == value){
        return current;
    }

    if(current->getValue() < value){
        return find(current->getRightChild()->getValue());
    }

    return find(current->getLeftChild()->getValue());
}

template<typename T>
TreeNode<T>* BinarySearchTree<T>::remove(T value){
    TreeNode<T>* node = find(value);
    TreeNode<T>* removed = find(value);
    TreeNode<T>* parent = node->getParentNode();
    TreeNode<T>* left = node->getLeftChild();
    TreeNode<T>* right = node->getRightChild();

    if(left == nullptr && right == nullptr){ //no children
        if(node->getValue() < parent->getValue()){ //smaller than parent
            parent->setLeft(nullptr);
        }else{ //bigger than parent
            parent->setRight(nullptr);
        }
    }else if(left == nullptr || right == nullptr){ //has one children
        if(node->getValue() < parent->getValue()){ //less than parent
            if(left != nullptr){ //left child present
                parent->setLeft(left);
                left->setParent(parent);
            }else{ //right child present
                parent->setLeft(right);
                right->setParent(parent);
            }
        }else{ //more than parent
            if(left != nullptr){ //left child present
                parent->setRight(left);
                left->setParent(parent);
            }else{ //right child present
                parent->setRight(right);
                right->setParent(parent);
            }
        }
    }else{ //two children
        TreeNode<T>* current = node->getRightChild();

        while(current->getLeftChild() != nullptr){
            if(current->getLeftChild() == nullptr){
                node->setValue(current->getValue());

                current = current->getParentNode();
                current->setLeft(nullptr);
            }

            current = current->getLeftChild();
        }
    }

    return removed;
}

template<typename T>
TreeNode<T>* BinarySearchTree<T>::getRoot(){
    return root;
}

template<typename T>
void BinarySearchTree<T>::rebalance(){

}

#endif //BSTBASE_BINARYSEARCHTREE_H
