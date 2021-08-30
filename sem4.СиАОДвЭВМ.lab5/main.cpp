#include "HashTable.hpp"
#include <fstream>
#include <iostream>

using namespace ads;

void task() {
    hash h (10);

    /* чтение списка из файлов */
    int key;
    int value;

    std::fstream file;  

    file.open("I");     
    while (file >> key && file >> value)
        h.insert(entry (key, value));

    file.close();

    std::cout << h << std::endl;

    entry* f;
    int i;
    std::cin >> i;
    int iter = 0;
    f = h.find(i, &iter);
    if (f)
        std::cout << "Find   " << i << " Just " << *f  << "  Iterations " << iter << std::endl;
    else std::cout << "Find   " << i << " Nothing" << "  Iterations " << iter << std::endl;
    h.remove (i, &iter);
    return ;
}

int main () {
    task();
    return 0;
}
