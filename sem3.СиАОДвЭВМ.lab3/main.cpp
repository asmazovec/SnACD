#include "list.hpp"
#include <iostream>
#include <fstream>
#include <stdexcept>

using namespace ads;


void task() {
    list<int> inputL;

    /* чтение списка из файлов */
    int i;
    std::fstream file;  

    file.open("I");     
    while (file >> i)
        inputL.pushBack (i);
    file.close();

    std::cout << inputL << std::endl;

    int n = inputL.len();
    long S = 0;
    if (n) S = 1;

    int xi0, xi1;
    for (int i = 0; i < n; i++) {
        xi0 = inputL[i];
        xi1 = inputL[n - i - 1];
        std::cout << xi0*xi0 - xi1*xi1 << std::endl;
        S *= xi0*xi0 - xi1*xi1;
    }

    std::cout << S << std::endl;
    return ;
}


int main() {
    try {
        task();
    } catch (std::exception &exception) {
        std::cerr << "Standard exception: " << exception.what() << std::endl;
    } catch (...) {
		std::cerr << "Undetermined exception" << std::endl;
    }
    return 0;
}
