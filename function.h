#ifndef FUNCTION_H
#define FUNCTION_H
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

double **matrix(const int size)
{
    double **array = malloc(size * sizeof(double *));
    for (int i = 0; i < size; i++)
        {
        array[i] = malloc(size * sizeof(double));
        if (array[i] == NULL)
        {
            printf("Error allocating memory for array\n");
            return NULL;
        }
    }
    return array;
}

double *f_array(const int size)
{
 double *array = malloc(size * sizeof(double));
    if (array == NULL) {
        printf("Error allocating memory for array\n");
        return NULL;
    }
    return array;
}

void input_manually(double **a, double *b, const int size){
    printf("Input SLAE elements (matrix with A elements has to be with dominant MAIN diagonal\n");
    int validInput = 0;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            do {
                printf("A(%d,%d) = ", i+1, j+1);
                validInput = scanf("%lf", &a[i][j]);
                if (validInput != 1) {
                    printf("Error, enter correct value for A: \n");
                }
                fflush(stdin);
            }while(validInput != 1);
        }
        do {
            printf("B(%d) = ", i+1);
            validInput = scanf("%lf", &b[i]);
            if (validInput != 1) {
                printf("Error, enter correct value for B: \n");
            }
            fflush(stdin);
        }while(validInput != 1);
    }
}

bool domimant_d (double **a, const int size) {
    for (int i = 0; i < size; i++) {
        double diagonal = fabs(a[i][i]);
        double sum = 0.0;
        for (int j = 0; j < size; j++) {
            if (j != i) {
                sum += fabs(a[i][j]);
            }
        }
        if (diagonal <= sum) {
            return false;
        }
    }
    return true;
}

 void calculation(double **a, double *b, double *x, double *x1, const int size, const double e) {
    int iteration = 0;
    double max_delta = 0;
    do {
        iteration++;
        for (int i = 0; i < size; i++) {
            x1[i] = 0.0;
            for (int j = 0; j < size; j++) {
                if(i !=j){
                    x1[i] = x1[i] + a[i][j] * x[j];
                }
            }
            x1[i] = (b[i] - x1[i]) / a[i][i];
        }
        max_delta = 0;
        for (int i = 0; i < size; i++) {
            if (fabs(x[i] - x1[i]) > max_delta) {
                max_delta = fabs(x[i] - x1[i]);
            }
            x[i] = x1[i];
        }

    } while (max_delta>e);
}

void print1(double **a, double *b, const int size) {
    printf("\nFirst SLAE is:\n");
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (j == 0) {
                printf(" %.1lf*x%d", a[i][j], j+1);
            }
            else {
                printf(" %+.1lf*x%d", a[i][j], j+1);
            }
        }
        printf(" = %.1lf\n", b[i]);
    }
}

void print2(double **a, double *b, double *x, const int size, int accuracy) {
    printf("\nFinal SLAE is:\n");
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (j == 0) {
               printf(" %.1lf*%.*lf", a[i][j], accuracy, x[j]);
            } else {
                printf(" %+.1lf*%.*lf", a[i][j], accuracy, x[j]);
            }
        }
        printf(" = %.1lf\n", b[i]);
    }
}


#endif //FUNCTION_H
