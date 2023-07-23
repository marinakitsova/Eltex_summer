#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#define MAX_CONTACTS 100
#define MAX_NAME_LENGTH 50
#define MAX_PHONE_LENGTH 15

typedef struct phonebook {
    char name[MAX_NAME_LENGTH];
    char number[MAX_PHONE_LENGTH];
} contact;

contact contacts[MAX_CONTACTS];
int numcontacts = 0;

void addcontacts() {
      if (numcontacts >= 100) {
          printf("Невозможно добавить контакт\n");
          return ;
      }


      contact newcontact;
      printf("Введите имя:\n");
      scanf("%s", newcontact.name);
      printf("Введите номер телефона:\n");
      scanf("%s", newcontact.number);

      contacts[numcontacts] = newcontact;
      numcontacts++;

      printf("Контакт добавлен\n");
}


void displaycontacts() {
      if (numcontacts == 0) {
          printf("Справочник пуст\n");
          return;
      }


      printf("Контакты\n");
      for (int i = 0; i < numcontacts; i++){
          printf("%s - %s\n",contacts[i].name, contacts[i].number);
      }
}


void deletecontact() {
      if (numcontacts == 0) {
          printf("Справочник пуст\n");
          return;
      }

      char name[MAX_NAME_LENGTH];
      printf("Введите имя контакта, который хотите удалить:\n");
      scanf("%s", name);

      int contactindex = -1;
      for (int i = 0; i < numcontacts; i++) {
          if (strcmp(contacts[i].name, name) == 0) {
              contactindex = i;
              break;
          }
      }

      if (contactindex == -1) {
        printf("Контакт с именем %s не найден\n", name);
        return;
      }

      for (int i = contactindex; i < numcontacts - 1; i++) {
          contacts[i] = contacts[i + 1];
      }

      numcontacts--;

      printf("Контакт%s успешно удален\n", name);
}

int main(){
    int choice;


    do {
        printf("\nАбонентный справочник\n");
        printf("1. Добавить контакт\n");
        printf("2. Показать все контакты\n");
        printf("3. Удалить контакт\n");
        printf("4. Выйти\n");
        printf("Введите номер операции\n");
        scanf("%d\n", &choice);

        switch (choice) {
          case 1:
                addcontacts();
                break;
          case 2:
                displaycontacts();
                break;
          case 3:
                deletecontact();
                break;
          case 4:
                printf("До свидания!\n");
                break;
          default:
                printf("Неверный номер операции, попробуйте еще раз\n");
                break;
        }
    } while (choice != 0);

    return 0;
}
