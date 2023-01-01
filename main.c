#include <stdio.h>
#include <stdlib.h>

void fill ( int** A, int** B, int n, int m);
void result ( int** A, int** B, int n, int m );
void max_min( int n, int m, int** A, int** B );
void transposeB ( int** B, int n, int m, int** T );
void mult ( int** B, int n, int m, int** A, int** Mult );
void sortA ( int** A, int n, int m, int sort );
void sum ( int** A, int** B, int n, int m, int sumA, int sumB );

int main()
{

    int n;
    int m;
    int sumA, sumB, sort;
    int methodfill;

    printf("\nEnter the size in columns and rows for A and rows for B:\t");
    scanf("%d", &n);
    printf("\nEnter the size in columns for B:\n\t");
    scanf("%d", &m);

    do {
        printf("\nHow do you want to fill it:\n\t[1] - Enter values by yourself\n\t[2] - Generate values by program");
        printf("\n\tMethod:");
        scanf_s("%d", &methodfill);

        if (methodfill <= 0 || methodfill > 2)
        {
            printf("\nWrong fill method! Try again.\n");
        }
    }while (methodfill <= 0 || methodfill > 2);

    int** A = NULL;
    A = (int**)malloc(n*sizeof(int));
    for(int i=0; i<n; i++)
    {
        A[i] = (int*)malloc(n*sizeof(int));
    }

    int** B = NULL;
    B = (int**)malloc(m*sizeof(int));
    int** Mult = NULL;
    Mult = (int**)malloc(m*sizeof(int));
    int** T = NULL;
    T = (int**)malloc(m*sizeof(int));

    for(int i=0; i<m; i++)
    {
        B[i] = (int**)malloc(n*sizeof(int));
        Mult[i] = (int**)malloc(n*sizeof(int));
        T[i] = (int**)malloc(n*sizeof(int));
    }

    if(methodfill==1)
    {
        for(int i = 0; i<n; i++)
        {
            for (int j=0; j<n; j++)
            {
                printf("Enter value for matrix A[%d][%d]:", i, j);
                scanf("%d", &A[i][j]);
            }
        }
        for (int i=0; i<n; i++)
        {
            for(int j=0; j<m; j++)
            {
                printf("Enter value for matrix B[%d][%d]:", i,j);
                scanf("%d", &B[i][j]);
            }
        }
    }
    else if (methodfill==2)
    {
        for (int i=0; i<n; i++)
        {
            for (int j=0; j<n; j++)
            {
                A[i][j] = rand()%15;
            }
        }
        for (int i=0; i<n; i++)
        {
            for (int j=0; j<m; j++)
            {
                B[i][j] = rand()%15;
            }
        }
    }
    else
    {
        for(int i=0; i<n; i++)
        {
            for(int j=0; j<n; j++)
            {
                A[i][j] = i+j;
            }
        }
        for (int i=0; i<n; i++)
        {
            for(int j=0; j<m; j++)
            {
                B[i][j] = i+j;
            }
        }
    }

    result(A, B, n, m);
    while(1){


         int showNext = 0;

         do{
            printf("\nChoose what to do:\n\t[1] - Maximum and minimum value of matrix A\n\t[2] - Show transpose matrix B\n\t[3] - Multiply both matrixs\n\t[4] - Show sorted matrix A\n\t[5] - Find the sum of the matrix n and m\n\t[6] - Close program");
            printf("\n\tMethod:");
            scanf("%d", &showNext);
         } while (showNext < 1 && showNext > 5);

         switch (showNext) {

         case 1:
             max_min(A, B, n, m);
             break;

         case 2:
             transposeB(T, n, m, B);
             break;

         case 3:
             if(n != m){
                printf("\nInvalid option selected!Try again\n");
                break;
             }
             else {
                mult(B, A, Mult, n, m);
                break;
             }

         case 4:
             sortA(A, n, m, sort);
             break;

         case 5:
             sum(A, B, n, m, sumA, sumB);
             break;

         case 6:
             for (int i=0; i<n; i++)
             {
                 free(A[i]);
             }
             free(A);
             for(int i=0; i<m; i++)
             {
                 free(B[i]);
                 free(Mult[i]);
                 free(T[i]);
             }
             free(B);
             free(Mult);
             free(T);
             break;

         default:
             printf("Wrong method! Try again.\n");
         }
    }
}
void sortA ( int** A, int n, int m, int sort ){
    int sortMethod;
    int n_sort;
    printf("\nChoose sort method:");
    printf("\n1 - Entire matrix\t2 - row sort\n\t");

    do
    {
        scanf("%d", &sortMethod);
    }while(sortMethod != 1 && sortMethod != 2);
    if (sortMethod == 1)
    {
        for(int k=0; k<n*m; ++k)
        {
            for(int i=0; i<n; ++i)
            {
                for(int j=0; j<m; ++j)
                {
                    if(j != m - 1)
                    {
                        if(A[i][j+1] < A[i][j])
                        {
                            int sort = A[i][j+1];
                            A[i][j+1] = A[i][j];
                            A[i][j] = sort;
                        }
                    }
                }
            }
        }
    printf("\n Sorted matrix: \n");
        for(int i=0; i<n; i++)
        {
            for(int j=0; j<n; j++)
            {
                printf("%5d", A[i][j]);
            }
            printf("\n");
        }
    }
    if(sortMethod == 2)
    {
        printf("\n Choose row to sort it\n");
        scanf("%d", &n_sort);

        for(int k=0; k<n; k++)
        {
            for(int j=0; j<n-k; j++)
            {
                if(A[n_sort][j] > A[n_sort][j+1])
                {
                    sort = A[n_sort][j];
                    A[n_sort][j] = A[n_sort][j+1];
                    A[n_sort][j+1] = sort;
                }
            }
        }
        for (int j=0; j<n; j++)
        {
            printf("%5d", A[n_sort][j]);
        }
    }
}

void result ( int** A, int** B, int n, int m){

    system("cls");
    printf("\n\tMatrix A:\n");

    for (int i = 0; i < n; i++){


            for (int j = 0; j < n; j++){

                printf("%5d", A[i][j]);
            }
            printf("\n");
        }
    printf("\n");

    printf("\n\tMatrix B:\n");
    for (int i = 0; i < n; i++){


            for (int j = 0; j < m; j++){

                printf("%5d", B[i][j]);
            }
            printf("\n");
        }
    printf("\n");
}

void max_min(int n, int m, int** A, int** B)
{
    int max = A[0][0];
    int min = A[0][0];

    for (int i=0; i < n; i++)
    {
        for(int j=0; j < n; j++)
        {
            if (A[i][j] > max)
            {
                max = A[i][j];
            }
        }
    }

    for ( int i = 0; i < n; i++ )
    {

      for ( int j = 0; j < n; j++ )
      {
        if ( A[i][j] < min )
        {
              min = A[i][j];
        }

      }

    }

    printf ("\nMaximum: %d\n", max);
    printf ("\nMinimum: %d\n", min);

}

void transposeB ( int** T, int n, int m, int** B )
{
    for ( int i = 0; i < m; i++ )
    {
        for ( int j = 0; j < n; j++ )
        {
            T[j][i] = B[i][j];
        }
    }

    printf("\nTranspose B:\n\n");

    for ( int i = 0; i < n; i++ )
    {
        printf("\t");

        for ( int j = 0; j < m; j++)
        {
            printf("%5d", T[i][j]);
        }

        printf ("\n");
    }
}

void mult ( int** B, int n, int m, int** A, int** Mult ){

    for ( int i = 0; i < m; i++){

        for ( int j = 0; j < n; j++){

            Mult[i][j] = 0;

            for (int k = 0; k < m; k++){

                Mult[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    printf("\n\tMultiplied matrix:\n");

    for ( int i = 0; i < m; i++){

        printf("\t");

        for(int j = 0; j < n; j++){

            printf("%5d", Mult[i][j]);
        }
        printf("\n");
    }
}

void sum ( int** A, int** B, int n, int m, int sumA, int sumB ){

    for ( int i = 0; i < n; i++){

        int sumA = 0;

        for ( int j = 0; j < n; j++){

            sumA += A[i][j];
        }
        printf("Sum rows %d of matrix A: %d\n", i, sumA);
    }

    for ( int j = 0; j < n; j++){

        int sumB = 0;

        for ( int i = 0; i < m; i++ ){

            sumB += B[i][j];
        }
        printf("Sum column %d of matrix B: %d\n", j, sumB);
    }
}
