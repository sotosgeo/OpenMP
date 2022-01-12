/*
This program estimates the value of pi, by using a Monte Carlo area simulation.

*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#ifdef _OPENMP
#include <omp.h>
#endif



int main(int argc, char *argv[]) {


    int thread_count;   
    long long int total_throws, current_throw, throws_in_circle;
    double x_pos,y_pos,sum_of_squares;
    thread_count = 4;
    total_throws = 1e9; 

    //Generating a seed with time
    srand (time (NULL));

    if (argc > 1) {
        thread_count = atoi(argv[1]);
    }
    if (argc > 2) {
        total_throws = atol(argv[2]);
    }



    //----Serial Solution----
    throws_in_circle = 0;
    double t0 = omp_get_wtime();
    for (current_throw = 0; current_throw < total_throws; current_throw++) {
        x_pos = (double)rand()/RAND_MAX*2.0-1.0;
        y_pos = (double)rand()/RAND_MAX*2.0-1.0;
        sum_of_squares = x_pos * x_pos + y_pos * y_pos;
        if (sum_of_squares <= 1) throws_in_circle ++;
    }
    double serial_pi_approx = 4.0 * throws_in_circle / ((double) total_throws);
    double t1 = omp_get_wtime();



    //----Parallel Solution----
    throws_in_circle = 0;
    double t2 = omp_get_wtime();    
    #pragma omp parallel for num_threads(thread_count) \
            default(none) \
            shared(total_throws) private(x_pos,y_pos, sum_of_squares,current_throw) \
            reduction(+ : throws_in_circle) 
    for (current_throw = 0; current_throw < total_throws; current_throw++) {
        x_pos = (double)rand()/RAND_MAX*2.0-1.0;
        y_pos = (double)rand()/RAND_MAX*2.0-1.0;
        sum_of_squares = x_pos * x_pos + y_pos * y_pos;
        if (sum_of_squares <= 1) throws_in_circle ++;
    }
    double parallel_pi_approx = 4.0 * throws_in_circle / ((double) total_throws);
    double t3 = omp_get_wtime();



    //----Output----
    printf("Number of threads = %d \n", thread_count);
    printf("Total darts n = %ld \n", total_throws);
    printf("Our estimate of pi = %.14f\n", pi_approx);
    printf("The error from the actual M_PI value is: %.14f\n", M_PI - pi_approx);
    
    printf("time = %.3f sec\n", t1 - t0);

    return 0;
}
