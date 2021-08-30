/* 8. 
 * Используя стек, решить следующую задачу. 
 * В текстовом файле F записана без ошибок формула следующего вида: 
 *      <формула> ::= <цифра> | М(<формула>, <формула>) | m(<формула>, <формула>) 
 *      <цифра>   ::= 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9
 *      М функция max
 *      m функция min
 *
 * Вычислить как целое число значение данной формулы. Например, М(M(4,5),m(6,M(8,3))). 
 * Для реализации АТД Стек использовать массив. 
 * 
 * */

#include "stack.h"
#include <iostream>
#include <cstdio>


int m(int a, int b) {
    return (a >= b)? b: a;
}

int M(int a, int b) {
    return (a >= b)? a: b;
}


int calculate(const char *filePath) {
    stack args(100);
    FILE *expr = fopen(filePath, "r");
    fseek(expr, -2, SEEK_END);
    char c;
    long pos  = ftell(expr);
    do {
        c = (char)fgetc(expr);
        fseek(expr, -2, SEEK_CUR);
        pos--;
        if(!(c == ')' || c == '(' || c == ',' || c == ' ')) {
            if(c >= '0' && c <= '9') {
                args.push(c - '0');
            } else if(c == 'M') {
                args.push(M(args.pop(), args.pop()));
            } else if(c == 'm') {
                args.push(m(args.pop(), args.pop()));
            }
        }
    } while(pos+1);

    return args.pop();
}


int main() {
    std::cout << calculate("F") << std::endl;
    return 0;
}


