#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include "calculator.h"


int main() {
    int a,b;
    char operetion;

    void* handle = dlopen("./libcalculator.so", RTLD_LAZY);
    if (!handle) {
        fprintf(stderr, "Ошибка при загрузке динамической библиотеки: %s\n", dlerror());
        return 1;
    }


    int (*add)(int, int) = dlsym(handle, "add");
    int (*subtract)(int, int) = dlsym(handle, "subtract");
    int (*multiply)(int, int) = dlsym(handle, "multiply");
    float(*divide)(int, int) = dlsym(handle, "divide");

    if (!add || !subtract || !multiply || !divide) {
        fprintf(stderr, "Ошибка при загрузке из динамической библиотеки: %s\n", dlerror());
        dlclose(handle);
        return 1;
    }

    printf("Введите операцию (+, -, *, /): ");
    scanf(" %c", &operetion);


        if (operetion != '+' &&operetion != '-' &&operetion != '*' &&operetion != '/') {
             printf("Ошибка: недопустимая операция\n");
             dlclose(handle);
             return 1;
        }

         printf("Введите два числа: \n");
         scanf("%d%d", &a, &b);

         switch (operetion) {
           case '+':
               printf("Результат: %d\n", add(a, b));
               break;
           case '-':
               printf("Результат: %d\n", subtract(a, b));
               break;
           case '*':
               printf("Результат: %d\n", multiply(a, b));
               break;
           case '/':
               if (b == 0) {
                   printf("Ошибка: деление на ноль\n");
                   dlclose(handle);
                   return 2;
               }
               printf("Результат: %.2f\n", divide(a, b));
               break;
           default:
               printf("Ошибка: недопустимая операция\n");
               dlclose(handle);
               return 1;

         }
          dlclose(handle);
          return 0;

}
