#ifndef HASH_HPP_
#define HASH_HPP_

#include <iostream>
#include "list.hpp"

namespace ads {
    class entry {
        friend std::ostream& operator<< (std::ostream& o, const entry &e);

        friend bool operator== (entry A, int B);
        friend bool operator== (int A, entry B);

        friend bool operator== (entry A, entry B);

        public:
            int key;
            int value;

            entry (int);
            entry (int, int);
    };

    class hash {
        friend std::ostream& operator<< (std::ostream& o, const hash &t);

        private:
            int length;
            list<entry>* keys;

        public:
            hash(int length); 
            ~hash();

            int hashfunction (int key) const; 
            entry *find (int key, int *iter) const;
            hash& insert (entry data);
            hash& remove (int key, int *iter);
    };
}

#endif /* HASH_HPP_ */
