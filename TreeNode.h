//
// Created by aaron on 11/7/2020.
//

#ifndef BSTBASE_TREENODE_H
#define BSTBASE_TREENODE_H
#include <iostream>
using namespace std;

template<typename T>
class TreeNode{
public:
    TreeNode(T amount);

    TreeNode<T>* getLeftChild();
    TreeNode<T>* getRightChild();
    TreeNode<T>* getParentNode();
    T getValue();

    void setLeft(TreeNode<T>* point);
    void setRight(TreeNode<T>* point);
    void setParent(TreeNode<T>* point);
private:
    T value;
    TreeNode<T>* left;
    TreeNode<T>* right;
    TreeNode<T>* parent;
};

template<typename T>
TreeNode<T>::TreeNode(T amount){
    value = amount;
    left = nullptr;
    right = nullptr;
    parent = nullptr;
}

template<typename T>
void TreeNode<T>::setLeft(TreeNode<T> *point){
    left = point;
}

template<typename T>
void TreeNode<T>::setRight(TreeNode<T> *point){
    right = point;
}

template<typename T>
void TreeNode<T>::setParent(TreeNode<T> *point){
    parent = point;
}

template<typename T>
TreeNode<T>* TreeNode<T>::getLeftChild(){
    return left;
}

template<typename T>
TreeNode<T>* TreeNode<T>::getRightChild(){
    return right;
}

template<typename T>
TreeNode<T>* TreeNode<T>::getParentNode(){
    return parent;
}

template<typename T>
T TreeNode<T>::getValue(){
    return value;
}

#endif //BSTBASE_TREENODE_H
