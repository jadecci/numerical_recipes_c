#include <math.h>
#include <stdio.h>
#include "util.h"
#include <stdlib.h>

void moment(float data[], int n, float *mu, float *std, float *var, float *skew, float *kurt){
    //define variabbles
    int i;
    float diff=0.0, diff_curr;

    if (n <= 1) nrerror("moment: n must be at least 2.");

    // First pass: compute sample mean
    *mu = 0.0;
    for (i=0; i<n; i++) *mu += data[i];
    *mu /= n;

    // Second pass: compute the moment term
    *var=(*skew)=(*kurt)=0.0;
    for (i=0; i<n; i++){
        diff_curr = data[i]-(*mu);
        diff += diff_curr;
        *var += pow(diff_curr, 2);
        *skew += pow(diff_curr, 3);
        *kurt += pow(diff_curr, 4);
    }

    // Finally: subtract the difference term
    *var = (*var - pow(diff, 2)/n)/(n-1);
    *std = sqrt(*var);
    if (*var){
        *skew /= n * pow(*std, 3);
        *kurt = (*kurt) / (n * pow(*var, 2)) - 3.0;
    }
    else nrerror("moment: variance is zero. No skew/kurtosis could be computed.");
}

int main(){
	// define inputs
    int n=100;
    float mu, std, var, skew, kurt;
    float data[n];
    
    // generate normally distributed data with a fixed seed
    srand(1);
    fill_rand_vec(data, n, 0, 16);
    fprintf(stdout, "Data points: ");
    print_vec(data, n);

    // compute the moments
    moment(data, n, &mu, &std, &var, &skew, &kurt);
    fprintf(stdout, "Sample mean: %.2f\n", mu);
    fprintf(stdout, "Sample variance: %.2f; standard deviation: %.2f\n", var, std);
    fprintf(stdout, "Skewness: %.2f\n", skew);
    fprintf(stdout, "Kurtosis: %.2f\n", kurt);
}