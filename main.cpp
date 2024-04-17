#include <iostream>

#include "HashMap.h"
#include <iostream>
#include <cassert>
#include <vector>
using namespace std;

void test_add_remove() {
    for (int i = 0; i < 1; i++) {
        vector<int> values;
        vector<int> keys;
        for (int j = 0; j < 7; j++) {
            int value = rand() % 20000 + 1;
            int key = rand() % 20000 + 1;
            values.push_back(value);
            keys.push_back(key);
        }

//        vector<vector<int>> keyValue = {keys, values};
//        cout << "Keys: " << endl;
//        for (int i = 0; i < keyValue[0].size(); i++) {
//            cout << keyValue[0][i] << ", ";
//        }
//        cout << endl << "Values: " << endl;
//        for (int i = 0; i < keyValue[0].size(); i++) {
//            cout << keyValue[1][i] << ",";
//        }

        cout << values.size() << endl;
        hashMap map;
        vector<int> actual_sizes = {1, 2, 3, 4, 5, 6, 7};
        vector<double> actual_load_factors = {1.0/2.0, 2.0/2.0, 3.0/5.0, 4.0/5.0, 5.0/5.0, 6.0/11.0, 7.0/11.0};
        vector<int> actual_empty_buckets = {1, 0, 2, 1, 0, 5, 4};
        for (int index = 0; index < values.size(); index++) {
            map.put(keys[index], values[index]);
            int size = map.get_size();
            double load_factor = map.get_load_factor();
            int empty_buckets = map.get_empty_buckets();
            cout << "current size: " << size << ", ";
            cout << "load factor: " << load_factor << endl;
            cout << "expected load factor: " << actual_load_factors[index] << endl;
            assert(size == actual_sizes[index]);
            assert(load_factor == actual_load_factors[index]);
            //assert(empty_buckets == actual_empty_buckets[index]);
        }

        for (int index = 0; index < values.size(); index++) {
            if (index % 3 == 0) {
                values[index] = rand() % 20000 + 1;
                map.put(keys[index], values[index]);
            }
        }

        for (int index = 0; index < values.size(); index++) {
            int getNum = map.get(keys[index]);
            cout << "Get: " << getNum << endl;
            assert(getNum == values[index]);
        }

        vector<vector<int>> table = map.get_table();
        cout << "Get Table: " << endl;
        for (int index = 0; index < table.size(); index++) {
            cout << table[index][0] << ", " << table[index][1] << endl;
        }
        cout << "----------------" << endl;

        for (int index = values.size()-2; index >= 0; index--) {
            map.remove(keys[index]);
            cout << map.get_load_factor() << endl;
            assert(map.get_size() == actual_sizes[index]);
        }
    }
}

int main() {
    test_add_remove();
    hashMap map;
    map.put(10, 39);
    map.put(17, 27);
}