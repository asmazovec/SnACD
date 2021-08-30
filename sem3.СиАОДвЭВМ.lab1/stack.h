#ifndef STACK_H_
#define STACK_H_


class stack {
    private:
        int m_size;   // Размер стека
        int *m_stack; // Массив стека
        int m_index;  // Внутренний указатель на вершину стека

    public:
        stack(int size = 1);
        ~stack();
        stack &push(int i);
        int pop();
        int top();
        bool isEmpty();
        bool isFull();
};


#endif /* STACK_H_ */
