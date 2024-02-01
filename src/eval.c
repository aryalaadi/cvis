/*
	TODO: rewrite to support functions
*/
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

double eval(char *exp, double x) {
    char *ptr = exp;
    double result = 0;
    char operation = '+';
    double num = 0;

    while (*ptr != '\0') {
        if (isdigit(*ptr) || *ptr == '.') {
            num = strtod(ptr, &ptr);
            switch (operation) {
                case '+':
                    result += num;
                    break;
                case '-':
                    result -= num;
                    break;
                case '*':
                    result *= num;
                    break;
                case '/':
                    result /= num;
                    break;
            }
        } else if (*ptr == 'x') {
            num = x;
            switch (operation) {
                case '+':
                    result += num;
                    break;
                case '-':
                    result -= num;
                    break;
                case '*':
                    result *= num;
                    break;
                case '/':
                    result /= num;
                    break;
            }
            ptr++;
        } else if (*ptr == '+' || *ptr == '-' || *ptr == '*' || *ptr == '/') {
            operation = *ptr;
            ptr++;
        } else {
            ptr++;
        }
    }

    return result;
}
