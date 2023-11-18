#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Naive BucketSort in C.

// Dynamic array
struct Bucket {
    int *array;
    int elements;
    int capacity;
};

typedef struct Bucket Bucket;

Bucket *create_bucket() {
    Bucket *a = malloc(sizeof(Bucket));
    if (a == NULL) fprintf(stderr, "Malloc failed.\n"), exit(0);
    a->capacity = 4;
    int *arr = malloc(a->capacity * sizeof(int));
    if (arr == NULL) fprintf(stderr, "Malloc failed.\n"), exit(0);
    a->array = arr;
    a->elements = 0;
    return a;
}

void bucket_push(Bucket *bu, int element) {
    if (bu->capacity == bu->elements) { // Double size of array
        int *arr = malloc(bu->capacity * 2 * sizeof(int));
        if (arr == NULL) fprintf(stderr, "Malloc failed.\n"), exit(0);
        for (int i = 0; i < bu->capacity; i++) { // Copy old elements
            arr[i] = bu->array[i];
        }
        free(bu->array);
        bu->array = arr;
    }

    bu->array[bu->elements] = element;
    bu->elements++;
}

void bucket_sort(int *array, int n) { // Try to compensate for negative values by adding the smallest negative value to indices 
    if (n == 0) return;

    int min_val = array[0];
    int max_val = array[0];

    for (int i = 0; i < n; i++) {
        if (array[i] > max_val) max_val = array[i];
        if (array[i] < min_val) min_val = array[i];
    }
    
    int offset = 0; 
    if (min_val < 0) {
        // Check bounds
        if (max_val > 0 && abs(min_val) > INT_MAX - max_val) fprintf(stderr, "BucketSort overflows for given array with negative values."), exit(0);
        offset = abs(min_val);
    }
    

    int *arr_copy = malloc(n * sizeof(int));
    if (arr_copy == NULL) fprintf(stderr, "Malloc failed.\n"), exit(0);
    for (int i = 0; i < n; i++) {
        arr_copy[i] = array[i];
    }

    max_val++; // Length of array will be max value + 1

    // Allocate array of buckets
    Bucket **buckets = malloc((max_val + offset) * sizeof(Bucket));
    if (buckets == NULL) fprintf(stderr, "Malloc failed.\n"), exit(0);
    for (int i = 0; i < max_val + offset; i++) {
        buckets[i] = create_bucket();
    }

    // Put elements into buckets
    for (int i = 0; i < n; i++) {
        bucket_push(buckets[array[i] + offset], i); 
    }

    // Final sort
    int ind = 0;
    for (int i = 0; i < max_val + offset; i++) {
        Bucket *bu = buckets[i];
        for (int j = 0; j < bu->elements; j++) {
            array[ind] = arr_copy[bu->array[j]];
            ind++;
        }
        free(bu);
    }
    free(arr_copy);
    free(buckets);
}

