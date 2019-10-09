#include <math.h>
#include <stdio.h>
#include "util.h"
#define SWAP(a, b) {float temp; temp=(a); (a)=(b); (b)=temp;}

void gaussj(float **a, int n, float **b, int m){
	// define variables
	int i_piv[n], index_r[n], index_c[n];
	int i, i_col, i_row, j, k, l;
	float big, piv_inv, temp;

	// initialise i_piv
	for (i=0; i<n; i++) i_piv[i] = 0;

	// main loop (through each column)
	for (i=0; i<n; i++){
    
        // find pivots
		big = 0.0;
        // loop through rows with no pivot
		for (j=0; j<n; j++){
			if (i_piv[j] != 1){
                // loop through columns with no pivot
				for (k=0; k<n; k++){
					if (i_piv[k] == 0){
						// choose largest element for pivot
						if (fabs(a[j][k]) >= big){
							big = fabs(a[j][k]);
							i_row = j;
							i_col = k;
						}
					}
				}
			}
		}
		++(i_piv[i_col]);
		//fprintf(stdout, "Reducing column %d...\n", i_col+1);

		// swap rows to put pivots on the diagonal
		if (i_row != i_col){
			for (j=0; j<n; j++) SWAP(a[i_row][j], a[i_col][j]);
			for (j=0; j<n; j++) SWAP(b[i_row][j], b[i_col][j]);
		}
		//fprintf(stdout, "\nSwapped matrix A:\n");
		//print_2d_matrix(a, 4, 4);
        //print_2d_matrix(b, 4, 5);
        
        index_r[i] = i_row; // original row of pivot
        index_c[i] = i_col; // actual column/row of pivot
        if (a[i_col][i_col] == 0.0) nrerror("gauss_jordan_full_pivot: Singular matrix");
        
        // divide row by pivot
        // linear combination of rows
        // i_col row = 0 * a non-pivoted row + piv_inv * i_col row
        piv_inv = 1.0 / a[i_col][i_col];
        for (j=0; j<n; j++) a[i_col][j] *= piv_inv;
        for (j=0; j<m; j++) b[i_col][j] *= piv_inv;
        
        // reduce non-pivoted rows
        // linear combination of rows
        // j row = 1 * j row - temp * i_col row
        for (j=0; j<n; j++){
            if (j != i_col){
                temp = a[j][i_col];
                for (k=0; k<n; k++) a[j][k] -= a[i_col][k] * temp;
                for (k=0; k<m; k++) b[j][k] -= b[i_col][k] * temp;
            }
        }
	}
}

int main(){
	// define inputs
	float *a[] = {(float[]){2, 1, 3, 4}, (float[]){10, 0, 3, 0}, (float[]){5, -3, 0, 1}, (float[]){2, 2, 3, 3}};
	float *b[] = {(float[]){44, 1, 0, 0, 0}, (float[]){-4, 0, 1, 0, 0}, (float[]){5, 0, 0, 1, 0}, (float[]){34, 0, 0, 0, 1}};
    float *c[] = {(float[]){2, 1, 3, 4}, (float[]){10, 0, 3, 0}, (float[]){5, -3, 0, 1}, (float[]){2, 2, 3, 3}}; // stores A
    float *d[] = {(float[]){0, 0, 0, 0}, (float[]){0, 0, 0, 0}, (float[]){0, 0, 0, 0}, (float[]){0, 0, 0, 0}}; // to hold A inverse later
    float *e[] = {(float[]){0, 0, 0, 0}, (float[]){0, 0, 0, 0}, (float[]){0, 0, 0, 0}, (float[]){0, 0, 0, 0}}; // to hold results later
	
	// print inputs
	fprintf(stdout, "Matrix A:\n");
	print_2d_matrix(a, 4, 4);
	fprintf(stdout, "Matrix b:\n");
	print_2d_matrix(b, 4, 5);

	// run Gaussian-Jordan elimination
	gaussj(a, 4, b, 5);
 
    // print outputs
    fprintf(stdout, "New matrix A (identity):\n");
    print_2d_matrix(a, 4, 4);
    fprintf(stdout, "New matrix b (solution of x | A inverse):\n");
    print_2d_matrix(b, 4, 5);
    
    // check if A inverse is accurate
    copy_matrix_col(b, d, 4, 1, 4);
    print_2d_matrix(d, 4, 4);
    matrix_multiply(c, d, 4, 4, 4, e);
    fprintf(stdout, "Results of A * A_inv:\n");
    print_2d_matrix(e, 4, 4);

	return 0;
}
