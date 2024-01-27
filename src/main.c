#include <stdio.h>
#include "array_utils.h"
#include "bsort.h"

int main(int argc, int **argv) {
    int n = 13;
    int arr[] = {12, 14, 20, 12, 2, 1, 5, 0, 3, 2, 5, 7, 8};

    bucket_sort(arr, n);

    print_array(arr, n);
}
