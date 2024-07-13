#include <stdio.h>
#include <iostream>

template<class T>
class AVLNode{
    public:
    AVLNode(const T& val) : data(val), parent(nullptr) ,left_son(nullptr), right_son(nullptr) , height(0) {};
    const T& getData() const { return data; }; 
    void setParent(AVLNode* node) { parent = node; };
    AVLNode* getParent() const { return parent; };
    void setLeft(AVLNode* node);
    AVLNode* getLeft() const { return left_son; };
    void setRight(AVLNode* node);
    AVLNode* getRight() const { return right_son; };
    int getHeight() const { return height; };
    void increaseHeight() { height++; };
    void decreaseHeight() { height--; };
    void setHeight(int h) { height = h; };
    int getBF() const;
    
    private:
    T data;
    AVLNode* parent;
    AVLNode* left_son;
    AVLNode* right_son;
    int height;

    AVLNode() {};
};

template<class T>
void AVLNode<T>::setLeft(AVLNode* node){
    if(node != nullptr){
        node->setParent(this);
    }
    left_son = node;
}

template<class T>
void AVLNode<T>::setRight(AVLNode* node){
    if(node != nullptr){
        node->setParent(this);
    }
    right_son = node;
}

template<class T>
int AVLNode<T>::getBF() const{
    int left_height = -1;
    int right_height = -1;
    if(left_son != nullptr){
        left_height = left_son->getHeight();
    }
    if(right_son != nullptr){
        right_height = right_son->getHeight();
    }
    return left_height - right_height;
}
