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
    bool nodeExist(TreeNode<T>* node, T value);
    TreeNode<T>* vecToTree(vector<T> list, int start, int end);
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
bool BinarySearchTree<T>::nodeExist(TreeNode<T>* node, T value){
    if(node == nullptr){
        return false;
    }
    if(node->getValue() == value){
        return true;
    }

    bool left = nodeExist(node->getLeftChild(), value);

    if(left){
        return true;
    }

    bool right = nodeExist(node->getRightChild(), value);

    return right;
}

template<typename T>
TreeNode<T>* BinarySearchTree<T>::find(T value){
    TreeNode<T>* current = root;
    int found = 0;

    if(nodeExist(root, value)){
        if(root->getValue() == value){
            return root;
        }else{
            while(found == 0){
                if(current->getLeftChild() != nullptr && current->getLeftChild()->getValue() == value){
                    return current->getLeftChild();
                }else if(current->getRightChild() != nullptr && current->getRightChild()->getValue() == value){
                    return current->getRightChild();
                }else{
                    if(value < current->getValue()){
                        if(current->getLeftChild() != nullptr){
                            current = current->getLeftChild();
                        }
                    }else{
                        if(value > current->getValue()){
                            if(current->getRightChild() != nullptr){
                                current = current->getRightChild();
                            }
                        }
                    }
                }
            }
        }
    }

    return nullptr;
}

template<typename T>
TreeNode<T>* BinarySearchTree<T>::remove(T value){
    TreeNode<T>* current = find(value);
    TreeNode<T>* removed = find(value); //removed node
    TreeNode<T>* left = current->getLeftChild();
    TreeNode<T>* right = current->getRightChild();
    TreeNode<T>* parent = current->getParentNode();

    if(right == nullptr && left == nullptr){ //no child
        if(value < parent->getValue()){
            parent->setLeft(nullptr);
            removed->setParent(nullptr);
        }else{
            parent->setRight(nullptr);
            removed->setParent(nullptr);
        }
    }else if(right != nullptr && left == nullptr){ //one child right child present
        if(value < parent->getValue()){ //left of parent
            parent->setLeft(right);
            right->setParent(parent);

            removed->setRight(nullptr);
            removed->setParent(nullptr);
        }else{
            parent->setRight(right);
            right->setParent(parent);

            removed->setRight(nullptr);
            removed->setParent(nullptr);
        }
    }else if(right == nullptr && left != nullptr){ //one child left child present
        if(value < parent->getValue()){ //left of parent
            parent->setLeft(left);
            left->setParent(parent);

            removed->setLeft(nullptr);
            removed->setParent(nullptr);
        }else{
            parent->setRight(left);
            left->setParent(parent);

            removed->setRight(nullptr);
            removed->setParent(nullptr);
        }
    }else{ //two children
        current = right;

        while(current->getLeftChild() != nullptr){ //next largest element
            current = current->getLeftChild();
        }

        TreeNode<T>* replace = remove(current->getValue());

        right = removed->getRightChild();

        replace->setRight(right);
        replace->setLeft(left);
        replace->setParent(parent);

        if(right != nullptr){
            right->setParent(replace);
        }
        left->setParent(replace);

        removed->setLeft(nullptr);
        removed->setRight(nullptr);
        removed->setParent(nullptr);

        if(root->getValue() == value){
            root = replace;
        }else{
            if(value < parent->getValue()){
                parent->setLeft(replace);
            }else{
                parent->setRight(replace);
            }
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
    vector<T> list;

    for(int i = 0; i < list.size(); i++){
        list.pop_back();
    }

    inOrder(root, list);

    for(int i = 0; i < list.size(); i++){
        cout << list.at(i) << " ";
    }

    root = vecToTree(list, 0, list.size() - 1);
}

template<typename T>
TreeNode<T>* BinarySearchTree<T>::vecToTree(vector<T> list, int start, int end){
    if(start > end){
        return nullptr;
    }

    int mid = (start + end) / 2;
    TreeNode<T>* newRoot = new TreeNode<T>(list.at(mid));

    root->setLeft(vecToTree(list, start, mid - 1));
    root->setRight(vecToTree(list, mid + 1, end));

    return newRoot;
}

#endif //BSTBASE_BINARYSEARCHTREE_H
