#include "matrix.h"

int main(void) {
    Matrix(int) mat = Matrix_new(int, 4, 4);
    mat[0] = 1; mat[1] = 0; mat[2] = 2; mat[3] = -1;
    mat[4] = 3; mat[5] = 0; mat[6] = 0; mat[7] = 5;
    mat[8] = 2; mat[9] = 1; mat[10] = 4; mat[11] = -3;
    mat[12] = 1; mat[13] = 0; mat[14] = 5; mat[15] = 0;
    Matrix_print(mat, lambda(void, (int n), { printf("%d    ", n); }));
    printf("det(MAT) = %d\n", Matrix_determinant(int, mat));
    Matrix_free(mat);
    Matrix(int) kk = Matrix_new(int, 3, 3);
    kk[0] = 1; kk[1] = 0; kk[2] = 1;
    kk[3] = 0; kk[4] = 1; kk[5] = 1;
    kk[6] = 1; kk[7] = 1; kk[8] = 1;
    Matrix(long double) invert = Matrix_invert(int, kk);
    Matrix_print(invert, lambda(void, (long double n), { printf("%Lf    ", n); }));
    Matrix_free(invert);
    kk[0] = 0; kk[1] = 7; kk[2] = 0;
    kk[3] = 0; kk[4] = 0; kk[5] = 0;
    kk[6] = 0; kk[7] = 1; kk[8] = 0;
    printf("Is invalid ? : %d\n", Matrix_invert(int, kk) == NULL);
    Matrix_free(kk);
    return 0;
}
