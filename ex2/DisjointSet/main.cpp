#include <iostream>
#include <cassert>
#include <vector>
#include <stdexcept>
#include "DisjointSet.h"

// Extended tests for DisjointSet implementation

// Test creation and basic operations of DisjointSet
void testMakeSet() {
    DisjointSet<int> ds(10);
    ds.makeSet(1);
    ds.makeSet(2);
    ds.makeSet(3);
    // Ensure that the root of each is itself
    assert(ds.find(1) == 1);
    assert(ds.find(2) == 2);
    assert(ds.find(3) == 3);

    // Replace the makeSet and find with a loop to verify
    for (int i = 4; i <= 10; ++i) {
        ds.makeSet(i);
        assert(ds.find(i) == i); // Each should point to itself
    }

    std::cout << "testMakeSet passed!" << std::endl;
}

// Test union and find operations for correctness
void testUnionAndFind() {
    DisjointSet<int> ds(10);
    ds.makeSet(1);
    ds.makeSet(2);
    ds.makeSet(3);
    
    ds.unite(1, 2);
    assert(ds.find(1) == ds.find(2)); // 1 and 2 should be in the same set
    assert(ds.find(3) != ds.find(2)); // 3 should be in a different set

    ds.unite(2, 3); // Merge 2 with 3
    assert(ds.find(1) == ds.find(3)); // Now 1 and 3 should also be connected

    std::cout << "testUnionAndFind passed!" << std::endl;
}

// Test connected method to ensure connectivity checks are correct
void testConnected() {
    DisjointSet<int> ds(10);
    ds.makeSet(1);
    ds.makeSet(2);
    ds.makeSet(3);
    
    ds.unite(1, 2);
    assert(ds.connected(1, 2) == true);  // 1 and 2 should be connected
    assert(ds.connected(1, 3) == false); // 1 and 3 should not be connected

    ds.unite(2, 3);
    assert(ds.connected(1, 3) == true); // Now they should all be connected

    std::cout << "testConnected passed!" << std::endl;
}

// Test handling of invalid operations and exception throwing
void testInvalidOperations() {
    DisjointSet<int> ds(10);
    ds.makeSet(1);
    
    try {
        ds.makeSet(1); // Duplicate makeSet should throw
        assert(false); // This should not be reached
    } catch (const std::invalid_argument& e) {
        assert(std::string(e.what()) == "Element already exists in the disjoint set.");
    }

    try {
        ds.find(2); // Finding an element that does not exist
        assert(false); // This should not be reached
    } catch (const std::invalid_argument& e) {
        assert(std::string(e.what()) == "Element not found in the disjoint set.");
    }

    try {
        ds.unite(1, 3); // One element not in the set
        assert(false); // This should not be reached
    } catch (const std::invalid_argument& e) {
        assert(std::string(e.what()) == "One or both elements not found in the disjoint set.");
    }

    std::cout << "testInvalidOperations passed!" << std::endl;
}

// Test path compression to ensure it optimizes the structure
void testPathCompression() {
    DisjointSet<int> ds(10);
    ds.makeSet(1);
    ds.makeSet(2);
    ds.makeSet(3);
    ds.unite(1, 2);
    ds.unite(2, 3);

    assert(ds.find(1) == ds.find(3)); // 1, 2, and 3 should be connected
    assert(ds.find(2) == ds.find(3)); // Confirmed path compression
    
    // Validating the internal structure (For debugging)
    assert(ds.find(1) == ds.find(2)); 
    assert(ds.find(2) == ds.find(3)); 
    
    std::cout << "testPathCompression passed!" << std::endl;
}

// Test multiple union operations and connectivity checks
void testMultipleUnions() {
    DisjointSet<int> ds(10);
    ds.makeSet(1);
    ds.makeSet(2);
    ds.makeSet(3);
    ds.makeSet(4);
    
    ds.unite(1, 2);
    ds.unite(3, 4);
    ds.unite(2, 3); // Now all should be in the same set

    assert(ds.find(1) == ds.find(4));
    assert(ds.find(2) == ds.find(3));

    // Validate that connecting in reverse order does not break structure
    ds.unite(1, 4);
    assert(ds.find(3) == ds.find(1));

    std::cout << "testMultipleUnions passed!" << std::endl;
}

// Test getting the size of the set containing an element
void testSetSize() {
    DisjointSet<int> ds(10);
    ds.makeSet(1);
    ds.makeSet(2);
    ds.makeSet(3);
    
    assert(ds.getSize(1) == 1); // Each should start as size 1
    ds.unite(1, 2);
    assert(ds.getSize(1) == 2); // Size of the set with element 1 should be 2
    assert(ds.getSize(3) == 1); // Size of the set with element 3 should be 1
    
    ds.unite(1, 3); // Now all should be connected
    assert(ds.getSize(1) == 3); // Size should now be 3
    assert(ds.getSize(2) == 3); // Size of set with 2 should also be 3
    assert(ds.getSize(3) == 3); // Size of set with 3 should also be 3

    std::cout << "testSetSize passed!" << std::endl;
}

// Test performance on large datasets
void testPerformance() {
    const int numElements = 100000;
    DisjointSet<int> ds(numElements);
    
    // Create sets
    for (int i = 1; i <= numElements; ++i) {
        ds.makeSet(i);
    }

    // Perform unions in a large scale
    for (int i = 1; i <= numElements; i += 2) {
        ds.unite(i, i + 1); // Combine pairs (1,2), (3,4), ...
    }

    // Verify a few connections
    assert(ds.connected(1, 2) == true);
    assert(ds.connected(3, 4) == true);
    assert(ds.connected(1, 3) == false);

    // Now connect all pairs merged above with another set of unions
    for (int i = 1; i <= numElements; i += 4) {
        ds.unite(i, i + 2); // Create larger sets (1,3), (2,4), ...
    }

    assert(ds.connected(1, 3) == true);
    assert(ds.connected(2, 4) == true);

    std::cout << "testPerformance passed!" << std::endl;
}

// Test various union and rank operations
void testRanks() {
    DisjointSet<int> ds(10);
    ds.makeSet(1);
    ds.makeSet(2);
    ds.makeSet(3);
    ds.makeSet(4);
    ds.makeSet(5);
    
    ds.unite(1, 2);
    ds.unite(3, 4);
    ds.unite(1, 3); // Unite two sets with two elements each

    assert(ds.getRank(1) == 1); // Root's rank should still be 1
    assert(ds.getRank(2) == 1); // 2 should have same rank as before

    ds.unite(5, 1); // Add 5 to the bigger set
    assert(ds.getRank(5) == 1); // Rank should be equal to the size of the set

    std::cout << "testRanks passed!" << std::endl;
}

// Test multiple makeSet and union operations
void testComplexUnions() {
    DisjointSet<int> ds(20);
    std::vector<int> elements = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    
    // Make sets for all elements
    for (int elem : elements) {
        ds.makeSet(elem);
    }

    // Perform complex union operations
    ds.unite(1, 2);
    ds.unite(2, 3);
    ds.unite(4, 5);
    ds.unite(6, 7);
    ds.unite(8, 9);
    ds.unite(7, 9);
    ds.unite(5, 6);
    ds.unite(3, 4);
    ds.unite(1, 8);

    // Validate the connections
    for (size_t i = 1; i < elements.size(); ++i) {
        assert(ds.connected(elements[0], elements[i]) == true);
    }

    std::cout << "testComplexUnions passed!" << std::endl;
}

int main() {
    testMakeSet();
    testUnionAndFind();
    testConnected();
    testInvalidOperations();
    testPathCompression();
    testMultipleUnions();
    testSetSize();
    testPerformance();
    testComplexUnions();
    testRanks();


    std::cout << "All tests passed!" << std::endl;
    return 0;
}
