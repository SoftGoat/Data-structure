#include <iostream>
#include <cassert>
#include "HashTable.h"
#include "DisjointSet.h"
#include <memory>

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
        return 0; // For simplicity, assume rank is always 0 for this basic example
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

    try {
        hashTable.get(10);
        assert(false);
    } catch (const std::out_of_range& e) {
        std::cout << "Exception caught for non-existent key: " << e.what() << std::endl;
    }

    assert(hashTable.insert(1, "one"));
    assert(hashTable.get(1) == "one");

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
}

void testMakeSet() {
  DisjointSet<std::shared_ptr<Element>> ds;

    auto element1 = std::make_shared<Element>(1);
    auto element2 = std::make_shared<Element>(2);

    // Normal case
    ds.makeSet(element1);
    ds.makeSet(element2);

    assert(ds.find(1)->get_key() == 1);
    assert(ds.find(2)->get_key() == 2);

    // Edge case: Adding an element with the same key again
    try {
        ds.makeSet(element1); // Should throw an exception
        assert(false);
    } catch (const std::invalid_argument&) {
        std::cout << "Exception caught for duplicate makeSet." << std::endl;
    }

    // Edge case: Very large element id
    auto elementLarge = std::make_shared<Element>(1000000);
    ds.makeSet(elementLarge);
    assert(ds.find(1000000)->get_key() == 1000000);

    std::cout << "testMakeSet passed." << std::endl;
}
void testFind() {
    DisjointSet<std::shared_ptr<Element>> ds;

    auto element1 = std::make_shared<Element>(1);
    auto element2 = std::make_shared<Element>(2);
    auto element3 = std::make_shared<Element>(3);
    auto element4 = std::make_shared<Element>(4);

    ds.makeSet(element1);
    ds.makeSet(element2);
    ds.makeSet(element3);
    ds.makeSet(element4);

    // Union and find
    ds.unite(1, 2);
    assert(ds.find(1)->get_key() == ds.find(2)->get_key());

    ds.unite(2, 3);
    assert(ds.find(1)->get_key() == ds.find(3)->get_key());

    // Edge case: Union of the same element with itself
    ds.unite(1, 1);
    assert(ds.connected(1, 1)); // Should always be true

    // Edge case: Union elements that are already connected
    ds.unite(1, 3); // Already connected, should not change anything
    assert(ds.connected(1, 3));

    // Edge case: Union of a large number of elements
    for (int i = 5; i <= 1000; ++i) {
        auto element = std::make_shared<Element>(i);
        ds.makeSet(element);
        ds.unite(1, i);
    }
    for (int i = 5; i <= 1000; ++i) {
        assert(ds.find(i)->get_key() == ds.find(1)->get_key());
    }

    // Edge case: Union on non-existent elements
    try {
        ds.unite(1001, 1002); // Should throw an exception
        assert(false);
    } catch (const std::invalid_argument&) {
        std::cout << "Exception caught for union of non-existent elements." << std::endl;
    }

    std::cout << "testUnion passed." << std::endl;
}

void testUnion() {
    DisjointSet<std::shared_ptr<Element>> ds;

    auto element1 = std::make_shared<Element>(1);
    auto element2 = std::make_shared<Element>(2);
    auto element3 = std::make_shared<Element>(3);

    ds.makeSet(element1);
    ds.makeSet(element2);
    ds.makeSet(element3);

    ds.unite(1, 2);
    assert(ds.find(1)->get_key() == ds.find(2)->get_key());

    ds.unite(2, 3);
    assert(ds.find(1)->get_key() == ds.find(3)->get_key());

    std::cout << "testUnion passed." << std::endl;
}

void testConnected() {
    DisjointSet<std::shared_ptr<Element>> ds;

    auto element1 = std::make_shared<Element>(1);
    auto element2 = std::make_shared<Element>(2);
    auto element3 = std::make_shared<Element>(3);

    ds.makeSet(element1);
    ds.makeSet(element2);
    ds.makeSet(element3);

    assert(!ds.connected(1, 2));
    assert(!ds.connected(2, 3));
    assert(!ds.connected(1, 3));

    ds.unite(1, 2);
    assert(ds.connected(1, 2));
    assert(!ds.connected(2, 3));

    ds.unite(2, 3);
    assert(ds.connected(1, 3));

    std::cout << "testConnected passed." << std::endl;
}

void testGetSizeAndRank() {
    DisjointSet<std::shared_ptr<Element>> ds;

    auto element1 = std::make_shared<Element>(1);
    auto element2 = std::make_shared<Element>(2);
    auto element3 = std::make_shared<Element>(3);

    ds.makeSet(element1);
    ds.makeSet(element2);
    ds.makeSet(element3);

    assert(ds.getSize(1) == 1);
    assert(ds.getSize(2) == 1);
    assert(ds.getSize(3) == 1);

    ds.unite(1, 2);
    assert(ds.getSize(1) == 2);
    assert(ds.getSize(2) == 2);

    ds.unite(2, 3);
    assert(ds.getSize(3) == 3);

    assert(ds.getRank(1) == 1);
    assert(ds.getRank(2) == 2);
    assert(ds.getRank(3) == 3);

    std::cout << "testGetSizeAndRank passed." << std::endl;
}

void testEdgeCases() {
    DisjointSet<std::shared_ptr<Element>> ds;

    try {
        ds.find(1);
        assert(false);
    } catch (const std::invalid_argument&) {
        assert(true);
    }

    try {
        ds.unite(1, 2);
        assert(false);
    } catch (const std::invalid_argument&) {
        assert(true);
    }

    auto element1 = std::make_shared<Element>(1);
    ds.makeSet(element1);
    ds.unite(1, 1);
    assert(ds.connected(1, 1));

    std::cout << "testEdgeCases passed." << std::endl;
}

} // namespace TestDisjointSet
