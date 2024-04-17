#include "HashMap.h"
#include <string>
#include <vector>
#include <list>
#include <cmath>
using namespace std;

// Initializes hashMap with size 5
hashMap::hashMap() {
    this->storage.resize(2);
    this->numVals= 0;
}

// Initializes hashMap with given size
hashMap::hashMap(int cap) {
    this->storage.resize(cap);
    this->numVals = 0;
}

void hashMap::put(int key, int val) {
    int keyIndex = this->getIndex(key);

    if (this->get_load_factor() >= 1) {
        this->resize_table(2 * this->storage.size());
    }
    // Checking if key already exists
    if (keyIndex != -1) {
        auto listIterator = this->storage[keyIndex].begin();

        while (listIterator != this->storage[keyIndex].end()) {
            if ((*listIterator)[0] == key) {
                (*listIterator)[1] = val;
            }
            listIterator++;
        }
    }

    // Adding a new value to storage
    else {
        int keyHash = hash<int>{}(key) % this->storage.size();
        this->storage[keyHash].push_back({key, val});
        this->numVals++;
    }
}

int hashMap::remove(int key) {
    int val = this->get(key);

    // If the key is not in storage
    if (val == -1) {
        return -1;
    }

    // Key is in storage
    int keyHash = hash<int>{}(key) % this->storage.size();
    this->storage[keyHash].remove({key, val});
    this->numVals--;
    return val;
}

// Clears storage
void hashMap::clear() {
    int storageSize = this->storage.size();
    this->storage.clear();
    this->storage.resize(storageSize);
    this->numVals = 0;
}

// Returns true if the given key is in storage
bool hashMap::contains(int key) {
    if (this->getIndex(key) == -1) {
        return false;
    }
    return true;
}

// Keeps values, but resizes table to newCap
void hashMap::resize_table(int newCap) {
    if (newCap <= this->storage.size()) {
        return;
    }
    else if (!this->isPrime(newCap)) {
        newCap = this->nextPrime(newCap);
    }

    vector<vector<int>> vals = this->get_table();
    this->clear();
    this->storage.resize(newCap);

    for (int i = 0; i < vals.size(); i++) {
        this->put(vals[i][0], vals[i][1]);
    }
}

// Returns a string of the keys and values in storage
string hashMap::to_string() {
    string keyValues;
    vector<vector<int>> table = this->get_table();

    for (int i = 0; i < table.size(); i++) {
        keyValues += "{" + ::to_string(table[i][0]) + ", " + ::to_string(table[i][1]) + "} ";
    }
    return keyValues;
}

// Returns proportion of storage currently filled
double hashMap::get_load_factor() {
    return (double) this->numVals / (double) this->storage.size();
}

// Returns size of storage
int hashMap::get_size() {
    return this->numVals;
}

// Returns number of blank spaces in storage
int hashMap::get_empty_buckets() {
    int count = 0;
    for (int i=0; i<this->storage.size(); i++) {
        if (this->storage[i].empty()) {
            count++;
        }
    }
    return count;
}

// Returns a vector of each pair in storage
// Pairs are ordered as {key, value}
vector<vector<int>> hashMap::get_table() {
    vector<vector<int>> returnVect;
    for (int i = 0; i < this->storage.size(); i++) {
        auto currentInt = this->storage[i].begin();
        while (currentInt != this->storage[i].end()) {
            returnVect.push_back(*currentInt);
            currentInt++;
        }
    }
    return returnVect;
}

// Returns the value at the given key
int hashMap::get(int key) {
    int keyIndex = this->getIndex(key);
    if (keyIndex == -1) {
        return -1;
    }

    auto listIterator = this->storage[keyIndex].begin();
    while (listIterator != this->storage[keyIndex].end()) {
        if ((*listIterator)[0] == key) {
            return (*listIterator)[1];
        }
        listIterator++;
    }
}

bool hashMap::isPrime(int num) {
    // If the number is a small prime number
    if ((num == 2) || (num == 3)) {
        return true;
    }
        // If the number is 1 or an even number
    else if ((num == 1) || (num%2 == 0)) {
        return false;
    }

    // Checks for if val is divisible by any number other than 1 < val
    int val = ceil(sqrt(num));
    for (int i=2; i<=val; i++) {
        if (num%i == 0) {
            return false;
        }
    }
    return true;
}

// Returns the closest higher prime number
int hashMap::nextPrime(int num) {
    if (num%2 == 0) {
        num++;
    }
    while (!isPrime(num)) {
        num += 2;
    }
    return num;
}

int hashMap::getIndex(int key) {
    int keyHash = hash<int>{}(key) % this->storage.size();
    auto listIterator = this->storage[keyHash].begin();

    while (listIterator != this->storage[keyHash].end()) {
        if ((*listIterator)[0] == key) {
            return keyHash;
        }
        listIterator++;
    }
    return -1;
}