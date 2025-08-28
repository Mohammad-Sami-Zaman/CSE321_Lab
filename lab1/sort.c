#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void sort(int size_arr, int arr_in[]) {
    int j = 1;

    while (j < size_arr) {
        int arr_val = arr_in[j];
        int k=j-1;
        while (k >= 0 && arr_val > arr_in[k]) {
            arr_in[k+1] =arr_in[k];
            k = k - 1;
        }
        arr_in[k+1]=arr_val;
        j = j+1;
    }

    printf("In descending order sorted array : \n");
    for (int i = 0; i <= size_arr - 1; i++) {
        printf("%d ", arr_in[i]);
    }
    printf("\n");
    printf("\n");
    printf("\n");
}

int main(int argc, char *argv[]) {

    int size_arr = argc - 1;
    int arr_in[size_arr];
    int i = 1;

    while (i < argc) {
        arr_in[i - 1] = atoi(argv[i]);
        i= i+1;
    }

    sort(size_arr, arr_in); 

    return 0;
}






