#include <stdbool.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "../src/bsort.h"

void print_array(int *arr, int n) {
    printf("[ ");
    for (int i = 0; i < n-1; i++) {
        printf("%d, ", arr[i]);
    }
    printf("%d ]\n", arr[n-1]);
}

int compare_int( const void* a, const void* b)
{
     int int_a = * ( (int*) a );
     int int_b = * ( (int*) b );

     if ( int_a == int_b ) return 0;
     else if ( int_a < int_b ) return -1;
     else return 1;
}

bool test(int *arr, int *arr_sorted, int n) {
    bucket_sort(arr, n);
    for (int i = 0; i < 1; i++) {
        if (arr[i] != arr_sorted[i]) {
            printf("SHOULD: ");
            print_array(arr_sorted, n);
            printf("WAS: ");
            print_array(arr, n);
            return false;
        }
    }
    return true;
}

bool test1f() {
    int arr[] = {0};
    int arr_sorted[] = {0};
    return test(arr, arr_sorted, 1);
}

bool test2f() {
    int arr[] = {12, 14, 20, 12, 2, 1, 5, 0, 3, 2, 5, 7, 8};
    int arr_sorted[] = {0, 1, 2, 2, 3, 5, 5, 7, 8, 12, 12, 14, 20};
    return test(arr, arr_sorted, 13);
}

bool test3f() {
    int arr[] = {-1};
    int arr_sorted[] = {-1};
    return test(arr, arr_sorted, 1);
}


bool testr() {
    int n = rand() % 3000 + 1;
    bool contains_neg_values = rand() % 1000 < 500;
    int *arr = malloc(n * sizeof(int));
    int *arr_sorted = malloc(n * sizeof(int));
    if (arr == NULL || arr_sorted == NULL) fprintf(stderr, "Malloc failed."), exit(0);

    for (int i = 0; i < n; i++) {
        if (contains_neg_values) arr[i] = rand() % 100000 - (rand() % 200000);
            else arr[i] = rand() % 100000;
        arr_sorted[i] = arr[i];
    }

    qsort(arr_sorted, n, sizeof(int), compare_int);

    bool passed = test(arr, arr_sorted, n);

    free(arr);

    return passed;
}

bool (*testsf[])() = {test1f, test2f, test3f};

void test_bucket_sort() {
    srand(time(NULL));   // Initialization of random

    int fixed_tests = 3;
    int fixed_passed = 0;
    int random_tests = 100;
    int random_passed = 0;

    printf("\nStarting tests:\n");
    for (int i = 0; i < fixed_tests; i++) {
        if (testsf[i]()) {
        fixed_passed++;
        printf("PASSED ");
        } else {
            printf("FAILED");
        }
        printf(" TEST %d/%d\n", i+1, fixed_tests);
    }

    printf("\nStarting random tests:\n");
    for (int i = 0; i < random_tests; i++) {
        if (testr()) {
            random_passed++;
            printf("PASSED");
        } else {
            printf("FAILED");
        }
        printf(" RANDOM TEST %d/%d\n", i+1, random_tests);
    }

    printf("\n");
    printf("TOTAL FIXED PASSED: %d/%d\n", fixed_passed, fixed_tests);
    printf("TOTAL FIXED FAILED: %d/%d\n", fixed_tests - fixed_passed, fixed_tests);
    printf("\n");
    printf("TOTAL RANDOM PASSED: %d/%d\n", random_passed, random_tests);
    printf("TOTAL RANDOM FAILED: %d/%d\n", random_tests - random_passed, random_tests);
    printf("\n");
    printf("TOTAL PASSED: %d/%d\n", fixed_passed + random_passed, fixed_tests + random_tests);
    printf("TOTAL FAILED: %d/%d\n", fixed_tests - fixed_passed + random_tests - random_passed, fixed_tests + random_tests);

}

int main(int argc, char **argv) {
    test_bucket_sort();
}
