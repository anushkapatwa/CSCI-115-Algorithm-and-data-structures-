#include <iostream>

class Array {
private:
    int *arr;
    int size;
    int capacity;

public:
//constructor 
    Array(int c) {
        capacity = c;
        arr = new int[capacity];
        size = 0;
    }

//destructor
    ~Array() {
        delete[] arr;
    }

//Insert at the beginning
    void insert_at_beginning(int a) {
        if (size < capacity) {
            for (int i = size; i > 0; i--) {
                arr[i] = arr[i - 1];
            }
            arr[0] = a;
            size++;
        }
    }

//Insert at the end
    void insert_at_end(int a) {
        arr[size] = a;
        ++size;
    }

//Insert at the correct position in a sorted array
    void insert_at_position(int a, int b) {
        if (b >= 0 && b <= size && size < capacity) {
            for (int i = size; i > b; i--) {
                arr[i] = arr[i - 1];
            }
            arr[b] = a;
            size++;
        }
    }

//Count the number of elements that have the value x
    int no_of_elements(int x) {
        int count = 0;
        for (int i = 0; i < size; i++) {
            if (arr[i] == x) {
                ++count;
            }
        }
        return count;
    }

//Delete at the beginning
    void delete_at_beginning() {
        for (int i = 0; i < size - 1; ++i) {
            arr[i] = arr[i + 1];
        }
        --size;
    }

//Delete at the end
    void delete_at_end() {
        --size;
    }
    
//Delete the element at position i
    void delete_at_position(int b) {
        if (b >= 0 && b < size) {
            for (int i = b; i < size - 1; i++) {
                arr[i] = arr[i + 1];
            }
            size--;
        }
    }

//Delete the element with value x
    void delete_element(int x) {
        for (int i = 0; i < size; i++) {
            if (arr[i] == x) {
                delete_at_position(i);
                i--;
            }
        }
    }

//Binary Search iterative version
    void binary_search_iterative(int c) {
        int l = 0;
        int r = size - 1;
        while (l <= r) {
            int mid = l + (r - l) / 2;
            if (arr[mid] == c) {
                std::cout << "Element is found at the index: " << mid << std::endl;
                return;
            } else if (arr[mid] < c) {
                l = mid + 1;
            } else {
                r = mid - 1;
            }
        }
        std::cout << "Element is not found" << std::endl;
    }

//Binary Search recursive version
    void binary_search_recursive(int c, int l, int r) {
        if (l <= r) {
            int mid = l + (r - l) / 2;
            if (arr[mid] == c) {
                std::cout << "Element is found at the index: " << mid << std::endl;
                return;
            } else if (arr[mid] < c) {
                binary_search_recursive(c, mid + 1, r);
            } else {
                binary_search_recursive(c, l, mid - 1);
            }
        } else {
            std::cout << "Element is not found" << std::endl;
        }
    }

    int getSize() const {
        return size;
    }

    int& operator[](int index) {
        return arr[index];
    }
};

int main() {
    Array arr(10);

    arr.insert_at_end(2);
    arr.insert_at_end(7);
    arr.insert_at_beginning(9);
    arr.insert_at_position(5, 1);

    std::cout << "Elements in the Array: ";
    for (int i = 0; i < arr.getSize(); i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;

    std::cout << "Count no. of elements with given value: " << arr.no_of_elements(6) << std::endl;

    arr.delete_at_position(3);
    arr.delete_element(8);

    arr.binary_search_iterative(2);
    arr.binary_search_recursive(6, 0, arr.getSize() - 1);

    return 0;
}
