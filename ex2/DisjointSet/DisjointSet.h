#ifndef DISJOINTSET_H
#define DISJOINTSET_H

#include "HashTable.h"
#include "UpTreeNode.h"
#include "UpTree.h"
#include <stdexcept>
#include <memory>

template <typename ValueType, typename KeyType = int, typename HashFunc = IntHash>
class DisjointSet {
private:
    HashTable<KeyType, std::shared_ptr<Node<ValueType>>, HashFunc> elementMap;
    UpTree<ValueType> upTree;

public:
    DisjointSet(size_t initialCapacity = 101);
    void makeSet(const ValueType& element);
    ValueType& find(const KeyType& element);
    void unite(const KeyType& element1, const KeyType& element2);
    bool connected(const KeyType& element1, const KeyType& element2) const;
    int getSize(const KeyType& element) const;
    int getRank(const KeyType& element) const;
};

// Implementation of DisjointSet

template <typename ValueType, typename KeyType, typename HashFunc>
DisjointSet<ValueType, KeyType, HashFunc>::DisjointSet(size_t initialCapacity)
    : elementMap(initialCapacity, HashFunc()) {}

template <typename ValueType, typename KeyType, typename HashFunc>
void DisjointSet<ValueType, KeyType, HashFunc>::makeSet(const ValueType& element) {
    KeyType key = element->get_key();
    if (elementMap.contains(key)) {
        throw std::invalid_argument("Element already exists in the disjoint set.");
    }

    auto newNode = std::make_shared<Node<ValueType>>(element);
    elementMap.insert(key, newNode);
}

template <typename ValueType, typename KeyType, typename HashFunc>
ValueType& DisjointSet<ValueType, KeyType, HashFunc>::find(const KeyType& element) {
    if (!elementMap.contains(element)) {
        throw std::invalid_argument("Element not found in the disjoint set.");
    }
    auto node = elementMap.get(element);
    return upTree.findExternal(node)->data;
}

template <typename ValueType, typename KeyType, typename HashFunc>
void DisjointSet<ValueType, KeyType, HashFunc>::unite(const KeyType& element1, const KeyType& element2) {
    if (!elementMap.contains(element1) || !elementMap.contains(element2)) {
        throw std::invalid_argument("One or both elements not found in the disjoint set.");
    }

    auto node1 = elementMap.get(element1);
    auto node2 = elementMap.get(element2);
    upTree.unite(node1, node2, node1->data->get_rank(), node2->data->get_rank());
}

template <typename ValueType, typename KeyType, typename HashFunc>
bool DisjointSet<ValueType, KeyType, HashFunc>::connected(const KeyType& element1, const KeyType& element2) const {
    auto node1 = elementMap.get(element1);
    auto node2 = elementMap.get(element2);
    auto root1 = upTree.findExternal(node1);
    auto root2 = upTree.findExternal(node2);

    return root1 == root2;
}

template <typename ValueType, typename KeyType, typename HashFunc>
int DisjointSet<ValueType, KeyType, HashFunc>::getSize(const KeyType& element) const {
    auto node = elementMap.get(element);
    return upTree.findExternal(node)->size;
}

template <typename ValueType, typename KeyType, typename HashFunc>
int DisjointSet<ValueType, KeyType, HashFunc>::getRank(const KeyType& element) const {
    auto node = elementMap.get(element);
    return upTree.getRank(node);
}

#endif // DISJOINTSET_H