#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <string>
#include <functional>
using namespace std;

const int TableSize = 10007;  // prime number for table size

class HashTable {
public:
    HashTable(int size) : table_size(size), table(size) {}

    void insert(const string& key) {
        int index = hash(key);
        table[index].push_back(key);
    }

    int getMaxListLength() {
        int max_length = 0;
        for (const auto& list : table) {
            max_length = max(max_length, static_cast<int>(list.size()));
        }
        return max_length;
    }

    double getAverageListLength() {
        int total_length = 0;
        for (const auto& list : table) {
            total_length += list.size();
        }
        return static_cast<double>(total_length) / table_size;
    }

private:
    int table_size;
    vector<list<string>> table;

    int hash(const string& key) {
        hash<string> hasher;
        return hasher(key) % table_size;
    }
};

int main() {
    ifstream dictionary_file("Oxford English Dictionary.txt");
    if (!dictionary_file) {
        cerr << "Error: Unable to open the dictionary file." << endl;
        return 1;
    }

    HashTable hashTable(TableSize);

    string word;
    while (dictionary_file >> word) {
        if (word.length() > 4 && word.length() < 10) {
            hashTable.insert(word);
        }
    }

    dictionary_file.close();

    int maxListLength = hashTable.getMaxListLength();
    double averageListLength = hashTable.getAverageListLength();

    cout << "Maximum length of a list in the hash table: " << maxListLength << endl;
    cout << "Average length of the lists in the hash table: " << averageListLength << endl;

    return 0;
}
