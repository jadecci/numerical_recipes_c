#ifndef _UTILS_H_
#define _UTILS_H_

void nrerror(char error_text[]);

void print_2d_matrix(float **a, int n, int m);
void print_2d_matrix_replaceDiag(float **a, int n, int m, float *p);
void print_vec(float *a, int n);
void print_vec_int(int *a, int n);

void matrix_multiply(float **a, float **b, int n, int m1, int m2, float **c);
void copy_matrix_col(float **a, float **b, int n, int start, int stop);
void fill_index_vec(int *index, int n);


#endif /* _UTILS_H_ */
