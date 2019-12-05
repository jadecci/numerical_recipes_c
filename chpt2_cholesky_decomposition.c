#include <math.h>
#include <stdio.h>
#include "util.h"

// Cholesky decomposition
// Note that only the upper-triangular part of input matrix A is needed
// Off-diagonal elements in L are stored by replacing the corresponding elements in A (upper-tri)
// Diagonal elements in L are stored in a separate vector p
void choldc(float **a, int n, float p[]){
    // define variables
    int i, j, k;
    float sum;

    // loop through rows
    for (i=0; i<n; i++){
        // loop through upper-triangular elemetns in the row
        for (j=i; j<n; j++){
            sum = a[i][j]; // LHS
            for (k=0; k<=(i-1); k++) sum -= a[i][k] * a[j][k]; // First term
            if (i == j){
                if (sum <= 0) nrerror ("choldc: A is not positive definite");
                p[i] = sqrt(sum); // diagonal elements
            }
            else a[j][i] = sum / p[i]; // off-diagonal elements
        }
    }
}

// Cholesky solver for linear equations
// Inputs A and p should be outputs from choldc
void cholsl(float **a, int n, float p[], float b[], float x[]){
    // define variables
    int i, k;
    float sum;

    // First, we solve Ly = b
    for (i=0; i<n; i++){
        sum = b[i]; // First term
        for (k=0; k<=(i-1); k++) sum -= a[i][k] * x[k]; // Second term (summation part)
        x[i] = sum / p[i]; // Divide by diagonal element of L
    }

    // Second, we solve L'x = y
    for (i=(n-1); i>=0; i--){
        sum = x[i]; // First term
        for (k=(i+1); k<n; k++) sum -= a[k][i] * x[k]; // Second term (summartion part)
        x[i] = sum / p[i]; // Divide by diagonal element of L
    }
}

int main(){
	// define inputs
	float *a[] = {(float[]){4, 20, -6, 2}, (float[]){0, 101, -30, 12}, (float[]){0, 0, 18, 12}, (float[]){0, 0, 0, 46}};
    float b[4] = {2, 7, 12, -12};
    float p[4]; // to hold diagonal elements of L
    float x[4]; // to hold results later
	
	// print inputs
	fprintf(stdout, "Matrix A (only upper-triangular part):\n");
	print_2d_matrix(a, 4, 4);
	fprintf(stdout, "Vector b:\n");
	print_vec(b, 4);

	// Cholesky decomposition
	choldc(a, 4, p);
    fprintf(stdout, "Matrix L (lower-triangular & diagonal):\n");
    print_2d_matrix_replaceDiag(a, 4, 4, p);

    // Solve Ax = b
    cholsl(a, 4, p, b, x);
    fprintf(stdout, "Solution to x:\n");
    print_vec(x, 4);

	return 0;
}