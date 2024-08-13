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
    /**
     * @brief Constructs a new DisjointSet object with a given initial capacity.
     * 
     * Initializes the hash table and up-trees with the specified capacity.
     * 
     * @param initialCapacity The initial capacity for the hash table.
     */
    DisjointSet(size_t initialCapacity = 101);

    /**
     * @brief Adds an element to the disjoint set.
     * 
     * Initializes the element as its own set within the disjoint set structure.
     * 
     * @param element The element to add to the disjoint set.
     * @param key The key to associate with the element.
     * @return True if the element was successfully added, false otherwise.
     */
    bool makeSet(const ValueType& element, const KeyType& key);


    /**
     * @brief Adds an element to the disjoint set.
     * 
     * Initializes the element as its own set within the disjoint set structure.
     * 
     * @param element The element to add to the disjoint set.
     * @return True if the element was successfully added, false otherwise.
     */
    bool makeSet(const ValueType& element);

    /**
     * @brief Finds the representative of the set containing the given element.
     * 
     * Uses path compression to optimize future queries and returns the representative element.
     * 
     * @param element The element to find within the disjoint set.
     * @return The representative element of the set containing the given element.
     */
    ValueType& find(const KeyType& element);

    ValueType& find_leaf(const KeyType& element);

    /**
     * @brief Unites the sets containing two elements.
     * 
     * Merges the sets containing the two specified elements, using the rank to determine the structure of the merged set.
     * 
     * @param element1 The first element to unite.
     * @param element2 The second element to unite.
     */
    bool unite(const KeyType& element1, const KeyType& element2);

    /**
     * @brief Checks if two elements are in the same set.
     * 
     * Determines if the two specified elements are part of the same connected component in the disjoint set.
     * 
     * @param element1 The first element to check.
     * @param element2 The second element to check.
     * @return True if both elements are in the same set, false otherwise.
     */
    bool connected(const KeyType& element1, const KeyType& element2) const;

    /**
     * @brief Gets the size of the set containing the given element.
     * 
     * Returns the number of elements in the set that contains the specified element.
     * 
     * @param element The element whose set size is being queried.
     * @return The size of the set containing the given element.
     */
    int getSize(const KeyType& element) const;

    /**
     * @brief Gets the rank of the set containing the given element.
     * 
     * Returns the rank of the set that contains the specified element.
     * 
     * @param element The element whose set rank is being queried.
     * @return The rank of the set containing the given element.
     */
    int getRank(const KeyType& element) const;

    int getRootRank(const KeyType& element) const;

    /**
     * @brief Adds a rank to the element.
     * 
     * Adds a rank to the element.
     * 
     * @param element The element whose rank is being updated.
     * @param rank The rank to add to the element.
     * @return True if the rank was added, false otherwise.
     */
    bool addAbsRank(const KeyType& element, int rank);
};


template <typename ValueType, typename KeyType, typename HashFunc>
    bool DisjointSet<ValueType, KeyType, HashFunc>::addAbsRank(const KeyType& element, int rank){
        try{
            auto node = elementMap.get(element);
            node->abs_rank += rank;
            return true;
        }
        catch(const std::out_of_range& e)
        {
            return false;
        }
    }


// Implementation of DisjointSet

template <typename ValueType, typename KeyType, typename HashFunc>
DisjointSet<ValueType, KeyType, HashFunc>::DisjointSet(size_t initialCapacity)
    : elementMap(initialCapacity, HashFunc()) {}

template <typename ValueType, typename KeyType, typename HashFunc>
bool DisjointSet<ValueType, KeyType, HashFunc>::makeSet(const ValueType& element, const KeyType& key) {
    if (elementMap.contains(key)) {
        throw std::invalid_argument("Element already exists.");
    }

    auto newNode = std::make_shared<Node<ValueType>>(element);
    elementMap.insert(key, newNode);
    return true;
}

template <typename ValueType, typename KeyType, typename HashFunc>
bool DisjointSet<ValueType, KeyType, HashFunc>::makeSet(const ValueType& element) {
    if (!element) {
        return false;
    }  
    KeyType key = element->get_key();
    if (elementMap.contains(key)) {
        return false;
    }

    auto newNode = std::make_shared<Node<ValueType>>(element);
    elementMap.insert(key, newNode);
    return true;
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
ValueType& DisjointSet<ValueType, KeyType, HashFunc>::find_leaf(const KeyType& element) {
    if (!elementMap.contains(element)) {
        throw std::invalid_argument("Element not found in the disjoint set.");
    }
    auto node = elementMap.get(element); 
    return node->data;
}

template <typename ValueType, typename KeyType, typename HashFunc>
bool DisjointSet<ValueType, KeyType, HashFunc>::unite(const KeyType& element1, const KeyType& element2) {
    if (!elementMap.contains(element1) || !elementMap.contains(element2) || connected(element1, element2)) {
        return false;
    }

    auto node1 = elementMap.get(element1);
    auto node2 = elementMap.get(element2);
    upTree.unite(node1, node2);
    return true;
}

template <typename ValueType, typename KeyType, typename HashFunc>
bool DisjointSet<ValueType, KeyType, HashFunc>::connected(const KeyType& element1, const KeyType& element2) const {
    try
    {
        auto node1 = elementMap.get(element1);
        auto node2 = elementMap.get(element2);
        auto root1 = upTree.findExternal(node1);
        auto root2 = upTree.findExternal(node2);
    return root1 == root2;
    }
    catch(const std::out_of_range& e)
    {
        std::cerr << e.what() << '\n';
        return false;
    }
    return false; // Should not reach here
}

template <typename ValueType, typename KeyType, typename HashFunc>
int DisjointSet<ValueType, KeyType, HashFunc>::getSize(const KeyType& element) const {
    try{
        auto node = elementMap.get(element);
        return upTree.findExternal(node)->size;
    }
    catch(const std::out_of_range& e)
    {
        throw std::invalid_argument("Element not found in the disjoint set.");
    }
    return -1; // Should not reach here
    
    
}

template <typename ValueType, typename KeyType, typename HashFunc>
int DisjointSet<ValueType, KeyType, HashFunc>::getRank(const KeyType& element) const {
    try{
        auto node = elementMap.get(element);
        return upTree.getRank(node);
    }
    catch(const std::out_of_range& e)
    {
        throw std::invalid_argument("Element not found in the disjoint set.");
    }
    return -1; // Should not reach here
}

template <typename ValueType, typename KeyType, typename HashFunc>
int DisjointSet<ValueType, KeyType, HashFunc>::getRootRank(const KeyType& element) const {
    try{
        auto node = elementMap.get(element);
        return upTree.getRootRank(node);
    }
    catch(const std::out_of_range& e)
    {
        throw std::invalid_argument("Element not found in the disjoint set.");
    }
    return -1; // Should not reach here
}




#endif // DISJOINTSET_H
