#ifndef RANDOMIZER_H
#define RANDOMIZER_H
#include <math.h>
void  input_randomly(double **a, double *b, const int size) {
    for (int i = 0; i < size; i++) {
        double sum = 0.0;
        for (int j = 0; j < size; j++) {
            if (i != j) {
                a[i][j] = (rand() % 200 - 100) / 10.0;
                sum += fabs(a[i][j]);
            }
        }
        a[i][i] = sum + rand() % 50 / 10.0 + 1.0;
        b[i] = (rand() % 200 - 100) / 10.0;
    }
}
#endif //RANDOMIZER_H
