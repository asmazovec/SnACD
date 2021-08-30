#include <iostream>
#include <ctime>
#include <fstream>
#include "tree.hpp"

using namespace ads;
void task (tree<int> &t) {
    t.print();
    std::cout << std::endl << std::endl;

    int A;
    std::cout << "Enter min diapazon" << std::endl;
    std::cin >> A;
    int B = A - 1;
    std::cout << "Enter max diapazon" << std::endl;
    while (B < A) {
        std::cin >> B;
        if (B < A)
            std::cout << "    Should be bigger than min. Try again" << std::endl;
    }
    std::cout << std::endl; 

    int count = 0;

    tree<int>* tmp = &t;
    while (tmp->get_data() >= A)  // начало слева
        if (tmp->prev())
            tmp = tmp->prev();
        else
            break;
    while (tmp->get_data() < A)  // начало справа
        if (tmp->next())
            tmp = tmp->next();
        else 
            break;

    std::cout << "symmetric: ";
    t.sym_order();
    std::cout << std::endl;
    std::cout << "current  : ";
    if (tmp->get_data() < A || tmp->get_data() > B) {
    } else {
        while (tmp && tmp->get_data() <= B) {
            std::cout << tmp->get_data() << " ";
            tmp = tmp->next();
            count++;
        }
    }
    std::cout << std::endl;
    std::cout << "count    : " << count << std::endl;
}

void settings() {
    srand (std::time(0));

    int mode;
    std::cout << "0 - manual\n1 - random\n2 - file" << std::endl;
    do {
        std::cin >> mode;
        if (mode != 0 && mode != 1 && mode != 2) 
            std::cout << "    Enter 0, 1 or 2 to continue" << std::endl;
    } while (mode != 0 && mode != 1 && mode != 2);
    std::cout << std::endl;

    if (mode == 0) {
        std::cout << "Enter size of tree" << std::endl;
        int tsize = 0;
        while (tsize <= 0) {
            std::cin >> tsize;
            if (tsize <= 0)
                std::cout << "    Should be positive. Try again" << std::endl;
        }
        std::cout << std::endl;

        int data;
        std::cout << "Enter nodes # one string - one node" << std::endl;
        std::cin >> data;
        tree<int> b(data);
        for (int i = 0; i < tsize-1; i++) {
            std::cin >> data;
            b.insert(data);
        }
        task (b);
    } else if (mode == 1) {
        int min;

        std::cout << "Enter size of tree" << std::endl;
        int tsize = 0;
        while (tsize <= 0) {
            std::cin >> tsize;
            if (tsize <= 0)
                std::cout << "    Should be positive. Try again" << std::endl;
        }
        std::cout << std::endl;

        std::cout << "Enter min possible random" << std::endl;
        std::cin >> min;
        int max = min - 1;
        std::cout << "Enter max possible random" << std::endl;
        while (max < min) {
            std::cin >> max;
            if (max < min)
                std::cout << "    Should be bigger than min. Try again" << std::endl;
        }
        std::cout << std::endl; 

        tree<int> t(std::rand() % (max - min + 1) + min);
        for (int i = 0; i < tsize-1; i++)
            t.insert(std::rand() % (max - min + 1) + min);
        task (t);
    } else {
        int i;
        std::fstream file;
        char path[255];
        std::cout << "Enter file path" << std::endl;
        std::cin >> path;
        file.open(path);     
        file >> i;
        tree<int> t(i);
        while (file >> i)
            t.insert (i);
        file.close();
        task (t);
    }
}

int main() {
    settings ();
    return 0;
}
