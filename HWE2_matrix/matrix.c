#include <stdio.h>

int main(void)
{
  int N = 5;
  int a [N][N];
  int num = N-1;
  for (int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            if(j < num)
               a[i][j] = 1;
            else
                a[i][j] = 0;
            printf("%d", a[i][j]);
        }
        num = num - 1;
        printf("\n");
  }
  printf("\n");

  int b [5] = {1,2,3,4,5};
  for (int i = 5; i > 0; --i)
      printf("%d ", b[i-1]);

      printf("\n\n");

   num = 1;

   for (int i = 0; i < N; i++) {
       for (int j = 0; j < N; j++) {
           a[i][j] = num++;
           printf("%d\t", a[i][j]);
   }
   printf("\n");
 }

 printf("\n");

    int matrix[N][N];
    num = 1;


    for (int i = 0; i < N/2; i++)
    {
        for (int j = i; j < N - i; j++)
            matrix[i][j] = num++;

        for (int j = i + 1; j < N - i; j++)
            matrix[j][N - 1 - i] = num++;

        for (int j = N - 2 - i; j >= i; j--)
            matrix[N - 1 - i][j] = num++;

        for (int j = N - 2 - i; j > i; j--)
            matrix[j][i] = num++;
    }
    matrix[N/2][N/2] = N*N;

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
                printf("%d\t", matrix[i][j]);
        }
        printf("\n");
    }
}
