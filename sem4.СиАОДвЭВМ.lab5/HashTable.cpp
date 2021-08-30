#ifndef HASH_CPP_
#define HASH_CPP_

#include <iostream>
#include <stdexcept>
#include "HashTable.hpp"
#include "list.hpp"

namespace ads {
    entry::entry (int) {}

    entry::entry (int k, int v) 
    : key (k), value (v) {}

    bool operator== (entry A, int B) {
        return A.key == B;
    }

    bool operator== (int A, entry B) {
        return A == B.key;
    }

    bool operator== (entry A, entry B) {
        return A.key == B.key;
    }

    hash::hash (int length)
    : length (length) {
        if (length < 1)
            throw std::invalid_argument ("Invalid length");
        keys = new list<entry>[length];
    }

    hash::~hash () {
        delete[] keys;
    }

    int hash::hashfunction (int key) const {
        return abs (key % length);
    }

    entry* hash::find (int key, int *iter) const {
        _node<entry> *find = keys[hashfunction(key)].find(entry (key, 0), iter);
        if (find && find->next)
            return &find->next->field;
        return nullptr;
    }

    hash& hash::insert (entry data) {
        keys[hashfunction(data.key)].pushStart(data);
        return *this;
    }

    hash& hash::remove (int key, int *iter) {
        _node<entry> *find = keys[hashfunction(key)].find(entry (key, 0), iter);
        std::cout << "Remove " << key << " ";
        if (find) {
            keys[hashfunction(key)].remove_next(find);
            std::cout << "Success deletion  ";
        } else {
            std::cout << "There is no key  ";
        }
        std::cout << "Iterations " << *iter << std::endl;
        return *this;
    }

    std::ostream& operator<< (std::ostream& o, const entry &e) {
        o << "(" << e.key << " : " << e.value << ")";
        return o;
    }

    std::ostream& operator<< (std::ostream& o, const hash &t) {
        for (int i = 0; i < t.length; i++)
            o << "[" << i << "] -> " <<  t.keys[i] << std::endl;
        return o;
    }
}

#endif /* HASH_CPP_ */
