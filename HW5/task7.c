#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

void *aligned_malloc(size_t size, size_t alignment) {
    if (alignment == 0 || (alignment & (alignment - 1)) != 0) {
        return NULL;
    }

    if (alignment < sizeof(void *)) {
        alignment = sizeof(void *);
    }

    if (size > SIZE_MAX - alignment - sizeof(void *)) {
        return NULL;
    }

    void *raw = malloc(size + alignment - 1 + sizeof(void *));
    if (raw == NULL) {
        return NULL;
    }

    uintptr_t addr = (uintptr_t)raw + sizeof(void *);
    uintptr_t aligned = (addr + alignment - 1) & ~(uintptr_t)(alignment - 1);

    ((void **)aligned)[-1] = raw;

    return (void *)aligned;
}

void aligned_free(void *ptr) {
    if (ptr == NULL) {
        return;
    }

    free(((void **)ptr)[-1]);
}

int main() {
    int *arr;
    int n;
    size_t alignment;

    printf("Enter the number of elements: ");
    scanf("%d", &n);

    if (n <= 0) {
        printf("Number of elements must be positive!\n");
        return 1;
    }

    printf("Enter the alignment (power of 2): ");
    scanf("%zu", &alignment);

    arr = (int *)aligned_malloc(n * sizeof(int), alignment);

    if (arr == NULL) {
        printf("Aligned memory allocation failed!\n");
        return 1;
    }

    printf("Address of the array: %p\n", arr);
    printf("Address %% alignment: %lu\n", (unsigned long)((uintptr_t)arr % alignment));

    printf("Enter %d integers: ", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    printf("Array: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    aligned_free(arr);

    return 0;
}
