#ifndef _UTILS_H_
#define _UTILS_H_

void nrerror(char error_text[]);

void print_2d_matrix(float **a, int n, int m);
void matrix_multiply(float **a, float **b, int n, int m1, int m2, float **c);
void copy_matrix_col(float **a, float **b, int n, int start, int stop);


#endif /* _UTILS_H_ */
