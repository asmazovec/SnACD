#ifndef TREE_HPP
#define TREE_HPP

#include <iostream>
#include <stdexcept>
#include <iomanip>

namespace ads {
    template <typename T>
    class tree {
        private:
            T data;
            tree* left;
            tree* right;
            tree* parent;
            tree* insert(tree* node);
            
        public:
           tree(T data);
            ~tree();

            T get_data() const;
            bool is_empty() const;
            tree* find(T data);
            void dir_order() const; // direct order
            void rev_order() const; // reverse order
            void sym_order() const; // symmetric order
            tree* insert(T data);
            tree& remove(T data);
            void print();
            tree* next();
            tree* prev();
            tree* min();
            tree* max();
    };

    template <typename T>
    tree<T>* tree<T>::min() {
        if (left)
            return left->min();
        return this;
    }
    
    template <typename T>
    tree<T>* tree<T>::max() {
        if (right)
            return right->max();
        return this;
    }

    template <typename T>
    tree<T>* tree<T>::next() {
        if (right)
            return right->min();

        tree<T>* tmp = this;
        while (tmp && tmp->parent && tmp == tmp->parent->right) 
            tmp = tmp->parent;

        return tmp->parent;
    }
    
    template <typename T>
    tree<T>* tree<T>::prev() {
        if (left)
            return left->max();

        tree<T>* tmp = this;
        while (tmp && tmp->parent && tmp == tmp->parent->left)
            tmp = tmp->parent;

        return tmp->parent;
    }
    
    template <typename T>
    tree<T>::tree(T data)
    : data(data), left(nullptr), right(nullptr), parent(nullptr) {}

    template <typename T>
    tree<T>::~tree() {
        if (left)
            delete left;
        if (right)
            delete right;
    }

    template <typename T>
    T tree<T>::get_data() const {
        return this->data;
    }

    template <typename T>
    bool tree<T>::is_empty() const {
        return !(left || right);
    }

    template <typename T>
    tree<T>* tree<T>::find(T data) {
        if (data == this->data)
            return this;
        if (left && data < this->data)
            return left->find(data);
        if (right && data >= this->data)
            return right->find(data);
        return nullptr;
    }

    template <typename T>
    void tree<T>::dir_order() const {
        std::cout << data << " ";
        if (left)
            left->dir_order();
        if (right)
            right->dir_order();
    }

    template <typename T>
    void tree<T>::rev_order() const {
        if (left)
            left->rev_order();
        if (right)
            right->rev_order();
        std::cout << data << " ";
    }
    
    template <typename T>
    void tree<T>::sym_order() const {
        if (left)
            left->sym_order();
        std::cout << data << " ";
        if (right)
            right->sym_order();
    }

    template <typename T>
    tree<T>* tree<T>::insert(T data) {
        if (data < this->data) {
            if (left)
                left->insert(data);
            else {
                left = new tree<T> (data);
                left->parent = this;
            }
        } else {
            if (right)
                right->insert(data);
            else {
                right = new tree<T> (data);
                right->parent = this;
            }
        }
        return this;
    }

    template <typename T>
    tree<T>* tree<T>::insert(tree<T>* node) {
        if (node->data < this->data) {
            if (left)
                left->insert(node);
            else {
                left = node;
                node->parent = this->parent;
            }
        } else {
            if (right)
                right->insert(node);
            else {
                right = node;
                node->parent = this->parent;
            }
        }
        return this;
    }

    template <typename T>
    tree<T>& tree<T>::remove(T data) {
        if (tree<T>* node = find(data)) {
            if (node->left && node->right) {
                tree<T>* min = node->right->min();
                node->data = min->data;
                node->right->remove(min->data);
            } else if (node->right) {
                tree<T>* tmp = node->right;
                node->left = tmp->left;
                node->right = tmp->right;
                node->data = tmp->data;
                tmp->left = nullptr;
                tmp->right = nullptr;
                delete tmp;
            } else if (node->left) {
                tree<T>* tmp = node->left;
                node->left = tmp->left;
                node->right = tmp->right;
                node->data = tmp->data;
                tmp->left = nullptr;
                tmp->right = nullptr;
                delete tmp;
            } else {
                node->data = 0;
                if (node->parent) {
                    if (node == node->parent->left)
                        node->parent->left = nullptr;
                    if (node == node->parent->right)
                        node->parent->right = nullptr;
                    delete node;
                }
            }
        }
        return *this;
    }

    template <typename T>
    void tree<T>::print() {
        static int h = 0;
        if (parent)
            std::cout << "-"  << "\x1b[1;36m[" << std::setfill('.') << std::setw(4) << data << "]" << "\x1b[0m" ;
        else 
            std::cout << " " << "\x1b[1;36m[" << std::setfill('.') << std::setw(4) << data << "]" << "\x1b[0m" ;
        if (right) {
            h ++;
            right->print();
            h --;
        }
        if (left) {
            std::cout << std::endl;
            tree<T>* tmp = this;
            while (tmp->parent) 
                tmp = tmp->parent;
            while (tmp != this) {
                if (tmp->data < this->data) {
                    if (tmp->left)
                        std::cout << "    |  ";
                    else
                        std::cout << "       ";
                    tmp = tmp->right;
                } else {
                    std::cout << "       ";
                    tmp = tmp->left;
                }
            }
            std::cout << "    `--";
            h ++;
            left->print();
            h --;
        }
    }
}

#endif
