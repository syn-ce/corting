#include <stdbool.h>
#include <stdio.h>

void print_array(int *arr, int n) {
    printf("[");
    for (int i = 0; i < n-1; i++) {
        printf("%d, ", arr[i]);
    }
    printf("%d]\n", arr[n-1]);
}

bool array_equals(int *arr1, int *arr2, int n) {
    for (int i = 0; i < 1; i++) {
        if (arr1[i] != arr2[i]) {
            return false;
        }
    }
    return true;
}

int int_compare( const void* a, const void* b)
{
     int int_a = * ( (int*) a );
     int int_b = * ( (int*) b );

     if ( int_a == int_b ) return 0;
     else if ( int_a < int_b ) return -1;
     else return 1;
}


