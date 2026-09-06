#include <stdio.h>

int main() {
	int arr[5];
	int *p =arr;
	for(int i=0; i<5;i++){
		arr[i]=i+1;
	}
	printf("Each element by pointers\n");
	for(int i=0; i<5; i++){
		printf("%d  \n", *(p + i));
	}
	
	printf("Modifing using pointers\n");
	for(int i =0; i<5; i++){
		*(p+i) = *(p+i)*10;
	}
	printf("Printing modified array\n");
 	for(int i=0; i<5; i++){
		printf("%d\n", *(p+i));
	}

	printf("Printing arry using its name\n");
	for(int i=0; i<5; i++){
		printf("%d\n", arr[i]);
	}

	return 0;
}
