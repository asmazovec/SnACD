#ifndef QUEUE_HPP_
#define QUEUE_HPP_

#include "list.hpp"
#include <iostream>

namespace ads {
    template <typename T>
    class queue {
        private:
            list<T> qlist;

        public:
            queue &enQueue (T data);
            T deQueue();
            T top() const;
            T end() const;
            bool isEmpty() const;
    };


    template <typename T>
    queue<T> &queue<T>::enQueue (T data) {
        qlist.pushBack(data);
        return *this;
    }

    template <typename T>
    T queue<T>::deQueue () {
        return qlist.pop(0);
    }

    template <typename T>
    T queue<T>::top() const {
        return qlist[0];
    }

    template <typename T>
    T queue<T>::end() const {
        return qlist[qlist.len() - 1];
    }

    template <typename T>
    bool queue<T>::isEmpty() const {
        return qlist.isEmpty();
    }
}


#endif /* QUEUE_HPP_ */
