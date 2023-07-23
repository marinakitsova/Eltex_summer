#include <stdio.h>
#include <stdlib.h>
#include "addition.h"
#include "subtraction.h"
#include "multiplication.h"
#include "division.h"

void exit_program(int code) {

    printf("Программа завершается с кодом: %d\n", code);
    exit(code);
}

int main() {
    int a,b;
    char operetion;


    printf("Введите операцию (+, -, *, /): ");
    scanf("%c", &operetion);


    if (operetion != '+' &&operetion != '-' &&operetion != '*' &&operetion != '/') {
        printf("Ошибка: недопустимая операция\n");
        exit_program(1);
    }

    printf("Введите два числа: ");
    scanf("%d %d", &a, &b);

    switch (operetion) {
      case '+':
          printf("Результат: %d\n", addition(a, b));
          break;
      case '-':
          printf("Результат: %d\n", subtraction(a, b));
          break;
      case '*':
          printf("Результат: %d\n", multiplication(a, b));
          break;
      case '/':
          if (b == 0) {
              printf("Ошибка: деление на ноль\n");
              exit_program(2);
          }
          printf("Результат: %.2f\n", division(a, b));
          break;
      default:
          printf("Ошибка: недопустимая операция\n");
          exit_program(1);

    }

    exit_program(0);
    return 0;
}
