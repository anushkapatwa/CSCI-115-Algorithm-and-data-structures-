#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;

void swap(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}

//case 1 (Arrays with random values)
void random_array(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        arr[i] = rand() % 10000;
    }
}

//case 2 (Arrays with sorted values)
void sorted_array(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        arr[i] = i;
    }
}

//case 3 (Arrays with 90% sorted values; permute 10% of the elements, select randomly 10% of elements and swap these elements)
void partially_sorted_array(int arr[], int size) {
    sorted_array(arr, size);
    int n = size / 10;
    for (int i = 0; i < n; i++) {
        int x1 = rand() % size;
        int x2 = rand() % size;
        swap(arr[x1], arr[x2]);
    }
}

//case 4 (Arrays with 50% sorted elements)
void half_sorted_array(int arr[], int size) {
    int half = size / 2;
    sorted_array(arr, half);
    random_array(arr + half, half);
}

//selection sort
void selection_sort(int arr[], int size) {
    for (int i = 0; i < size - 1; i++) {
        int min = i;
        for (int j = i + 1; j < size; j++) {
            if (arr[j] < arr[min]) {
                min = j;
            }
        }
        swap(arr[i], arr[min]);
    }
}

//insertion sort
void insertion_sort(int arr[], int size) {
    for (int i = 1; i < size; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
} 

//bubble sort
void bubble_sort(int arr[], int size) {
    for (int i = 0; i < size - 1; i++) {
        bool swapped = false;
        for (int j = 0; j < size - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }
        if (!swapped) {
            break;
        }
    }
    sorted_array(arr, size);
}

int main() {
    clock_t time;
    int sizes[] = {100, 1000, 10000, 100000};

    for (int size : sizes) {
        cout << endl << "Input Size: " << size << endl;
        int* arr = new int[size];

        random_array(arr, size);
        sorted_array(arr, size);
        partially_sorted_array(arr, size);
        half_sorted_array(arr, size);
        
        time = clock();
        bubble_sort(arr,size);
        time = clock() - time;
        cout << fixed << "Bubble Sort: " << (float)time/CLOCKS_PER_SEC << " seconds" << endl;

        time = clock();
        selection_sort(arr,size);
        time = clock() - time;
        cout << fixed << "Selection Sort: " << (float)time/CLOCKS_PER_SEC << " seconds" << endl;

        time = clock();
        insertion_sort(arr,size);
        time = clock() - time;
        cout << fixed << "Insertion Sort: " << (float)time/CLOCKS_PER_SEC << " seconds" << endl;

        delete[] arr;
    }

    return 0;

}