#include <stdio.h>

int main()
{
int a= 0x0000AABB;
unsigned char c;

c = (a & 0x000000FF);
printf("first byte of a = %x\n",c);
c = ((a>>8) & 0xFF);
printf("second byte of a = %x\n",c);

printf("\n");

 a = 0x00DDAABB;
 int b = 0x00CCAABB;
 for (int i = 0; i < sizeof(a); i++) {
      c = (a & 0x000000FF);
      printf("%d byte a = %x\n", i , c);
      a = a >> 8;
}

printf("\n");

    a = 0x00DDAABB;

  	printf("default a - 0x00%X", a);
  	a^= 0x11 << 16;
  	printf("\nit's a after bite move - 0x00%X",a);

  	printf("\nmust be - 0x00%X\n", b);
  	return 0;
}
