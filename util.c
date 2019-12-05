#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <math.h>

void nrerror(char error_text[]){
// to show run-time error messages
    fprintf(stderr, "Run-time error!\n");
    fprintf(stderr, "%s\n", error_text);
    fprintf(stderr, "...now exiting to system...\n");
    exit(1);
}

void print_2d_matrix(float **a, int n, int m){
// print a 2D matrix of size nxm
    int i, j;
    
    for (i=0; i<n; i++){
        for (j=0; j<m; j++){
            fprintf(stdout, "%.2f    ", a[i][j]);
        }
        fprintf(stdout, "\n");
    }
}

void print_2d_matrix_replaceDiag(float **a, int n, int m, float *p){
// print a 2D matrix of size nxm, replacing the diagonal values with elements in p
// original matrix A is not modified
    int i, j;
    
    for (i=0; i<n; i++){
        for (j=0; j<m; j++){
            if (i==j) fprintf(stdout, "%.2f    ", p[i]);
            else fprintf(stdout, "%.2f    ", a[i][j]);
        }
        fprintf(stdout, "\n");
    }
}

void print_vec(float *a, int n){
// print a vector of length n
    int i;

    for (i=0; i<n; i++) fprintf(stdout, "%.2f   ", a[i]);
    fprintf(stdout, "\n");
}

void print_vec_int(int *a, int n){
// print an int vector of length n
    int i;

    for (i=0; i<n; i++) fprintf(stdout, "%d   ", a[i]);
    fprintf(stdout, "\n");
}

void matrix_multiply(float **a, float **b, int n, int m1, int m2, float **c){
// matrix multiplication between A (m1xn) and B (nxm2)
// results stored in matrix C (m1xm2)
    int i, j, k;

    for (i=0; i<m1; i++){ // rows of A
        for (j=0; j<m2; j++){ // columns of B
            c[i][j] = 0;
            for (k=0; k<n; k++){ // element in common position
                c[i][j] += a[i][k] * b[k][j];
            }
        }
    }
}

void copy_matrix_col(float **a, float **b, int n, int start, int stop){
// copy content of (start:stop) columns of matrix A to matrix B
// both matrix should have n rows
// start & stop should be 0-indexed
    int i, j, j_b;
    
    for (i=0; i<n; i++){ // rows
        for (j=start; j<=stop; j++){ // columns
            j_b = j - start;
            b[i][j_b] = a[i][j];
        }
    }
}

void fill_index_vec(int *index, int n){
// fill in an index vector with elements 1 to n
    int i;

    for (i=0; i<n; i++) index[i] = i;
}

void fill_rand_vec(float *index, int n, int min, int max){
// fill in a vector with random elements in the range min to max
// srand should be set up before this function is called
    int i;

    for (i=0; i<n; i++) index[i] = min + rand() % (max - min + 1);
}
        

