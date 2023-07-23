#include <stdio.h>

int main()
{
  int a = 270533154;
  char *ptr;
  ptr = (char*) &a;
  printf("first byte of a = %d\n", *ptr);
  ptr++;
  printf("second byte of a = %d\n", *ptr);
  ptr++;
  *ptr = 8;
  printf("third byte of a = %d\n", *ptr);
  ptr++;
  printf("fourth byte of a = %d\n", *ptr);


  return 0;

}
