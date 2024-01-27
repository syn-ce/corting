#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../src/array_utils.h"
#include "../src/bsort.h"

bool test1f() {
    int arr[] = {0};
    int arr_sorted[] = {0};
    return bucket_sort_equals(arr, arr_sorted, 1);
}

bool test2f() {
    int arr[] = {12, 14, 20, 12, 2, 1, 5, 0, 3, 2, 5, 7, 8};
    int arr_sorted[] = {0, 1, 2, 2, 3, 5, 5, 7, 8, 12, 12, 14, 20};
    return bucket_sort_equals(arr, arr_sorted, 13);
}

bool test3f() {
    int arr[] = {-1};
    int arr_sorted[] = {-1};
    return bucket_sort_equals(arr, arr_sorted, 1);
}

bool test4f() {
    int arr[] = {3,4,2,100,3,2,5,2,2,6,2,2,2,2,59,2,2,71};
    int arr_sorted[] = {2,2,2,2,2,2,2,2,2,2,3,3,4,5,6,59,71,100};
    return bucket_sort_equals(arr, arr_sorted, 10);
}


bool testr(int i) {
    int n = rand() % (rand() % 10000) + 1;
    bool contains_neg_values = rand() % 1000 < 500;
    int *arr = malloc(n * sizeof(int));
    int *arr_sorted = malloc(n * sizeof(int));
    if (arr == NULL || arr_sorted == NULL) fprintf(stderr, "Malloc failed."), exit(0);

    for (int i = 0; i < n; i++) {
        if (contains_neg_values) arr[i] = rand() % 150 + i * 100 - (rand() % 300 + i * 100);
            else arr[i] = rand() % 150 + i * 100;
        arr_sorted[i] = arr[i];
    }

    qsort(arr_sorted, n, sizeof(int), int_compare);

    bool passed = bucket_sort_equals(arr, arr_sorted, n);

    free(arr);

    return passed;
}

bool (*testsf[])() = {test1f, test2f, test3f, test4f};

void test_bucket_sort() {
    srand(time(NULL));   // Initialization of random

    int fixed_tests = 4;
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
        if (testr(i)) {
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
