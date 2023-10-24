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

//merge sort
void merge(int arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int l[n1], r[n2];

    for (int i = 0; i < n1; i++)
        l[i] = arr[left + i];
    for (int i = 0; i < n2; i++)
        r[i] = arr[mid + 1 + i];

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2) {
        if (l[i] <= r[j]) {
            arr[k] = l[i];
            i++;
        } else {
            arr[k] = r[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = l[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = r[j];
        j++;
        k++;
    }
}

void merge_sort(int arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        merge_sort(arr, left, mid);
        merge_sort(arr, mid + 1, right);

        merge(arr, left, mid, right);
    }
}

//quick sort
int quick(int arr[], int low, int high) {
    int n = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < n) {
            i++;
            swap(arr[i], arr[j]);
        }
    }

    swap(arr[i + 1], arr[high]);
    return (i + 1);
}

void quick_sort(int arr[], int low, int high) {
    if (low < high) {
        int p = quick(arr, low, high);

        quick_sort(arr, low, p - 1);
        quick_sort(arr, p + 1, high);
    }
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
        merge_sort(arr, 0, size - 1);
        time = clock() - time;
        cout << fixed << "Merge Sort: " << (float)time/CLOCKS_PER_SEC << " seconds" << endl;

        time = clock();
        quick_sort(arr, 0, size - 1);
        time = clock() - time;
        cout << fixed << "Quick Sort: " << (float)time/CLOCKS_PER_SEC << " seconds" << endl;

        delete[] arr;
    }

    return 0;

}