#ifndef list_HPP_
#define list_HPP_

#include <iostream>
#include <stdexcept>

namespace ads {
    template <typename T>
    class _node;

    template <typename T>
    class list;

    template <typename T> 
    std::ostream& operator<< (std::ostream& o, const _node<T> &n);

    template <typename T> 
    std::ostream& operator<< (std::ostream& o, const list<T> &l);


    template <typename T>
    class _node {
        public:
            T field;
            _node *next;

            _node (T data = 0);
            _node (const _node &) = delete;
            _node (_node &&n);
            _node &operator= (const _node &) = delete;
            _node &operator= (_node &&n);
            _node &operator= (T data);

            friend std::ostream& operator<< <> (std::ostream& o, const _node<T> &n);
    };


    template <typename T>
    class list {
        private:
            mutable _node<T> node;
            _node<T> &getNode (int index) const;

        public:
            list();
            ~list();
            T &operator[] (int index);
            T operator[] (int index) const;

            list &push (T data, int index);
            list &pushStart (T data);
            list &pushBack (T data);
            T pop (int index);
            int len() const;
            bool isEmpty() const;

            friend std::ostream& operator<< <> (std::ostream& o, const list<T> &l);
    };



    template <typename T>
    _node<T>::_node (T data): field (data), next(nullptr) {}

    template <typename T>
    _node<T>::_node (_node &&n) 
        :field (n.field), next (n.next) {
        std::cout << "move clone node " << std::endl;
        n.next = nullptr;
    }

    template <typename T>
    _node<T> &_node<T>::operator= (_node<T> &&n) {
        std::cout << "move operator= node " << std::endl;
        if (&n == this) 
            return *this;

        field = n.field;
        next = n.next;
        n.next = nullptr;
        return *this;
    }

    template <typename T>
    _node<T> &_node<T>::operator= (T data) {
        field = data;
        return *this;
    }

    template <typename T> 
    std::ostream& operator<< (std::ostream& o, const _node<T> &n) {
        o << n.field;
        return o;
    }



    template <typename T>
    list<T>::list(): node (_node<T>()) {}

    template <typename T>
    list<T>::~list() {
        _node<T> *cur = node.next;
        _node<T> *next;
        while (cur) {
            next = cur->next;
            delete cur;
            cur = next;
        }
    }

    template <typename T>
    _node<T> &list<T>::getNode (int index) const {
        if (++index < 0)
            throw std::invalid_argument ("Invalid list index.");
        _node<T> *cur = &node;
        for (int i = 0; i < index; i++)
            if (cur->next)
                cur = cur->next;
            else
                throw std::out_of_range ("Index is out of range.");
        return *cur;
    }

    template <typename T>
    T &list<T>::operator[] (int index) {
        if (index < 0)
            throw std::invalid_argument ("Invalid list index.");
        if (isEmpty())
            throw std::out_of_range ("List is empty.");
        _node<T> *n = &getNode (index);
        return n->field;
    }

    template <typename T>
    T list<T>::operator[] (int index) const {
        if (index < 0)
            throw std::invalid_argument ("Invalid list index.");
        if (isEmpty())
            throw std::out_of_range ("List is empty.");
        _node<T> *n = &getNode (index);
        return n->field;
    }

    template <typename T>
    list<T> &list<T>::push (T data, int index) {
        if (index < 0)
            throw std::invalid_argument ("Invalid list index.");
        _node<T> *n = &getNode (index - 1);
        _node<T> *cur = new _node<T> (data);
        cur->next = n->next;
        n->next = cur;
        return *this;
    }

    template <typename T>
    list<T> &list<T>::pushStart (T data) {
        push (data, 0);
        return *this;
    }

    template <typename T>
    list<T> &list<T>::pushBack (T data) {
        push (data, len());
        return *this;
    }

    template <typename T>
    T list<T>::pop (int index) {
        if (index < 0)
            throw std::invalid_argument ("Invalid list index.");
        if (isEmpty())
            throw std::out_of_range ("List is empty.");
        _node<T> *n = &getNode (index - 1);
        int data = n->next->field;
        _node<T> *next = n->next->next;
        n->next->next = nullptr;
        delete n->next;
        n->next = next;
        return data;
    }

    template <typename T>
    int list<T>::len() const {
        _node<T> *cur = &node;
        int len = 0;
        while (cur->next) {
            cur = cur->next;
            len++;
        }
        return len;
    }

    template <typename T>
    bool list<T>::isEmpty() const {
        return !node.next;
    }

    template <typename T> 
    std::ostream& operator<< (std::ostream& o, const list<T> &l) {
        _node<T> *cur = &l.node;
        while (cur->next) {
            cur = cur->next;
            o << *cur << " ";
        }
        return o;
    }
}


#endif /* list_HPP_ */
