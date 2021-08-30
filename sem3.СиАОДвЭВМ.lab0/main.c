#include <stdio.h>

/* 3.
 * Входной файл содержит 15 целых чисел. 
 * Программа должна считать файл и выполнить операцию умножения. 
 * Выходной файл должен содержать одно число – результат умножения.
 *
 * Пример:
 * Входной файл: 2 2 2 2 … 2
 * Выходной файл: 32768
 * */
int main () {
    FILE* input  = fopen ("input", "r");
    FILE* output = fopen ("output", "w"); 
    if (ferror (input))  perror ("Произошла ошибка: ");

    int newnum;
    int multip = 1;

    while (EOF != fscanf (input, "%d", &newnum))
        multip *= newnum;

    fprintf (output, "%d\n", multip);

    fclose (input);
    fclose (output);

    return 0;
}
