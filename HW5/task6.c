#include <stdio.h>
#include <stdlib.h>  
#include <string.h>  
void *my_realloc(void *ptr, size_t old_size, size_t new_size) {
    // No old block, behave like malloc()
    if (ptr == NULL) {
        return malloc(new_size);
    }

    if (new_size == 0) {
        free(ptr);
        return NULL;
    }

    void *new_ptr = malloc(new_size);

    if (new_ptr == NULL) {
        return NULL;
    }

    size_t copy_size = old_size;
    if (new_size < old_size) {
        copy_size = new_size;
    }
    memcpy(new_ptr, ptr, copy_size);

    free(ptr);

    return new_ptr;
}

int main() {
    int *arr;
    int n;
    int new_n;

    printf("Enter the number of elements: ");
    scanf("%d", &n);

    if (n <= 0) {
        printf("Number of elements must be positive!\n");
        return 1;
    }

    arr = (int *)malloc(n * sizeof(int));

    if (arr == NULL) {
        printf("Initial memory allocation failed!\n");
        return 1;
    }

    printf("Enter %d integers: ", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    printf("Enter the new number of elements: ");
    scanf("%d", &new_n);

    if (new_n <= 0) {
        printf("New number of elements must be positive!\n");
        free(arr);
        return 1;
    }

    int *new_arr = (int *)my_realloc(arr, n * sizeof(int), new_n * sizeof(int));

    if (new_arr == NULL) {
        printf("Memory reallocation failed!\n");
        free(arr);  // Free the original memory if my_realloc fails
        return 1;
    }

    if (new_n > n) {
        printf("Enter %d more integers: ", new_n - n);
        for (int i = n; i < new_n; i++) {
            scanf("%d", &new_arr[i]);
        }
    }

    printf("Array after resizing: ");
    for (int i = 0; i < new_n; i++) {
        printf("%d ", new_arr[i]);
    }
    printf("\n");

    free(new_arr);

    return 0;
}
