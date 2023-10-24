#include <iostream>
#include <unordered_map>
#include <stack>
using namespace std;

class Node {
public:
    int data;
    Node* next;
    Node(int val) : data(val), next(nullptr) {}
};

void insert(Node** head, int x) {
    Node* newNode = new Node(x);
    newNode->next = *head;
    *head = newNode;
}

//function that returns a list l containing the unique values
Node* unique_values(int arr[], int n) {
    unordered_map<int, bool> seen;
    Node* head = nullptr;
    
    for (int i = n - 1; i >= 0; i--) {
        if (!seen[arr[i]]) {
            seen[arr[i]] = true;
            insert(&head, arr[i]);
        }
    }
    
    return head;
}

//function that return a list l containing the occurrence of each element
Node* occurrence_list(int arr[], int n) {
    unordered_map<int, int> countMap;
    Node* head = nullptr;
    
    for (int i = 0; i < n; i++) {
        countMap[arr[i]]++;
    }
    
    for (auto& entry : countMap) {
        insert(&head, entry.first);
    }
    
    return head;
}

//sorted list that returns all the elements from an array that are above a given element x
Node* sorted_list(int arr[], int n, int x) {
    Node* head = nullptr;
    
    for (int i = 0; i < n; i++) {
        if (arr[i] > x) {
            insert(&head, arr[i]);
        }
    }
    
    return head;
}

//stack class using a list
class Stack {
private:
    Node* top;

public:
    Stack() : top(nullptr) {}

    void Push(int x) {
        insert(&top, x);
    }

    void Pop() {
        if (top != nullptr) {
            Node* temp = top;
            top = top->next;
            delete temp;
        }
    }

    int Top() {
        if (top != nullptr) {
            return top->data;
        }
        return -1; 
    }

    bool IsEmpty() {
        return top == nullptr;
    }
};

int main() {
    int arr[] = {0, 1, 0, 2, 3, 0, 1};
    int n = sizeof(arr) / sizeof(arr[0]);

    //ques 1
    Node* unique = unique_values(arr, n);
    cout << "Unique values list: ";
    while (unique != nullptr) {
        cout << unique->data << " ";
        unique = unique->next;
    }
    cout << endl;

    //ques 2
    Node* occurrence = occurrence_list(arr, n);
    cout << "Occurrence list: ";
    while (occurrence != nullptr) {
        cout << occurrence->data << " ";
        occurrence = occurrence->next;
    }
    cout << endl;

    //ques 3
    int x = 5;
    Node* sorted_above_x = sorted_list(arr, n, x);
    cout << "Sorted list above " << x << ": ";
    Node* current = sorted_above_x;  
    while (current != nullptr) {
        cout << current->data << " ";
        current = current->next; 
    }
    cout << endl;

    //ques 4
    Stack myStack;
    myStack.Push(1);
    myStack.Push(2);
    myStack.Push(3);

    cout << "Stack top: " << myStack.Top() << endl;
    myStack.Pop();
    cout << "Stack top after pop: " << myStack.Top() << endl;

    return 0;
}
