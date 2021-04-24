#include <stdio.h>
#include <stdlib.h>
#include <math.h>


//This code should generate a delimited 2 column dataset
//This code has been modified to generate a 1 column dataset

int main() {
	
	FILE *pointer;
	char filename[50];
	int length, i;
	char correct = 'N';
	
	//Confirm the user-entered file destination
	do {
		printf("Please enter a file destination: ");
		scanf(" %s", filename);
		printf("Please enter a file length: ");
		scanf("%d", &length);
		//Check for existing versions to avoid overwriting
		pointer = fopen(filename, "r");
		if (pointer != NULL) {
			printf("Warning: this may overwrite an existing file\n");
		}
		printf("Is \"%s\" with %d rows correct? (Y/N): ", filename, length);
		scanf(" %c", &correct);
	} while (correct != 'Y');
	
	//Close and then reopen with writing pointer
	fclose(pointer);
	pointer = fopen(filename, "w");
	
	//Print to the file and to the console
	for(i=0;i<length;i++) {
		//printf("%12.4f, %12.4f\n", rand()/100., rand()/100.);
		//fprintf(pointer, "%12.4f, %12.4f\n", rand()/100., rand()/100.);
		printf("%12.4f\n", rand()/100.);
		fprintf(pointer, "%12.4f\n", rand()/100.);
	}
	
	fclose(pointer);
	
	return 0;
}

