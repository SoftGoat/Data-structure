#include <iostream>
#include <cassert>
#include "HashTable.h"
#include "DisjointSet.h"
#include <memory>
#include <vector>

// Forward declarations of test functions
void runAllTests();

namespace TestHashTable {
    void run();
    void testInsert();
    void testRemove();
    void testDuplicateHandling();
    void testGetNonExistentKey();
    void testCollisionResolution();
    void testResizeFunctionality();
    void testContains();
    void testGet();
    void testResize();
    void testEdgeCases();
}

namespace TestDisjointSet {
    void run();
    void testMakeSet();
    void testFind();
    void testUnion();
    void testConnected();
    void testGetSizeAndRank();
    void testEdgeCases();
    void stressTestDisjointSet();
}

namespace TestUpTree
{
    void run();
    void testFind();
    void testUnite();
    void testConnected();
    void testGetRank();
    void testEdgeCases();
    void stressTestUpTree();
    
}


// Custom class for testing DisjointSet
class Element {
public:
    int id;
    Element(int id) : id(id) {}

    int get_key() const {
        return id;
    }

    int get_rank() const {
        return 1; // For simplicity, assume rank is always 1 for this basic example
    }
};

int main() {
    std::cout << "Running all tests..." << std::endl;
    runAllTests();
    std::cout << "All tests passed!" << std::endl;
    return 0;
}

void runAllTests() {
    TestHashTable::run();
    TestDisjointSet::run();
    TestUpTree::run(); 


}

// Implementation of HashTable tests
namespace TestHashTable {

void run() {
    std::cout << "Running HashTable tests..." << std::endl;
    testInsert();
    testRemove();
    testDuplicateHandling();
    testGetNonExistentKey();
    testCollisionResolution();
    testResizeFunctionality();
    testContains();
    testGet();
    testResize();
    testEdgeCases();
}

void testInsert() {
    HashTable<int, std::string> hashTable(5, IntHash(), 0.5f);

    assert(hashTable.insert(1, "one"));
    assert(hashTable.insert(6, "six"));
    assert(hashTable.insert(11, "eleven"));
    assert(hashTable.insert(16, "sixteen"));

    assert(hashTable.contains(1));
    assert(hashTable.contains(6));
    assert(hashTable.contains(11));
    assert(hashTable.contains(16));

    assert(!hashTable.insert(1, "one again")); // Duplicate key

    assert(hashTable.get(1) == "one");
    assert(hashTable.get(6) == "six");
    assert(hashTable.get(11) == "eleven");
    assert(hashTable.get(16) == "sixteen");

    std::cout << "testInsert passed." << std::endl;
}

void testRemove() {
    HashTable<int, std::string> table;
    table.insert(1, "one");
    table.insert(2, "two");

    assert(table.remove(1));
    assert(!table.contains(1));
    assert(table.contains(2));
    assert(!table.remove(1));

    std::cout << "testRemove passed." << std::endl;
}

void testDuplicateHandling() {
    HashTable<int, std::string> hashTable(5, IntHash(), 0.5f);

    assert(hashTable.insert(1, "one"));
    assert(hashTable.insert(2, "two"));
    
    assert(!hashTable.insert(1, "one again")); // Duplicate key
    assert(!hashTable.insert(2, "two again"));

    assert(hashTable.get(1) == "one");
    assert(hashTable.get(2) == "two");

    std::cout << "testDuplicateHandling passed." << std::endl;
}

void testGetNonExistentKey() {
    HashTable<int, std::string> hashTable(5, IntHash(), 0.5f);

    // Case 1: Attempt to get a key from an empty hash table
    try {
        hashTable.get(10);
        assert(false); // Should not reach this line
    } catch (const std::out_of_range& e) {
        std::cout << "Exception caught for non-existent key in empty table: " << e.what() << std::endl;
    }

    // Insert some elements
    assert(hashTable.insert(1, "one"));
    assert(hashTable.insert(2, "two"));
    assert(hashTable.insert(3, "three"));

    // Case 2: Attempt to get a key that was never inserted
    try {
        hashTable.get(4); // Key 4 has not been inserted
        assert(false); // Should not reach this line
    } catch (const std::out_of_range& e) {
        std::cout << "Exception caught for non-existent key: " << e.what() << std::endl;
    }

    // Case 3: Remove an element and then attempt to get it
    assert(hashTable.remove(2)); // Remove key 2
    try {
        hashTable.get(2); // Key 2 has been removed
        assert(false); // Should not reach this line
    } catch (const std::out_of_range& e) {
        std::cout << "Exception caught for removed key: " << e.what() << std::endl;
    }

    // Case 4: Attempt to get a key after resizing
    assert(hashTable.insert(5, "five"));
    assert(hashTable.insert(6, "six"));
    assert(hashTable.insert(7, "seven"));
    assert(hashTable.insert(8, "eight")); // This should trigger resizing

    try {
        hashTable.get(9); // Key 9 has never been inserted
        assert(false); // Should not reach this line
    } catch (const std::out_of_range& e) {
        std::cout << "Exception caught for non-existent key after resizing: " << e.what() << std::endl;
    }

    // Ensure existing keys still return correct values
    assert(hashTable.get(1) == "one");
    assert(hashTable.get(3) == "three");
    assert(hashTable.get(5) == "five");
    assert(hashTable.get(6) == "six");

    std::cout << "testGetNonExistentKey passed." << std::endl;
}

void testCollisionResolution() {
    HashTable<int, std::string> hashTable(5, IntHash(), 0.5f);

    assert(hashTable.insert(1, "one"));
    assert(hashTable.insert(6, "six"));
    assert(hashTable.insert(11, "eleven"));

    assert(hashTable.contains(1));
    assert(hashTable.contains(6));
    assert(hashTable.contains(11));

    assert(hashTable.get(1) == "one");
    assert(hashTable.get(6) == "six");
    assert(hashTable.get(11) == "eleven");

    std::cout << "testCollisionResolution passed." << std::endl;
}

void testResizeFunctionality() {
    HashTable<int, std::string> hashTable(2, IntHash(), 0.5f);

    assert(hashTable.insert(1, "one"));
    assert(hashTable.insert(2, "two"));
    assert(hashTable.insert(3, "three"));

    assert(hashTable.contains(1));
    assert(hashTable.contains(2));
    assert(hashTable.contains(3));

    std::cout << "testResizeFunctionality passed." << std::endl;
}

void testContains() {
    HashTable<int, std::string> table;
    table.insert(1, "one");
    table.insert(2, "two");

    assert(table.contains(1));
    assert(table.contains(2));
    assert(!table.contains(3));

    std::cout << "testContains passed." << std::endl;
}

void testGet() {
    HashTable<int, std::string> table;
    table.insert(1, "one");
    table.insert(2, "two");

    assert(table.get(1) == "one");
    assert(table.get(2) == "two");

    try {
        table.get(3);
        assert(false);
    } catch (const std::out_of_range& e) {
        assert(true);
    }

    std::cout << "testGet passed." << std::endl;
}

void testResize() {
    HashTable<int, std::string> table(2);

    for (int i = 1; i <= 100; ++i) {
        table.insert(i, "value" + std::to_string(i));
    }

    for (int i = 1; i <= 100; ++i) {
        assert(table.contains(i));
        assert(table.get(i) == "value" + std::to_string(i));
    }

    std::cout << "testResize passed." << std::endl;
}

void testEdgeCases() {
    HashTable<int, std::string> table;

    assert(!table.contains(100));
    assert(!table.remove(100));

    table.insert(100, "hundred");
    assert(table.remove(100));
    assert(table.insert(100, "hundred again"));
    assert(table.get(100) == "hundred again");
    assert(table.remove(100));

    for (int i = 1; i <= 1000; ++i) {
        assert(table.insert(i, "value" + std::to_string(i)));
    }
    for (int i = 1; i <= 1000; ++i) {
        assert(table.remove(i));
    }
    for (int i = 1; i <= 1000; ++i) {
        assert(!table.contains(i));
    }

    std::cout << "testEdgeCases passed." << std::endl;
}

} // namespace TestHashTable

// Implementation of DisjointSet tests
namespace TestDisjointSet {

void run() {
    std::cout << "Running DisjointSet tests..." << std::endl;
    testMakeSet();
    testFind();
    testUnion();
    testConnected();
    testGetSizeAndRank();
    testEdgeCases();
    stressTestDisjointSet();
}

void testMakeSet() {
    DisjointSet<std::shared_ptr<Element>> ds;

    auto element1 = std::make_shared<Element>(1);
    auto element2 = std::make_shared<Element>(2);

    // Normal case
    assert(ds.makeSet(element1));  // Expect true
    assert(ds.makeSet(element2));  // Expect true

    assert(ds.find(1)->get_key() == 1);
    assert(ds.find(2)->get_key() == 2);

    // Edge case: Adding an element with the same key again
    assert(!ds.makeSet(element1)); // Expect false since the element is already in the set

    // Edge case: Adding nullptr
    assert(!ds.makeSet(nullptr));  // Expect false

    // Edge case: Very large element id
    auto elementLarge = std::make_shared<Element>(1000000);
    assert(ds.makeSet(elementLarge));  // Expect true
    assert(ds.find(1000000)->get_key() == 1000000);

    // Stress test: Adding a large number of elements
    for (int i = 3; i <= 10000; ++i) {
        auto element = std::make_shared<Element>(i);
        assert(ds.makeSet(element));  // Expect true
        assert(!ds.makeSet(element));  // Expect false since the element is already in the set
        assert(ds.find(i)->get_key() == i);
    }

    // Ensure earlier elements are still correct
    assert(ds.find(1)->get_key() == 1);
    assert(ds.find(1000)->get_key() == 1000);
    assert(ds.find(5000)->get_key() == 5000);
    assert(ds.find(10000)->get_key() == 10000);

    // Edge case: MakeSet for already united elements
    auto element3 = std::make_shared<Element>(3);
    auto element4 = std::make_shared<Element>(4);
    ds.makeSet(element3);
    ds.makeSet(element4);
    ds.unite(3, 4);

    assert(!ds.makeSet(element3));  // Expect false since the element is already in a set

    std::cout << "testMakeSet passed." << std::endl;
}

void testFind() {
    DisjointSet<std::shared_ptr<Element>> ds;

    auto element1 = std::make_shared<Element>(1);
    auto element2 = std::make_shared<Element>(2);
    auto element3 = std::make_shared<Element>(3);
    auto element4 = std::make_shared<Element>(4);

    assert(ds.makeSet(element1));  // Expect true
    assert(ds.makeSet(element2));  // Expect true
    assert(ds.makeSet(element3));  // Expect true
    assert(ds.makeSet(element4));  // Expect true

    // Basic union and find tests
    assert(ds.unite(1, 2));  // Expect true
    assert(ds.find(1)->get_key() == ds.find(2)->get_key());

    assert(ds.unite(2, 3));  // Expect true
    assert(ds.find(1)->get_key() == ds.find(3)->get_key());

    assert(ds.unite(3, 4));  // Expect true
    assert(ds.find(1)->get_key() == ds.find(4)->get_key());

    // Edge case: Union of the same element with itself
    assert(!ds.unite(1, 1));  // Expect false, no actual union happens
    assert(ds.connected(1, 1)); // Should always be true

    // Edge case: Union elements that are already connected
    assert(!ds.unite(1, 3)); // Expect false, already connected
    assert(ds.connected(1, 3));
    assert(ds.find(1)->get_key() == ds.find(3)->get_key());

    // Stress test: Union and find a large number of elements
    for (int i = 5; i <= 1000; ++i) {
        auto element = std::make_shared<Element>(i);
        assert(ds.makeSet(element));  // Expect true
        assert(ds.unite(1, i));  // Expect true
        assert(ds.find(i)->get_key() == ds.find(1)->get_key());
    }

    // Ensure path compression: After union, check that finds are efficient
    auto root1 = ds.find(1);
    for (int i = 5; i <= 1000; ++i) {
        assert(ds.find(i) == root1); // All should point to the same root
    }

    // Edge case: Find on non-existent element
    try {
        ds.find(1001); // Should throw an exception since 1001 wasn't added
        assert(false);
    } catch (const std::invalid_argument&) {
        std::cout << "Exception caught for find on non-existent element." << std::endl;
    }

    // Edge case: Ensure that the find operation does not alter the structure for a non-existent element
    assert(ds.find(1) == root1); // Root should remain unchanged

    std::cout << "testFind passed." << std::endl;
}

void testUnion() {
    DisjointSet<std::shared_ptr<Element>> ds;

    auto element1 = std::make_shared<Element>(1);
    auto element2 = std::make_shared<Element>(2);
    auto element3 = std::make_shared<Element>(3);
    auto element4 = std::make_shared<Element>(4);

    assert(ds.makeSet(element1));  // Expect true
    assert(ds.makeSet(element2));  // Expect true
    assert(ds.makeSet(element3));  // Expect true
    assert(ds.makeSet(element4));  // Expect true

    // Basic union and verification
    assert(ds.unite(1, 2));  // Expect true
    assert(ds.find(1)->get_key() == ds.find(2)->get_key());

    assert(ds.unite(2, 3));  // Expect true
    assert(ds.find(1)->get_key() == ds.find(3)->get_key());

    assert(ds.unite(3, 4));  // Expect true
    assert(ds.find(1)->get_key() == ds.find(4)->get_key());

    // Edge case: Union of the same element with itself
    assert(!ds.unite(1, 1));  // Expect false, no actual union happens
    assert(ds.connected(1, 1)); // Should always be true

    // Edge case: Union elements that are already connected
    assert(!ds.unite(1, 3));  // Expect false, already connected
    assert(ds.connected(1, 3));
    assert(ds.find(1)->get_key() == ds.find(3)->get_key());

    // Edge case: Union non-existent elements (should throw an exception)
    assert(!ds.unite(1, 1001));  // Expect false, 1001 doesn't exist
    assert(!ds.unite(1001, 1002));  // Expect false, 1001 and 1002 don't exist

    // Edge case: Union a large number of elements in a linear chain
    for (int i = 5; i <= 1000; ++i) {
        auto element = std::make_shared<Element>(i);
        assert(ds.makeSet(element));  // Expect true
        assert(ds.getSize(i) == 1); // Initial size should be 1
        assert(ds.unite(1, i));  // Expect true
        assert(ds.getSize(1) == i); // Size should increase by 1
    }
    for (int i = 5; i <= 1000; ++i) {
        assert(ds.find(i)->get_key() == ds.find(1)->get_key()); 
    }

    // Edge case: Union an already connected element with a new one
    auto element1001 = std::make_shared<Element>(1001);
    assert(ds.makeSet(element1001));  // Expect true
    assert(ds.unite(1001, 1000));  // Expect true
    assert(ds.find(1001)->get_key() == ds.find(1)->get_key());

    // Edge case: Ensure no disruption when uniting connected components with different ranks
    auto element1002 = std::make_shared<Element>(1002);
    assert(ds.makeSet(element1002));  // Expect true
    assert(ds.unite(1, 1002));  // Expect true
    assert(ds.find(1002)->get_key() == ds.find(1)->get_key());

    std::cout << "testUnion passed." << std::endl;
}



void testConnected() {
    DisjointSet<std::shared_ptr<Element>> ds;

    auto element1 = std::make_shared<Element>(1);
    auto element2 = std::make_shared<Element>(2);
    auto element3 = std::make_shared<Element>(3);
    auto element4 = std::make_shared<Element>(4);
    auto element5 = std::make_shared<Element>(5);

    assert(ds.makeSet(element1));
    assert(ds.makeSet(element2));
    assert(ds.makeSet(element3));
    assert(ds.makeSet(element4));
    assert(ds.makeSet(element5));

    // Initially, none of the elements should be connected
    assert(!ds.connected(1, 2));
    assert(!ds.connected(2, 3));
    assert(!ds.connected(1, 3));
    assert(!ds.connected(4, 5));
    assert(!ds.connected(1, 5));

    // Unite some elements and check connections
    assert(ds.unite(1, 2));
    assert(ds.connected(1, 2));
    assert(!ds.connected(2, 3));
    assert(!ds.connected(1, 3));

    assert(ds.unite(2, 3));
    assert(ds.connected(1, 3)); // Should now be connected through 2
    assert(!ds.connected(3, 4));

    // Unite the remaining elements
    assert(ds.unite(4, 5));
    assert(ds.connected(4, 5));
    assert(!ds.connected(3, 5));

    // Unite different sets and verify connections
    assert(ds.unite(3, 4));
    assert(ds.connected(1, 5)); // All should be connected now

    // Edge case: Check connected on the same element
    assert(ds.connected(1, 1)); // An element should always be connected to itself

    // Edge case: Check connection between elements that haven't been added
    assert(!ds.connected(100, 200)); // Should return false, as elements do not exist

    // Edge case: Large number of elements
    for (int i = 6; i <= 1000; ++i) {
        auto element = std::make_shared<Element>(i);
        assert(ds.makeSet(element)); // Adding element
        assert(!ds.connected(1, i)); // Should not be connected initially
    }

    // Connect all elements in a chain
    for (int i = 5; i < 1000; ++i) {
        assert(ds.unite(i, i + 1)); // Connect current element to the next
        assert(ds.connected(1, i + 1)); // Should all be connected to 1
    }

    // Edge case: Try to connect elements that are already connected
    assert(!ds.unite(1, 1000)); // Should return false since they are already connected

    std::cout << "testConnected passed." << std::endl;
}

void testGetSizeAndRank() {
    DisjointSet<std::shared_ptr<Element>> ds;

    auto element1 = std::make_shared<Element>(1);
    auto element2 = std::make_shared<Element>(2);
    auto element3 = std::make_shared<Element>(3);
    auto element4 = std::make_shared<Element>(4);
    auto element5 = std::make_shared<Element>(5);

    ds.makeSet(element1);
    ds.makeSet(element2);
    ds.makeSet(element3);
    ds.makeSet(element4);
    ds.makeSet(element5);

    // Initially, all sets should have size 1 and rank 0 (assuming the rank doesn't change)
    assert(ds.getSize(1) == 1);
    assert(ds.getSize(2) == 1);
    assert(ds.getSize(3) == 1);
    assert(ds.getSize(4) == 1);
    assert(ds.getSize(5) == 1);

    assert(ds.getRank(1) == 1);
    assert(ds.getRank(2) == 1);
    assert(ds.getRank(3) == 1);
    assert(ds.getRank(4) == 1);
    assert(ds.getRank(5) == 1);

    // Perform unions and check sizes and ranks
    ds.unite(1, 2);
    assert(ds.getSize(1) == 2);
    assert(ds.getSize(2) == 2);
    assert(ds.getRank(1) == 1); // Rank should adjust based on union logic
    assert(ds.getRank(2) == 2); // Rank should be the same as for 1

    ds.unite(3, 4);
    assert(ds.getSize(3) == 2);
    assert(ds.getSize(4) == 2);
    assert(ds.getRank(3) == 1);
    assert(ds.getRank(4) == 2);

    ds.unite(1, 3);
    assert(ds.getSize(1) == 4);
    assert(ds.getSize(3) == 4);
    assert(ds.getRank(1) == 1); // Rank should reflect the merged set's size
    assert(ds.getRank(3) == 3);

    // Edge case: Union elements that are already connected
    assert(!ds.unite(1, 3)); // Should not change anything
    assert(ds.getSize(1) == 4);
    assert(ds.getRank(1) == 1);

    // Edge case: Rank should stay correct after multiple unions
    ds.unite(4, 5);
    assert(ds.getSize(5) == 5);
    printf("Rank of 5: %d\n", ds.getRank(5));
    assert(ds.getRank(5) == 5);

    // Edge case: Size and rank of an element not in the set should return errors
    try {
        ds.getSize(6); // Should throw an exception since 6 is not added
        assert(false);
    } catch (const std::invalid_argument&) {
        std::cout << "Exception caught for getSize on non-existent element." << std::endl;
    }

    try {
        ds.getRank(6); // Should throw an exception since 6 is not added
        assert(false);
    } catch (const std::invalid_argument&) {
        std::cout << "Exception caught for getRank on non-existent element." << std::endl;
    }

    // Stress test: Add and unite a large number of elements, checking size and rank
    for (int i = 6; i <= 1000; ++i) {
        auto element = std::make_shared<Element>(i);
        ds.makeSet(element);
        ds.unite(1, i);
        assert(ds.getSize(i) == i);
        assert(ds.getRank(i) == i);
    }

    std::cout << "testGetSizeAndRank passed." << std::endl;
}


void testEdgeCases() {
    DisjointSet<std::shared_ptr<Element>> ds;

    // Edge Case 1: Attempting to find an element that hasn't been added
    try {
        ds.find(1); // Element 1 does not exist
        assert(false); // Should not reach here
    } catch (const std::invalid_argument&) {
        std::cout << "Exception caught for find on non-existent element." << std::endl;
    }

    // Edge Case 2: Attempting to unite elements that haven't been added
    assert(!ds.unite(1, 2)); // Both elements do not exist

    // Edge Case 3: Attempting to add nullptr as an element
    assert(!ds.makeSet(nullptr)); // Should return false

    // Edge Case 4: Union an element with itself
    auto element1 = std::make_shared<Element>(1);
    ds.makeSet(element1);
    assert(!ds.unite(1, 1)); // Union with itself should return false
    assert(ds.connected(1, 1)); // Should always be true

    // Edge Case 5: Union the same element multiple times
    auto element2 = std::make_shared<Element>(2);
    ds.makeSet(element2);
    assert(ds.unite(1, 2)); // First union should succeed
    assert(!ds.unite(1, 2)); // Subsequent union should do nothing, returning false

    // Edge Case 6: Union elements with a large difference in key values
    auto elementLarge = std::make_shared<Element>(1000000);
    ds.makeSet(elementLarge);
    assert(ds.unite(2, 1000000)); // Should succeed

    // Edge Case 7: Union an existing element with a non-existent one
    try {
        assert(!ds.unite(1, 3)); // Element 3 does not exist, should return false
    } catch (const std::invalid_argument&) {
        std::cout << "Exception caught for union with non-existent element." << std::endl;
    }

    // Edge Case 8: Finding elements after multiple unions
    auto element3 = std::make_shared<Element>(3);
    ds.makeSet(element3);
    ds.unite(1, 3);
    assert(ds.find(3)->get_key() == ds.find(1)->get_key()); // Should point to the same root

    // Edge Case 9: Verify that non-existent elements return appropriate errors in connected
    assert(!ds.connected(1, 999999)); // Element 999999 does not exist, should return false

    // Edge Case 10: Attempt to get size or rank of a non-existent element
    try {
        ds.getSize(999999); // Should throw an exception
        assert(false);
    } catch (const std::invalid_argument&) {
        std::cout << "Exception caught for getSize on non-existent element." << std::endl;
    }

    try {
        ds.getRank(999999); // Should throw an exception
        assert(false);
    } catch (const std::invalid_argument&) {
        std::cout << "Exception caught for getRank on non-existent element." << std::endl;
    }



    std::cout << "testEdgeCases passed." << std::endl;
}
    void stressTestDisjointSet() {
    const int numElements = 10000;
    DisjointSet<std::shared_ptr<Element>> ds;

    // Step 1: Add a large number of elements
    for (int i = 1; i <= numElements; ++i) {
        auto element = std::make_shared<Element>(i);
        ds.makeSet(element);
    }

    // Step 2: Randomly unite elements and check connections
    for (int i = 1; i < numElements; i += 2) {
        int element1 = i;
        int element2 = i + 1;
        ds.unite(element1, element2);
        assert(ds.connected(element1, element2)); // Ensure they are connected
    }

    // Step 3: Further unite random pairs and check the connections
    for (int i = 1; i < numElements / 2; i += 4) {
        int element1 = i;
        int element2 = numElements - i;
        ds.unite(element1, element2);
        assert(ds.connected(element1, element2)); // Ensure they are connected
    }

    // Step 4: Check the size and rank of sets
    for (int i = 1; i <= numElements; i += 10) {
        int root = ds.find(i)->get_key();
        int size = ds.getSize(root);
        int rank = ds.getRank(root);

        // Ensure the size is consistent with the number of elements united
        assert(size >= 1 && size <= numElements);
        assert(rank >= 1 && rank <= numElements);
    }

    // Step 5: Perform random checks for connected components
    for (int i = 1; i <= numElements / 2; i++) {
        int element1 = i;
        int element2 = i + (numElements / 2);
        assert(!ds.connected(element1, element2) || ds.connected(element1, element2));
    }

    // Step 6: Verify that the find operation is consistent after multiple operations
    for (int i = 1; i <= numElements; ++i) {
        int root1 = ds.find(i)->get_key();
        int root2 = ds.find(i)->get_key();
        assert(root1 == root2); // Ensure that subsequent finds give the same root
    }

    // Step 7: Stress test the find operation with repeated calls
    for (int i = 1; i <= numElements; ++i) {
        for (int j = 0; j < 100; ++j) {
            ds.find(i);
        }
    }

    // Step 8: Verify that all operations completed without exception
    std::cout << "stressTestDisjointSet passed with " << numElements << " elements and thousands of operations." << std::endl;
}

}


namespace TestUpTree {

    void run();
    void testUnite();
    void testConnected();
    void testFind();
    void stressTestUpTree();
    void testGetRank();


    // Helper function to create nodes
    template <typename T>
    std::shared_ptr<Node<T>> createNode(T value) {
        auto node = std::make_shared<Node<T>>(value); // Pass the value to the constructor
        node->parent = nullptr; // Initially, a node is its own parent
        node->size = 1;
        node->rank = 1;
        return node;
    }


    void run() {
        std::cout << "Running UpTree tests..." << std::endl;
        testUnite();
        testConnected();
        testFind();
        stressTestUpTree();
        testGetRank();

    }

    void testUnite() {
    UpTree<int> ut;

    auto node1 = createNode(1);
    auto node2 = createNode(2);
    auto node3 = createNode(3);
    auto node4 = createNode(4);
    auto node5 = createNode(5);

    // Basic unite and connection test
    ut.unite(node1, node2);
    assert(ut.connected(node1, node2));

    ut.unite(node2, node3);
    assert(ut.connected(node1, node3));

    // Edge case: Unite the same node with itself
    ut.unite(node1, node1);
    assert(ut.connected(node1, node1)); // Should always be true

    // Edge case: Unite already connected nodes
    ut.unite(node1, node3);
    assert(ut.connected(node1, node3)); // Should not change the connection

    // Edge case: Unite disjoint sets and verify connections
    ut.unite(node4, node5);
    assert(ut.connected(node4, node5));
    assert(!ut.connected(node1, node4)); // Different sets should not be connected

    // Edge case: Connect two larger disjoint sets
    ut.unite(node3, node4);
    assert(ut.connected(node1, node5)); // All nodes should now be connected

    // Edge case: Union nodes where one has a much higher rank than the other
    auto node6 = createNode(6);
    node6->rank = 10;  // Set a higher rank for node6
    ut.unite(node5, node6);
    assert(ut.connected(node1, node6)); // All should be connected

    // Edge case: Attempt to unite nodes that have not been added to the tree
    auto node7 = std::make_shared<Node<int>>(7);
    auto node8 = std::make_shared<Node<int>>(8);
    ut.unite(node7, node8); // No effect since they are not connected to any tree
    assert(ut.connected(node7, node8)); // Should be connected but isolated

    // Edge case: Unite after a large number of operations
    for (int i = 8; i <= 100; ++i) {
        auto node = createNode(i);
        ut.unite(node6, node);
        assert(ut.connected(node1, node)); // All new nodes should be connected to the original tree
    }

    // Edge case: Ensure no disruption when reuniting nodes in the same set
    ut.unite(node3, node5);
    assert(ut.connected(node1, node5)); // Connection should remain intact

    std::cout << "testUnite passed." << std::endl;
}


void testConnected() {
    UpTree<int> ut;

    auto node1 = createNode(1);
    auto node2 = createNode(2);
    auto node3 = createNode(3);
    auto node4 = createNode(4);
    auto node5 = createNode(5);
    auto node6 = createNode(6);

    // Test basic connections
    ut.unite(node1, node2);
    ut.unite(node3, node4);

    assert(ut.connected(node1, node2));
    assert(ut.connected(node3, node4));
    assert(!ut.connected(node1, node3));

    // Test connecting multiple components
    ut.unite(node2, node3);
    assert(ut.connected(node1, node4)); // Now all should be connected

    // Edge Case: Check connection with itself
    assert(ut.connected(node1, node1));
    assert(ut.connected(node2, node2));

    // Edge Case: Non-existent nodes (not in the tree)
    auto nodeNonExistent = createNode(100);
    assert(!ut.connected(node1, nodeNonExistent));

    // Edge Case: Node that is in a different tree (simulate by creating a new tree)
    UpTree<int> ut2;
    auto node7 = createNode(7);
    auto node8 = createNode(8);
    ut2.unite(node7, node8);
    assert(!ut.connected(node1, node7));

    // Test after multiple unions
    ut.unite(node1, node5);
    ut.unite(node4, node6);
    assert(ut.connected(node5, node6));
    assert(ut.connected(node1, node6));
    assert(ut.connected(node2, node5));
    assert(!ut.connected(node5, node7)); // Different tree should still not connect

    // Edge Case: Chain of connections
    auto node9 = createNode(9);
    auto node10 = createNode(10);
    ut.unite(node9, node10);
    ut.unite(node10, node1); // Connecting to the main tree
    assert(ut.connected(node9, node6)); // Should now be connected through node10

    // Edge Case: Disconnected nodes
    auto node11 = createNode(11);
    auto node12 = createNode(12);
    assert(!ut.connected(node11, node12)); // Should not be connected as they are not united

    std::cout << "testConnected passed." << std::endl;
}



    void testFind() {
        UpTree<int> ut;

        auto node1 = createNode(1);
        auto node2 = createNode(2);
        auto node3 = createNode(3);
        auto node4 = createNode(4);
        auto node5 = createNode(5);

        // Basic case: Unite two nodes and ensure find returns the same root
        ut.unite(node1, node2);
        assert(ut.findExternal(node1) == ut.findExternal(node2));

        // Unite another pair and check find
        ut.unite(node3, node4);
        assert(ut.findExternal(node3) == ut.findExternal(node4));
        assert(ut.findExternal(node1) != ut.findExternal(node3)); // They are not connected yet

        // Edge case: Find on a node that has not been united with others
        assert(ut.findExternal(node5) == node5); // Should return itself as the root

        // Unite two groups and check the root
        ut.unite(node2, node3);
        assert(ut.findExternal(node1) == ut.findExternal(node4));

        // Edge case: Unite a node with itself and check find
        ut.unite(node1, node1);
        assert(ut.findExternal(node1) == node1);



        // Edge case: Repeated find operations to ensure path compression
        auto root = ut.findExternal(node1);
        for (int i = 0; i < 100; ++i) {
            assert(ut.findExternal(node1) == root);
        }

        // Edge case: After multiple unites, ensure all nodes point to the same root
        assert(ut.findExternal(node1) == ut.findExternal(node2));
        assert(ut.findExternal(node2) == ut.findExternal(node3));
        assert(ut.findExternal(node3) == ut.findExternal(node4));
        assert(ut.findExternal(node4) != ut.findExternal(node5)); // Different group

        // Stress test: Find on a large number of nodes
        const int numNodes = 10000;
        std::vector<std::shared_ptr<Node<int>>> nodes;
        for (int i = 6; i <= numNodes; ++i) {
            auto node = createNode(i);
            nodes.push_back(node);
            ut.unite(node1, node);
            assert(ut.findExternal(node) == ut.findExternal(node1)); // All should point to the same root
        }

        // Edge case: Find on a disconnected node after many operations
        auto nodeDisconnected = createNode(numNodes + 1);
        assert(ut.findExternal(nodeDisconnected) == nodeDisconnected); // Should return itself as the root

        std::cout << "testFind passed." << std::endl;
    }



void stressTestUpTree() {
    UpTree<int> ut;
    const int numNodes = 10000;

    std::vector<std::shared_ptr<Node<int>>> nodes;
    for (int i = 1; i <= numNodes; ++i) {
        nodes.push_back(createNode(i));
    }

    // Step 1: Randomly unite nodes and verify connections
    for (int i = 0; i < numNodes - 1; ++i) {
        ut.unite(nodes[i], nodes[i + 1]);
        assert(ut.connected(nodes[i], nodes[i + 1]));
    }

    // Step 2: Verify that all nodes are connected
    for (int i = 0; i < numNodes - 1; ++i) {
        assert(ut.connected(nodes[0], nodes[i + 1]));
    }

    // Step 3: Verify the rank and size consistency
    for (int i = 0; i < numNodes; ++i) {
        int expectedRank = ut.getRank(nodes[i]);
        assert(expectedRank >= 0); // Ensure rank is non-negative
        assert(ut.getRank(nodes[i]) == expectedRank); // Rank consistency check
    }

    // Step 4: Perform additional random unites and verify connections
    for (int i = 0; i < numNodes / 2; ++i) {
        int idx1 = rand() % numNodes;
        int idx2 = rand() % numNodes;
        ut.unite(nodes[idx1], nodes[idx2]);
        assert(ut.connected(nodes[idx1], nodes[idx2]));
    }

    // Step 5: Check if all nodes point to the same root after multiple unites
    auto root = ut.findExternal(nodes[0]);
    for (int i = 1; i < numNodes; ++i) {
        assert(ut.findExternal(nodes[i]) == root);
    }

    // Step 6: Perform stress test with findExternal to ensure path compression works
    for (int i = 0; i < numNodes; ++i) {
        for (int j = 0; j < 100; ++j) {
            assert(ut.findExternal(nodes[i]) == root); // Should all point to the same root
        }
    }

    // Step 7: Verify after stress that all nodes still point to the same root
    for (int i = 1; i < numNodes; ++i) {
        assert(ut.findExternal(nodes[i]) == root);
    }

    // Step 8: Randomly check connected status between different pairs
    for (int i = 0; i < numNodes / 10; ++i) {
        int idx1 = rand() % numNodes;
        int idx2 = rand() % numNodes;
        assert(ut.connected(nodes[idx1], nodes[idx2]));
    }

    // Step 9: Verify that the size of the up-tree is as expected
    for (int i = 0; i < numNodes; ++i) {
        assert(ut.getRank(nodes[i]) <= numNodes);
    }

    // Step 10: Edge case: Attempt to unite a node with itself
    for (int i = 0; i < numNodes; ++i) {
        ut.unite(nodes[i], nodes[i]);
        assert(ut.connected(nodes[i], nodes[i]));
    }

    std::cout << "stressTestUpTree passed with " << numNodes << " nodes and multiple operations." << std::endl;
}



    void testGetRank() {
        UpTree<int> ut;

        auto node1 = createNode(1);
        auto node2 = createNode(2);
        auto node3 = createNode(3);
        auto node4 = createNode(4);
        auto node5 = createNode(5);
        auto node6 = createNode(6);

        // Basic unite and rank checks
        ut.unite(node1, node2);
        assert(ut.getRank(node1) == 1);
        assert(ut.getRank(node2) == 2);

        ut.unite(node3, node4);
        assert(ut.getRank(node3) == 1);
        assert(ut.getRank(node4) == 2);

        // Unite all nodes together and check ranks
        ut.unite(node2, node3);
        assert(ut.getRank(node1) == 1); // Rank should reflect the combined depth
        assert(ut.getRank(node2) == 2);
        assert(ut.getRank(node3) == 3);
        assert(ut.getRank(node4) == 4);

        // Edge case: Unite nodes where one has a higher initial rank
        node5->abs_rank = 5;
        ut.unite(node4, node5);
        printf("node4 rank: %d\n", ut.getRank(node4));
        assert(ut.getRank(node4) == 9); // Rank should consider node5's higher rank
        printf("node5 rank: %d\n", ut.getRank(node5));
        assert(ut.getRank(node5) == 1);

        // Edge case: Unite an entire chain of nodes and check the ranks
        ut.unite(node1, node6);
        printf("node6 rank: %d\n", ut.getRank(node6));
        assert(ut.getRank(node6) == 10);
        assert(ut.getRank(node1) == 6); // Rank should now reflect the total depth

        // Edge case: Unite two large trees and verify rank calculations
        auto node7 = createNode(7);
        auto node8 = createNode(8);
        node7->abs_rank = 3;
        node8->abs_rank = 4;

        ut.unite(node7, node8);
        printf("node7 rank: %d\n", ut.getRank(node7));
        assert(ut.getRank(node7) == 5); // Check the ranks after union
        assert(ut.getRank(node8) == 1);

        ut.unite(node6, node7);
        assert(ut.getRank(node6) == 10); // Combined tree rank check
        assert(ut.getRank(node8) == 11);

        // Edge case: Unite nodes with equal ranks and verify rank adjustments
        auto node9 = createNode(9);
        auto node10 = createNode(10);
        node9->abs_rank = 3;
        node10->abs_rank = 3;

        ut.unite(node9, node10);
        assert(ut.getRank(node9) == 1);
        assert(ut.getRank(node10) == 4);

        // Edge case: Attempting to get the rank of a node not part of any union
        auto node11 = createNode(11);
        assert(ut.getRank(node11) == 1); // A standalone node's rank should be 1
        std::cout << "testGetRank passed." << std::endl;
    }

}


 // namespace TestDisjointSet
