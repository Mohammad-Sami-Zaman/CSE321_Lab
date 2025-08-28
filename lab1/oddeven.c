#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void oddEven(int size_arr, int arr_in[]) {
    printf("OddEvenCheck:\n");
    int j = 0;
    while(j <= size_arr - 1) {
        if (arr_in[j] % 2 == 0) {
            printf("%d is Even\n", arr_in[j]);
        } 
        else {
            printf("%d is Odd\n", arr_in[j]);
        }
    j = j+1;
    }
}


int main(int argc, char *argv[]){
    int size_arr = argc - 1;
    int arr_in[size_arr];
    int i = 0;
    while (i <= argc - 1) {
        arr_in[i - 1] = atoi(argv[i]);
        i = i + 1;
    }
    oddEven(size_arr, arr_in);
    return 0;
}






