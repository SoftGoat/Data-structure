#ifndef UPTREE_H
#define UPTREE_H

#include "UpTreeNode.h"
#include <memory>

template <typename T>
class UpTree {
private:
    std::shared_ptr<Node<T>> find(std::shared_ptr<Node<T>> node) const;

public:
    UpTree();
    ~UpTree();

    void unite(std::shared_ptr<Node<T>> x, std::shared_ptr<Node<T>> y, int Xrank, int Yrank);
    bool connected(std::shared_ptr<Node<T>> x, std::shared_ptr<Node<T>> y) const;
    int getRank(std::shared_ptr<Node<T>> x) const;
    std::shared_ptr<Node<T>> findExternal(std::shared_ptr<Node<T>> node) const;
};

// Implementation of UpTree

template <typename T>
UpTree<T>::UpTree() {}

template <typename T>
UpTree<T>::~UpTree() {}

template <typename T>
std::shared_ptr<Node<T>> UpTree<T>::find(std::shared_ptr<Node<T>> node) const {
    if (node->parent != node) {
        if (node->parent->parent != node->parent) {
            node->rank += node->parent->rank;
        }
        node->parent = find(node->parent);
    }
    return node->parent;
}

template <typename T>
std::shared_ptr<Node<T>> UpTree<T>::findExternal(std::shared_ptr<Node<T>> node) const {
    return find(node);
}

template <typename T>
void UpTree<T>::unite(std::shared_ptr<Node<T>> x, std::shared_ptr<Node<T>> y, int Xrank, int Yrank) {
    auto rootX = find(x);
    auto rootY = find(y);

    if (rootX == rootY) {
        return;
    }

    if (rootX->size < rootY->size) {
        rootX->parent = rootY;
        if (Xrank < Yrank) {
            rootX->rank += rootY->size - 1;
        } else {
            rootY->rank += rootX->size - 1;
        }
        rootY->size += rootX->size;
    } else {
        rootY->parent = rootX;
        if (Xrank < Yrank) {
            rootX->rank += rootY->size - 1;
        } else {
            rootY->rank += rootX->size - 1;
        }
        rootX->size += rootY->size;
    }
}

template <typename T>
bool UpTree<T>::connected(std::shared_ptr<Node<T>> x, std::shared_ptr<Node<T>> y) const {
    return find(x) == find(y);
}

template <typename T>
int UpTree<T>::getRank(std::shared_ptr<Node<T>> x) const {
    int realRank = 1;
    find(x);
    while (x->parent != x) {
        realRank += x->rank;
        x = x->parent;
    }
    return realRank;
}

#endif // UPTREE_H