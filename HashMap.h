#ifndef HASHMAPLINKEDLISTS_HASHMAP_H
#define HASHMAPLINKEDLISTS_HASHMAP_H

#include <vector>
#include <string>
#include <list>

class hashMap {
private:
    // Variables
    int numVals;
    std::vector<std::list<std::vector<int>>> storage;

    // Helper Functions
    bool isPrime(int num);
    int nextPrime(int num);
    int getIndex(int key);

public:
    // Constructors
    hashMap();
    hashMap(int cap);

    // Altering Storage
    void put(int key, int val);
    int remove(int key);
    void clear();

    // Useful Methods
    bool contains(int key);
    void resize_table(int newCap);
    std::string to_string();

    // Get Methods
    double get_load_factor();
    int get_size();
    int get_empty_buckets();
    std::vector<std::vector<int>> get_table();
    int get(int key);
};

#endif //HASHMAPLINKEDLISTS_HASHMAP_H