#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void matrixMul(int size)
{
    int row = size, col = row;
    int *first = (int *)malloc(row * col * sizeof(int));
    int *second = (int *)malloc(row * col * sizeof(int));
    int *multiply = (int *)malloc(row * col * sizeof(int));
    int m = row, c, d, k, sum = 0;

    for (c = 0; c < m; c++)
    {
        for (d = 0; d < m; d++)
        {
            *(first + c * col + d) = d;
            //first[c][d] = d;
        }
    }

    for (c = 0; c < m; c++)
    {
        for (d = 0; d < m; d++)
        {
            *(second + c * col + d) = d;
            //second[c][d] = d;
        }
    }
    for (c = 0; c < m; c++)
    {
        for (d = 0; d < m; d++)
        {
            for (k = 0; k < m; k++)
            {
                sum = sum + (*(first + c * col + k)) * (*(second + k * col + d));
                //sum = sum + first[c][k] * second[k][d];
            }

            *(multiply + c * col + d) = sum;
            //multiply[c][d] = sum;
            sum = 0;
        }
    }
}

int main()
{
    int size;
    scanf("%d",&size);
    int sizeTable = 0;
    double total = 0;
    for (int i = 1; i <= 10; i++)
    {
        sizeTable = size * i;
        clock_t t;
        t = clock();
        matrixMul(sizeTable);
        t = clock() - t;
        double executionTime = ((double)t) / CLOCKS_PER_SEC;
        printf("Iteration: %d Mat Size: %dx%d Execution Time: %f\n", i, sizeTable, sizeTable, executionTime);
        total += executionTime;
        if (i == 10)
        {
            printf("Average Execution Time: %f\n", total / ((double)i));
        }
    }
    return 0;
}