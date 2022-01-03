/*
Use bubble sort to sort a list of ints.
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// for random list, 0 <= keys < RMAX
const int RMAX = 100;

void bubble_sort(int *, int );
void odd_even_sort(int *, int );

//--------------------------------
int main(int argc, char* argv[]) {
   int  n;
   char g_i;
   int* a;

    n = 10;
    if (argc > 1)
        n = atoi(argv[1]);

    a = malloc(n * sizeof(int));

    // generate random list
    srand(time(NULL));
    for (int i = 0; i < n; i++)
        a[i] = rand() % RMAX;
    
    // print_list
    for (int i = 0; i < n; i++)
        printf("%2d ", a[i]);
    printf("before\n");
    
    //bubble_sort(a, n);
    odd_even_sort(a, n);
    
    // print_list
    for (int i = 0; i < n; i++)
        printf("%2d ", a[i]);
    printf("after\n");
   
    free(a);
    return 0;
}

//---------------
void bubble_sort(int *a, int  n) {
    int len, i, temp;

    for (len = n; len >= 2; len--)
        for (i = 0; i < len-1; i++)
            if (a[i] > a[i+1]) {
                // swap a[i], a[i+1]
                temp = a[i];
                a[i] = a[i+1];
                a[i+1] = temp;
            }
}

//---------------
void odd_even_sort(int *a, int  n) {
    int phase, i, temp;

    for (phase = 0; phase < n; phase++) 
        if (phase % 2 == 0) {   /* even phase */
            for (i = 1; i < n; i += 2) 
                if (a[i-1] > a[i]) {
                    temp = a[i];
                    a[i] = a[i-1];
                    a[i-1] = temp;
                }
        } else {                /* odd phase */
            for (i = 1; i < n-1; i += 2)
                if (a[i] > a[i+1]) {
                    temp = a[i];
                    a[i] = a[i+1];
                    a[i+1] = temp;
                }
        }
}
