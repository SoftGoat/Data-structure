#ifndef DYNAMICARRAY_H
#define DYNAMICARRAY_H

#include <cstddef>   // For size_t
#include <stdexcept> // For std::out_of_range

/**
 * @brief A dynamic array class that automatically resizes as needed.
 * 
 * This class provides functionality similar to `std::vector`,
 * allowing for dynamic resizing, element access, and management.
 */
template <typename T>
class DynamicArray {
private:
    T* data;             ///< Pointer to the array data
    size_t capacity;     ///< Current capacity of the array
    size_t size;         ///< Number of elements in the array

    /**
     * @brief Doubles the capacity of the array.
     * 
     * This function allocates a new array with double the capacity,
     * copies existing elements to the new array, and deallocates
     * the old array.
     */
    void resize();

    /**
     * @brief Returns the closest prime number greater than n.
     * 
     * @param n The number to find the closest prime greater than.
     * @return The closest prime number greater than n.
     */
    int closestPrime(int n);

public:
    /**
     * @brief Constructs a new DynamicArray object with an initial capacity.
     * 
     * @param initialCapacity The initial capacity of the array (default is 2).
     */
    DynamicArray(size_t initialCapacity = 101);

    /**
     * @brief Destroys the DynamicArray object.
     * 
     * Frees the allocated memory to prevent memory leaks.
     */
    ~DynamicArray();

    /**
     * @brief Adds an element to the dynamic array.
     * 
     * @param element The element to add to the array.
     */
    void add(T element);

    /**
     * @brief Accesses the element at a given index.
     * 
     * @param index The index of the element to access.
     * @return The element at the specified index.
     * @throws std::out_of_range if the index is out of bounds.
     */
    T get(size_t index) const;

    /**
     * @brief Returns the number of elements in the array.
     * 
     * @return The number of elements currently in the array.
     */
    size_t getSize() const;

    /**
     * @brief Returns the current capacity of the array.
     * 
     * @return The current capacity of the array.
     */
    size_t getCapacity() const;

    /**
     * @brief Removes the last element from the array.
     * 
     * @throws std::out_of_range if the array is empty.
     */
    void removeLast();

    // Prevent copying
    DynamicArray(const DynamicArray&) = delete;
    DynamicArray& operator=(const DynamicArray&) = delete;

    // Allow moving
    DynamicArray(DynamicArray&& other) noexcept;
    DynamicArray& operator=(DynamicArray&& other) noexcept;
};

// Implementation of DynamicArray

// Constructor
template <typename T>
DynamicArray<T>::DynamicArray(size_t initialCapacity) 
    : capacity(initialCapacity), size(0) {
    data = new T[capacity];
}

// Destructor
template <typename T>
DynamicArray<T>::~DynamicArray() {
    delete[] data;
}

template <typename T>
int DynamicArray<T>::closestPrime(int n) {
        int i, j;
        for (i = n + 1; ; i++) {
            for (j = 2; j < math.sqrt(i); j++) {
                if (i % j == 0) {
                    break;
                }
            }
            if (j == i) {
                return i;
            }
        }
};

// Resize the array by doubling its capacity
template <typename T>
void DynamicArray<T>::resize() {
    capacity = closestPrime(capacity * 2);  // Double the capacity
    T* newData = new T[capacity];  // Allocate new array

    // Copy existing elements to the new array
    for (size_t i = 0; i < size; ++i) {
        newData[i] = data[i];
    }

    // Delete old array and point to new array
    delete[] data;
    data = newData;
}

// Add an element to the dynamic array
template <typename T>
void DynamicArray<T>::add(T element) {
    if (size == capacity) {
        resize();  // Resize if the array is full
    }
    data[size++] = element;  // Add element and increase size
}

// Access element at a given index
template <typename T>
T DynamicArray<T>::get(size_t index) const {
    if (index >= size) {
        throw std::out_of_range("Index out of range");
    }
    return data[index];
}

// Return the number of elements in the array
template <typename T>
size_t DynamicArray<T>::getSize() const {
    return size;
}

// Return the current capacity of the array
template <typename T>
size_t DynamicArray<T>::getCapacity() const {
    return capacity;
}

// Remove the last element from the array
template <typename T>
void DynamicArray<T>::removeLast() {
    if (size > 0) {
        --size;  // Decrease size to remove the last element
    } else {
        throw std::out_of_range("Array is empty");
    }
}

// Move constructor
template <typename T>
DynamicArray<T>::DynamicArray(DynamicArray&& other) noexcept
    : data(other.data), capacity(other.capacity), size(other.size) {
    other.data = nullptr;
    other.capacity = 0;
    other.size = 0;
}

// Move assignment operator
template <typename T>
DynamicArray<T>& DynamicArray<T>::operator=(DynamicArray&& other) noexcept {
    if (this != &other) {
        delete[] data; // Release current resources

        data = other.data;
        capacity = other.capacity;
        size = other.size;

        other.data = nullptr;
        other.capacity = 0;
        other.size = 0;
    }
    return *this;
}

#endif // DYNAMICARRAY_H
