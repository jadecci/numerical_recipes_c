#include <math.h>
#include <stdio.h>
#include "util.h"
#define SWAP(a, b) {float temp; temp=(a); (a)=(b); (b)=temp;}
#define TINY 1.0e-20

// LU decomposition
// Input vector index should be a vector of 1 to n
// Output: LU decomposition in A, pivot positions in index
// Unlike the original codes, we do not keep track of the number of row switching as even/odd here,
// which is only used for computing det(A) later
void ludcmp(float **a, int n, int *index){
    // define variables
    int i, j, row_max, col_max, i_max, k;
    float sum, curr;
    float scale[n];

    // Implicit pivoting: find the scaling factor needed for each row
    // The scaling factor is inverse of the largest absolute value in each column
    // i.e. each row's largest value is 1 after implicit scaling, thus more comparable to each other
    for (i=0; i<n; i++){
        row_max = 0.0;
        for (j=0; j<n; j++){
            if ((curr=fabs(a[i][j])) > row_max) row_max=curr; // find the largest absolute value
        }
        if (row_max == 0.0) nrerror("ludcmp: At least one row in A is no nonzero element!");
        scale[i] = 1.0 / row_max; // inverse the max value for the scale factor
    }

    // Crout's method: loop through the columns
    // Note that both the lower non-diagonal part of L and upper part of U are stored in A
    // i.e. by replacing the corresponding element in A
    for (j=0; j<n; j++){
        // Solve for elements in column j in matrix U
        // U: only upper matrix is need, i.e. i < j
        // Note that beta_jj (the pivot) will be computed later
        for (i=0; i<j; i++){
            sum = a[i][j]; // first term in the equation
            for (k=0; k<i; k++) sum -= a[i][k] * a[k][j]; // subtract the second term 
            a[i][j] = sum; // replace the element in A
        }

        // Solve for elements in column j in matrix L
        // L: only lower matrix is needed, i.e. i >= j
        col_max = 0.0;
        for (i=j; i<n; i++){
            // First, solve for the elements (same as solving for elements in U)
            // Note that this only computes the numerator part of the equation
            sum=a[i][j];
            for (k=0; k<j; k++) sum -= a[i][k] * a[k][j];
            a[i][j] = sum;

            // Keep track of the largest element in the column and its index
            // Note that the element is scaled before comparison (implicit pivoting)
            if ((curr=scale[i]*fabs(sum)) >= col_max){
                col_max = curr;
                i_max = i;
            }
        }

        // Partial pivoting: switch rows so that diagonal element is the largest in the column
        // Skipped if the current pivot is already the largest element
        if (j != i_max) {
            for (k=0; k<n; k++) SWAP(a[i_max][k], a[j][k]); 
            // Scaling factor for the rows should be switched too
            // Note that scale[j] doesn't need to be updated, since it won't be used anymore
            scale[i_max] = scale[j]; 
        }

        // Row affected by partial pivoting is recorded in the vector index
        index[j] = i_max;
        // For singular matrix
        if (a[j][j] == 0.0) a[j][j] = TINY;
        // Finish solving the elements in L: dividing by the pivot (denomintor part of euqation)
        // Skip for j=n since no element in L needs solving for the last row
        if ( j != (n-1) ){
            curr = 1.0 / a[j][j];
            for (i=j+1; i<n; i++) a[i][j] *= curr;
        }
    }
}

// LU solver for Ax = b using back-substitution
// Input matrix A should be its LU decomposition (from ludcmp)
// Input vector index stores the (row) positions of all pivots (from ludcmp)
// Output: solution of x in b
void lubksb(float **a, int n, int *index, float b[]){
    int i, i_pivot, start_sum=0, j;
    float sum;

    // First, we solve Ly = b with forward substitution
    for (i=0; i<n; i++){
        i_pivot = index[i];
        // First term in the equation
        sum = b[i_pivot];
        // The summation part (second term) of the equation
        // Skipped for i=1 Since the first row doesn't need to be solved
        // The first few consecutive rows with b[i]=0 can also be skipped since the sum will also be zero
        if (start_sum){
            for (j=(start_sum-1); j<i; j++) sum -= a[i][j] * b[j];
        }
        else if (sum) start_sum = i+1;
        // Put the solution for y in b & unscramble b
        b[i_pivot] = b[i];
        b[i] = sum;
    }

    // Second, we solve Ux = y with back substitution
    for (i=(n-1); i>=0; i--){
        // First term in the equation
        sum = b[i];
        // Second term in the equation
        for (j=i+1; j<n; j++) sum -= a[i][j] * b[j];
        // Divide by the denominator
        b[i] = sum / a[i][i];
    }
}

int main(){
	// define inputs
	float *a[] = {(float[]){2, 1, 3, 4}, (float[]){10, 0, 3, 0}, (float[]){5, -3, 0, 1}, (float[]){2, 2, 3, 3}};
	float b[4] = {44, -4, 5, -1};
    int index[4];

    // create the index vector
    fill_index_vec(index, 4);
	
	// print inputs
	fprintf(stdout, "Matrix A:\n");
	print_2d_matrix(a, 4, 4);
	fprintf(stdout, "Vector b:\n");
	print_vec(b, 4);

	// LU decomposition
	ludcmp(a, 4, index);
    fprintf(stdout, "New matrix A (L and U scrambled):\n");
    print_2d_matrix(a, 4, 4);

    // Solve Ax = b
    lubksb(a, 4, index, b);
    fprintf(stdout, "New vector b (solution to x):\n");
    print_vec(b, 4);

	return 0;
}
