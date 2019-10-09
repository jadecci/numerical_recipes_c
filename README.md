# \<Numerical Recipes in C> Codes with Examples

This repository contains codes from the book \<Numerical Recipes in C> with my comments. The codes are contained in a function, which is called in the
main function with example inputs. All codes can be compiled and run without input parameter.

## Usage

For MacOS, the codes can be compiled by `clang util.c file_to_compile.c -o programme`. The compiled code can be then run by `./programme`.

## Content

The codes included in this repository, in correspondence to the book's chapters:

**Chapter 2 Solution of Linear Algebraic Equations**

- Gauss-Jordan Elimination with full pivoting: `gauss_jordan_full_pivot.c`

- LU Decomposition

- Cholesky Decomposition

- QR Decomposition

**Chapter 3 Interpolation and Extrapolation**

- Polynomial

- Cubic Spline

- Higher Dimensionality

**Chapter 6 Special Functions**

- Gamma, Beta, Factorials, Binomial

- Incomplete Gamma, Error, Chi-Square, Cumulative Poisson

- Incomplete Beta, Student's, F, Cumulative Binomial

**Chapter 7 Random Numbers**

- Uniform Deviates

- Tranformation: Exponential and Normal Deviates

- Rejection: Gamma, Poisson, Binomial Deviates

- Monte Carlo Integration

**Chapter Minimisation or Maximisation of Functions**

- Golden Section Search (1D)

- Parabolic Interpolation and Brent's Method (1D)

- First Derivatives (1D)

- Downhill Simplex

- Direction Set (Powell's)

- Variable Metric

- Linear Programming and Simplex Method

**Chapter 11 Eigensystems**

- Jacobi Transforms (symmetric matrix)

- Givens and Householder Reductions

- Eigenvalues and Eigenvectors of tridiagonal matrix

- Hermitian

- Hessenberg Form

- QR Algorithm for Real Hessenberg Matrices

**Chapter 14 Statistical Description of Data**

- Moments (mean, variance, skewness, etc.)

- Comparing Distributions

- Contigency Table Analysis

- Linear Correlation

- Nonparametric/Rank Correlation

- Comparing 2D Distributions

- Savitzky-Golay Smoothing Filters

**Chapter 15 Modeling of Data**

- Least Squares (MLE)

- General Linear Least Squares

- Nonlinear models
