#include <iostream>
#include "DisjointSet.h"

int main() {
    // Create a disjoint set for integers with initial capacity of 10
    DisjointSet<int> ds(10);

    // Add elements to the disjoint set
    ds.makeSet(1);
    ds.makeSet(2);
    ds.makeSet(3);
    ds.makeSet(4);

    // Unite some sets
    ds.unite(1, 2);
    ds.unite(3, 4);

    // Check if elements are connected
    std::cout << "1 and 2 connected? " << (ds.connected(1, 2) ? "Yes" : "No") << std::endl;
    std::cout << "1 and 3 connected? " << (ds.connected(1, 3) ? "Yes" : "No") << std::endl;

    // Unite all elements into a single set
    ds.unite(2, 3);

    // Check connections again
    std::cout << "1 and 3 connected after union? " << (ds.connected(1, 3) ? "Yes" : "No") << std::endl;

    return 0;
}
