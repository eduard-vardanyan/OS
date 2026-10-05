#include <stdio.h>
#include <stdlib.h>

int main() {
    char **arr;
    int initial_size = 3;
    int new_size = 5;

    arr = (char **)malloc(initial_size * sizeof(char *));

    if (arr == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }

    for (int i = 0; i < initial_size; i++) {
        arr[i] = (char *)malloc(51 * sizeof(char));
        if (arr[i] == NULL) {
            printf("Memory allocation failed!\n");
            for (int j = 0; j < i; j++) {
                free(arr[j]);  
            }
            free(arr);
            return 1;
        }
    }

    printf("Enter %d strings: ", initial_size);
    for (int i = 0; i < initial_size; i++) {
        scanf("%50s", arr[i]);
    }

    printf("Entered strings: ");
    for (int i = 0; i < initial_size; i++) {
        printf("%s ", arr[i]);
    }
    printf("\n");

    char **new_arr = (char **)realloc(arr, new_size * sizeof(char *));

    if (new_arr == NULL) {
        printf("Memory reallocation failed!\n");
        for (int i = 0; i < initial_size; i++) {
            free(arr[i]);  
        }
        free(arr);
        return 1;
    }

    for (int i = initial_size; i < new_size; i++) {
        new_arr[i] = (char *)malloc(51 * sizeof(char));
        if (new_arr[i] == NULL) {
            printf("Memory allocation failed!\n");
            for (int j = 0; j < i; j++) {
                free(new_arr[j]);  
            }
            free(new_arr);
            return 1;
        }
    }

    printf("Enter %d more strings: ", new_size - initial_size);
    for (int i = initial_size; i < new_size; i++) {
        scanf("%50s", new_arr[i]);
    }

    printf("All strings: ");
    for (int i = 0; i < new_size; i++) {
        printf("%s ", new_arr[i]);
    }
    printf("\n");

    for (int i = 0; i < new_size; i++) {
        free(new_arr[i]);
    }
    free(new_arr);

    return 0;
}
