#include <stdio.h>
#include <stdlib.h>
#include <math.h>


int main() {
	
	FILE *pointer;
	float A[50], B[50];
	int i,j,k,l;
	
	pointer = fopen("data.txt", "r");
	
	for (i=0;i<50;i++) {
		fscanf(pointer, "%f", &A[i]);
	}
	
	fclose(pointer);
	
	//Initial printout
	printf("\tInitial\t\tSorted\n");
	for (i=0;i<50;i++) {
		B[i] = 0.0;
		printf("A[%2d] = %10f, B[%2d] = %10f\n", i, A[i], i, B[i]);
	}
	printf("\n\n");
	
	
	//Sorting code
	
	//A_row_trans is used to signify which row in the A colomn is being moved
	int A_row_trans;
	
	//Outermost for loop is used to construct the B array with every interation
	for (i=0;i<50;i++) {
		
		//Temporarily set the next value in the B array to the first row in the A array
		B[i] = A[0];
		A_row_trans = 0;
		
		//Scan through array A and updates B[i] with the lowest value, also records the row in the A column being copied as A_row_trans
		for (j=1;j<(50-i);j++) {
			if (B[i] > A[j]) {
				B[i] = A[j];
				A_row_trans = j;
			}
		}
		
		//Moves everything below the row in the A colomn being copied up one row
		for (k=A_row_trans;k<(50-i);k++) {
			A[k] = A[k+1];
		}
		
		//Print statements
		printf("\tInitial\t\tSorted\n");
		for(l=0;l<50;l++) {
			printf("A[%2d] = %10f, B[%2d] = %10f\n", l, A[l], l, B[l]);
		}
		printf("\nA[%d] = %10f was moved to B[%d], and A[%d] was moved up to A[%d]\n\n\n", A_row_trans, B[i], i, (A_row_trans+1), A_row_trans);
	}


	return 0;
}

