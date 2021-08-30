#include "queue.hpp"
#include <iostream>
#include <fstream>
#include <stdexcept>

using namespace ads;


int task() {
    queue<float> X;
    queue<float> Y;

    /* чтение очередей из файлов */
    float x, y;         
    std::fstream file;  

    file.open("X");     
    while (file >> x)
        X.enQueue (x);
    file.close();

    file.open("Y");
    while (file >> y)
        Y.enQueue (y);
    file.close();

    int iter = 0;
    /* вычисление */
    while (!X.isEmpty() && !Y.isEmpty()) {
        if (X.top() < Y.top()) 
            X.enQueue (X.deQueue() + Y.deQueue()); 
        else 
            Y.enQueue (X.deQueue() - Y.deQueue());
        iter++;
    }
    return iter;
}


int main() {
    try {
        std::cout << task() << std::endl;
    } catch (std::exception &exception) {
        std::cerr << "Standard exception: " << exception.what() << std::endl;
    } catch (...) {
		std::cerr << "Undetermined exception" << std::endl;
    }
    return 0;
}
