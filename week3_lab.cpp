#include <iostream>
#include <cmath>
#include <ctime>
using namespace std;

class Array {
private:
    int* arr;
    int size;
    int capacity;

    int single = 0;
    int doublee = 0;  

public:
    Array() {
        this->capacity = 10;
        this->size = 0;
        this->arr = new int[this->capacity];
    }
    
    Array(int capacity) {
        this->capacity = capacity;  
        this->size = 0;
        this->arr = new int[this->capacity];
    }

    //inserting a single element
    void insert_single(int val) {
        if (size >= capacity) {
            int newCapacity = capacity * 2;
            int* newArr = new int[newCapacity];
            for (int i = 0; i < size; i++) {
                newArr[i] = arr[i];
                single++;
            }
            delete[] arr;
            arr = newArr;
            capacity = newCapacity;
        }
        arr[size++] = val;
    }

    //using the single insert method
    void insert_single(int* vals, int size) {
        for (int i = 0; i < size; i++) {
            insert_single(vals[i]);
        }
    }

    //inserting a single element with doubling capacity
    void insert_double(int val) {
        if (size >= capacity) {
            int newCapacity = capacity * 2;
            int* newArr = new int[newCapacity];
            for (int i = 0; i < size; i++) {
                newArr[i] = arr[i];
                doublee++;  
            }
            delete[] arr;
            arr = newArr;
            capacity = newCapacity;
        }
        arr[size++] = val;
    }

    void insert_double(int* vals, int size) {
        for (int i = 0; i < size; i++) {
            insert_double(vals[i]);
        }
    }

    int getSingleCopyCount() {
        return single;
    }

    int getDoubleCopyCount() {
        return doublee;
    }
};

//hanoi tower function
void hanoiTower(int n, char source, char aux, char dest) {
    if (n == 1) {
        cout << "Move disk 1 from pole " << source << " to pole " << dest << endl;
        return;
    }
    hanoiTower(n - 1, source, dest, aux);
    cout << "Move disk " << n << " from pole " << source << " to pole " << dest << endl;
    hanoiTower(n - 1, aux, source, dest);
}

int main() {
    cout << "Hanoi Tower Solution for 3 disks:" << endl;
    hanoiTower(3, 'A', 'B', 'C');

    const int data_size = 10000;
    int data[data_size];
    for (int i = 0; i < data_size; i++) {
        data[i] = i;
    }

    Array single_array;
    Array double_array(data_size);

    //measuring the time for inserting 10000 elements 100 times
    for (int i = 0; i < 100; i++) {
        clock_t start, stop;

        start = clock();
        single_array.insert_single(data, data_size);
        stop = clock();
        cout << "Single_Copy - Run_" << i + 1 << " : " << (stop - start) << " ms" << endl;

        start = clock();
        double_array.insert_double(data, data_size);
        stop = clock();
        cout << "Double_Copy - Run_" << i + 1 << " : " << (stop - start) << " ms" << endl;
    }

    //mean and standard deviation
    float single_times[100], double_times[100];
    for (int i = 0; i < 100; i++) {
        single_times[i] = 0.0f;
        double_times[i] = 0.0f;
    }

    for (int i = 0; i < 100; i++) {
        clock_t start, stop;

        start = clock();
        single_array.insert_single(data, data_size);
        stop = clock();
        single_times[i] = float(stop - start)/CLOCKS_PER_SEC;

        start = clock();
        double_array.insert_double(data, data_size);
        stop = clock();
        double_times[i] = float(stop - start)/CLOCKS_PER_SEC;
    }

    float single_sum = 0.0f, double_sum = 0.0f;
    for (int i = 0; i < 100; i++) {
        single_sum += single_times[i];
        double_sum += double_times[i];
    }

    float single_mean = single_sum / 100.0f;
    float double_mean = double_sum / 100.0f;

    float singleCopyStdDev = 0.0f, doubleCopyStdDev = 0.0f;
    for (int i = 0; i < 100; i++) {
        singleCopyStdDev += pow(single_times[i] - single_mean, 2);
        doubleCopyStdDev += pow(double_times[i] - double_mean, 2);
    }

    singleCopyStdDev = sqrt(singleCopyStdDev / 100.0f);
    doubleCopyStdDev = sqrt(doubleCopyStdDev / 100.0f);

    cout << "Mean (Single): " << single_mean << " seconds" << endl;
    cout << "Standard Deviation (Single): " << singleCopyStdDev << " seconds" << endl;

    cout << "Mean (Double): " << double_mean << " seconds" << endl;
    cout << "Standard Deviation (Double): " << doubleCopyStdDev << " seconds" << endl;

    cout << "Total no. of single copies: " << single_array.getSingleCopyCount() << endl;
    cout << "Total no. of double copies: " << double_array.getDoubleCopyCount() << endl;

    return 0;
}
