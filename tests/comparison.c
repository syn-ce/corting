#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../src/array_utils.h"
#include "../src/bsort.h"

// Comparing performance of Quicksort and Bucketsort.

int main(int argc, char **argv) {
    srand(time(NULL));
    int n = 10000000;
    int max_num = 255;
    if (argc > 1) n = atoi(argv[1]);
    if (argc > 2) max_num = atoi(argv[2]);

    max_num++;

    int *arr_quick = malloc(n * sizeof(int));
    int *arr_buck = malloc(n * sizeof(int));
    if (arr_quick == NULL || arr_buck == NULL) fprintf(stderr, "Malloc failed.\n"), exit(0);

    printf("Generating array with %d elements\n", n);
    for (int i = 0; i < n; i++) {
        arr_quick[i] = rand() % max_num;
        arr_buck[i] = arr_quick[i];
    }

    printf("Sorting with quicksort...\n");
    clock_t begin = clock();
    qsort(arr_quick, n, sizeof(int), int_compare);
    clock_t end = clock();

    double time_quick = (double) (end - begin) / CLOCKS_PER_SEC;

    printf("Sorting with bucketsort...\n");
    begin = clock();
    bucket_sort(arr_buck, n);
    end = clock();

    double time_bucket = (double) (end - begin) / CLOCKS_PER_SEC;

    printf("Time quick: %lf\n", time_quick);
    printf("Time bucket: %lf\n", time_bucket);

    free(arr_quick);
    free(arr_buck);
}
