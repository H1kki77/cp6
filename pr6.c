#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include "function.h"
#include "randomizer.h"
#define SIZE_MIN 2
#define SIZE_MAX 15
#define MIN_EPSILON 1e-15
#define MAX_EPSILON 1e-3

int main () {
    srand(time(NULL));
    printf("This program calculates SLAE by method of simple iteration\n");
    do {
        int size = 0;
        do {
            printf("\nPlease enter amount of equations from %d to %d:\n",SIZE_MIN, SIZE_MAX);
            if(scanf("%d", &size) != 1 || size > SIZE_MAX || size < SIZE_MIN) {
                printf("Incorrect input, enter valid 'n':\n");
            }
            fflush(stdin);
        } while (size > SIZE_MAX || size < SIZE_MIN);
        double e=0.0;
        do {
            printf("Enter precision from %.0e to %.0e:\n",MIN_EPSILON, MAX_EPSILON);
            if(scanf("%lf", &e) != 1 || e < MIN_EPSILON || e > MAX_EPSILON) {
                printf("Incorrect input, enter valid precision:\n");
            }
            fflush(stdin);
        } while (e < MIN_EPSILON || e > MAX_EPSILON);

        double **a = matrix(size);
        double *b = f_array(size);
        double *x = f_array(size);
        double *x1 = f_array(size);
        if(a != NULL && b != NULL && x != NULL && x1 != NULL) {
            printf("Type 1 to input by yourself or 2 for random\n");

            char choice;
            do{
                choice = getch();
            switch (choice){
                case '1':{
                    input_manually(a,b,size);
                }
                break;
                case '2': {
                    input_randomly(a,b,size);
                }
                break;
                default: {
                    printf("Incorrect input, try again\n");
                    fflush(stdin);
                }
               break;
                }
            }while (choice != '1' && choice != '2');
            print1(a, b, size);

            if(!domimant_d(a,size)) {
                printf("Error, matrix isn`t diagonally dominant\n");
            }
            else {
                calculation(a, b, x, x1, size, e);
                const int accuracy = (int) - log10 (e);
                printf("\n");
                for (int i = 0; i<size; i++) {
                    printf("x%d = %.*lf ", i+1, accuracy, x[i]);
                }
                printf("\n");

                print2(a, b, x, size, accuracy);
            }
            for (int i = 0; i<size; i++) {
                free(a[i]);
            }

            free(a);
            free(b);
            free(x);
            free(x1);
        }

        printf("Press 'r' to restart or ANY other key to exit:\n");
    }while (getch() == 'r');

    return 0;
}
