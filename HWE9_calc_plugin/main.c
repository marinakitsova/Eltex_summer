#include <stdio.h>
#include <dlfcn.h>
#include <stdlib.h>
#include "calculator.h"

int main() {
    int a, b;

    void* handle = dlopen("./libcalculator.so", RTLD_LAZY);
    if (!handle) {
        fprintf(stderr, "Ошибка при загрузке динамической бибилиотеки: %s\n", dlerror());
        return 1;
    }


    int (*operationFunc)(int, int);
    printf("Введите операцию (+, -, *, /): ");
    scanf("%c", operation);

    switch (operation) {
      case '+':
          operationFunc = dlsym(handle, "addition");
          break;
      case '-':
          operationFunc = dlsym(handle, "subtraction");
          break;
      case '*':
          operationFunc = dlsym(handle, "multiplication");
          break;
      case '/':
          operationFunc = dlsym(handle, "division");
          break;
      default:
          printf("Ошибка: недопустимая операция\n");
          dlclouse(handle);
          return 1;
    }

    printf("Введите два числа: ");
    scanf("%d, %d", &a, &b);

    printf("Результат: %d\n", operationFunc(a, b));

    dlclouse(handle);
    return 0;
}
