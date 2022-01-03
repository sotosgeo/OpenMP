/*
Estimate pi using the formula
    pi = 4*[1 - 1/3 + 1/5 - 1/7 + 1/9 - . . . ]
       = 4 [1/(2*0 + 1) - 1/(2*1 + 1) + 1/(2*2 + 1) -...]
       
       = 4 S (-1)^i / (2*i + 1)
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//--------------------------------
int main(int argc, char *argv[]) {
    long n, i;
    int thread_count;

    thread_count = 4;
    n = 1e8; //100000000;

    if (argc > 1) {
        thread_count = atoi(argv[1]);
    }
    if (argc > 2) {
        n = atol(argv[2]);
    }

    double factor = 1.0;
    double sum = 0;
    for (i = 0; i < n; i++) {
        sum += factor / (2 * i + 1);
        factor = -factor;
    }
    double p_approx  = 4.0 * sum;

    printf("With n = %ld terms\n", n);
    printf("   Our estimate of pi = %.14f\n", p_approx);
    printf("                 M_PI = %.14f\n", M_PI);//4.0 * atan(1.0));

    return 0;
}
