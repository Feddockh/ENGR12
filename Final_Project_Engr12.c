#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

int menu_selections(int n, char[][20], char[][20]);
int randnum(int, int);
int timestamp_generator(int[][3]);
void pickup_time_generator(int, int[][3], int[][3]);
void sorting(int [][3], int [][3], int [][3], int [][3], char [][20], char [][20], int);
void food_prep(char mealchoice[][20], int number_of_orders);

int main() {
	
	//Variables
	int number_of_options = 5, timestamp[20000][3], number_of_orders, i, ordernum, funcselect;
	int pickup_times[20000][3], check;
	char options[][20] = {"Pizza", "Burger", "Pasta", "Salad", "Tacos"}, filtered_options[][20] = {""};
	char dataselect, filename[50] = "data.txt", mealchoice[20000][20];
	FILE *pointer;
	
	//Prompt user to choose program function
	do {
	printf("Would you like to generate data (1), or sort data (2): ");
	scanf("%d", &funcselect);
	} while (funcselect != 1 && funcselect != 2);
	
	
	if (funcselect == 1) {
		//Generating data
		//Explain purpose for code
		printf("This is the data generator which is representive of the input from the user\n\n");
		
		
		//Passing info to the menu_selections function
		number_of_options = menu_selections(number_of_options, options, filtered_options);
		
		
		//Generate a day full of orders
		number_of_orders = timestamp_generator(timestamp);
		
		
		//Generate pick-up times
		pickup_time_generator(number_of_orders, pickup_times, timestamp);
		
		//Print timestamp and order
		pointer = fopen("data.txt", "w");
		for (i=0;i<number_of_orders;i++) {
			ordernum = randnum(number_of_options, 1)-1;
			printf("%02d:%02d:%02d, %10s, %02d:%02d:%02d\n", timestamp[i][2], timestamp[i][1], timestamp[i][0], filtered_options[ordernum], pickup_times[i][2], pickup_times[i][1], pickup_times[i][0]);
			fprintf(pointer, "%02d:%02d:%02d, %10s, %02d:%02d:%02d\n", timestamp[i][2], timestamp[i][1], timestamp[i][0], filtered_options[ordernum], pickup_times[i][2], pickup_times[i][1], pickup_times[i][0]);
		}
		fclose(pointer);
		
	} else if (funcselect == 2) {
		//Sorting the data
		//First we check to see if they want to pull from the same filename
		do {
			printf("Would you like to pull from \"data.txt\"?\n");
			printf("Please select \"Y\" or \"N\": ");
			scanf(" %c", &dataselect);
		} while (dataselect != 'Y' && dataselect != 'N');
		
		//If they want a different file then we let them enter that
		if (dataselect == 'N') {
			do {
				printf("Please enter the name of the data file: ");
				scanf(" %s", filename);
				pointer = fopen(filename, "r");
			} while (pointer == NULL);
		} else if (dataselect == 'Y') {
			pointer = fopen("data.txt", "r");
		} else printf("Error");
		
		//Then pull in the data
		i=0;
		for (;;) {
			check = fscanf(pointer, "%d:%d:%d, %s %d:%d:%d", &timestamp[i][2], &timestamp[i][1], &timestamp[i][0], mealchoice[i], &pickup_times[i][2], &pickup_times[i][1], &pickup_times[i][0]);
			if (check == EOF) break;
			printf("%02d:%02d:%02d, %10s %02d:%02d:%02d\n", timestamp[i][2], timestamp[i][1], timestamp[i][0], mealchoice[i], pickup_times[i][2], pickup_times[i][1], pickup_times[i][0]);
			i++;
		}
		number_of_orders = i;
		fclose(pointer);
		
		//Now we can begin sorting
		int timestamp_sorted[number_of_orders][3], pickup_times_sorted[number_of_orders][3];
		char mealchoice_sorted[number_of_orders][20];
		sorting(pickup_times, pickup_times_sorted, timestamp, timestamp_sorted, mealchoice, mealchoice_sorted, number_of_orders);
		
		//Print the sorted list to screen and to datasorted file
		pointer = fopen("datasorted.txt", "w");
		printf("\n\nThe following list is in order by pickup time\n");
		for (int i=0;i<number_of_orders;i++) {
			fprintf(pointer, "%02d:%02d:%02d, %10s %02d:%02d:%02d\n", timestamp_sorted[i][2], timestamp_sorted[i][1], timestamp_sorted[i][0], mealchoice_sorted[i], pickup_times_sorted[i][2], pickup_times_sorted[i][1], pickup_times_sorted[i][0]);
			printf("%02d:%02d:%02d, %10s %02d:%02d:%02d\n", timestamp_sorted[i][2], timestamp_sorted[i][1], timestamp_sorted[i][0], mealchoice_sorted[i], pickup_times_sorted[i][2], pickup_times_sorted[i][1], pickup_times_sorted[i][0]);
		}
		fclose(pointer);
		
		food_prep(mealchoice,number_of_orders);

	} else printf("Error\n");
	
	return 0;
}

//Function for determining menu selection
int menu_selections(int n, char options[][20], char filtered_options[][20]) {
	
	int i, j, k;
	char available;
	
	//Display the menu options
	printf("The following menu options are: \n%s", options[0]);
	for(i=1;i<n;i++) {
		printf(", %s", options[i]);
	}
	printf("\n");
	
	
	//Prompting the user to enter which menu options will be available
	//Outer for loop is to ask user about each options
	j = 0;
	for(i=0;i<n;i++) {
		
		//Asking the user if an option is available and error checking reply
		do {
			printf("Will \"%s\" be available? Please enter a \"Y\" or \"N\": ", options[i]);
			scanf(" %c", &available);
		} while (available != 'Y' && available != 'N');
		
		//If an option is available, move it to the filter_options array
		if (available == 'Y') {
			
			//Inner for loop is needed to transfer strings letter by letter
			for (k=0;k<strlen(options[i]);k++) {
				filtered_options[j][k] = options[i][k];
			}
		j++;
		}
	}
	
	//Display the filtered_options to the user
	printf("Today's menu is: %s", filtered_options[0]);
	for(i=1;i<j;i++) {
		printf(", %s", filtered_options[i]);
		
	}
	printf("\n");
	
	//return the new number of options
	n = i;
	
	return n;
}

//Function for generating random numbers within a range
int randnum(int upper, int lower) {
	int x = (rand()%(upper-lower+1))+lower;
	return x;
}

//Function for calculating the timestamp
int timestamp_generator(int timestamp[][3]) {
	
	int i=0;
	int seconds=0, minutes=0, hours=1;
	
	//Using a forever loop to continue to increment seconds according the function
	for (;;) {
		//Using a function depending on the hour to account for high-traffic times
		float multiplier = (.006*pow((hours-12.5),2))+.4;
		int upper = 60.*multiplier;
		
		//Seconds is incremented by the random function with the upper bound dependent on the function
		seconds += randnum(upper, 0);
		
		if (seconds > 60) {
			seconds -= 60;
			minutes++;
		}
		
		if (minutes > 60) {
			minutes -= 60;
			hours++;
		}
		
		timestamp[i][0] = seconds;
		timestamp[i][1] = minutes;
		timestamp[i][2] = hours;
		
		if (i>=20000) {
			printf("ERROR: To many datapoints\n");
			break;
		}
		
		//Breaking loop when hours reaches 24
		if (hours>=24) break;
		i++;
	}
	
	return i;
}


//Function for determining estimated arrival time
void pickup_time_generator(int n, int pickup_times[][3], int timestamp[][3]) {
	
	//Multiplier modfies the randomly generated integer to fit it to predicted trend
	float multiplier, added_time;
	
	//For loop builds the array with semi-randomized pickup times ranging from 15 to 180 minutes in advance
	for (int i=0;i<n;i++) {
		multiplier = (randnum(100, 1))/100.0;
		added_time = 15. * ceil(randnum(12, 1) * multiplier);
		
		pickup_times[i][0] = 0;
		pickup_times[i][1] = ceil(timestamp[i][1]/15)*15+15 + added_time;
		//printf("%d\n", pickup_times[i][1]);
		
		pickup_times[i][2] = timestamp[i][2];
		while (pickup_times[i][1] >= 60) {
			pickup_times[i][1] -= 60;
			pickup_times[i][2] += 1;
		}
		
		if (pickup_times[i][2] > 24) {
			pickup_times[i][2] -= 24;
		}
		
	}
	
}



void sorting(int A[][3], int A_sorted[][3], int B[][3], int B_sorted[][3], char C[][20], char C_sorted[][20], int n) {
	
	//A_row_trans is used to signify which row in the A colomn is being moved
	int A_row_trans;
	int A_seconds, A_sorted_seconds;
	
	
	//Outermost for loop is used to construct the B array with every interation
	for (int i=0;i<n;i++) {
		
		//Temporarily set the next value in the B array to the first row in the A array
		A_sorted[i][0] = A[0][0];
		A_sorted[i][1] = A[0][1];
		A_sorted[i][2] = A[0][2];
		
		B_sorted[i][0] = B[0][0];
		B_sorted[i][1] = B[0][1];
		B_sorted[i][2] = B[0][2];
		
		for (int c=0;c<20;c++) {
			C_sorted[i][c] = C[i][c];
		}
		
		A_row_trans = 0;
		
		//Scan through array A and update A_sorted[i] with the lowest value, also records the row in the A column being copied as A_row_trans
		for (int j=1;j<(n-i);j++) {
			
			A_seconds = A[j][0] + A[j][1]*60 + A[j][2]*3600;
			A_sorted_seconds = A_sorted[i][0] + A_sorted[i][1]*60 + A_sorted[i][2]*3600;
			
			if (A_sorted_seconds > A_seconds) {
				A_sorted[i][0] = A[j][0];
				A_sorted[i][1] = A[j][1];
				A_sorted[i][2] = A[j][2];
				
				B_sorted[i][0] = B[j][0];
				B_sorted[i][1] = B[j][1];
				B_sorted[i][2] = B[j][2];
				
				for (int c=0;c<20;c++) {
					C_sorted[i][c] = C[j][c];
				}
				
				A_row_trans = j;
			}
			
		}
		
		//Moves everything below the row in the A colomn being copied up one row
		for (int k=A_row_trans;k<(n-i-1);k++) {
			
			A[k][0] = A[k+1][0];
			A[k][1] = A[k+1][1];
			A[k][2] = A[k+1][2];
			
			B[k][0] = B[k+1][0];
			B[k][1] = B[k+1][1];
			B[k][2] = B[k+1][2];
			
			
			for (int c=0;c<20;c++) {
				C[k][c] = C[k+1][c];
			}
			
		}
		
	}
	
}


//Function for counting number of food items that need to be prepared
void food_prep(char mealchoice[][20], int number_of_orders){
	
	int countpizza=0,countburger=0,countpasta=0,countsalad=0,counttaco=0,i;

	for (i=0;i<number_of_orders;i++){
	
			if (mealchoice[i][0]=='P'){
				if(mealchoice[i][1]=='i'){
					countpizza=countpizza+1;
				}
				else if(mealchoice[i][1]=='a'){
					countpasta=countpasta+1;
				}
			}
			else if(mealchoice[i][0]=='S'){
				countsalad=countsalad+1;
			}
			else if(mealchoice[i][0]=='T'){
				counttaco=counttaco+1;
			}
			else if (mealchoice[i][0]=='B'){
			countburger=countburger+1;
		}
	}
	printf("\n\nThe number of Pizzas that need to be prepared today is %d\nThe number of Burgers that need to be prepared today is %d\nThe number of Pasta dishes that need to be prepared today is %d\nThe number of Salads that need to be prepared today is %d\nThe number of Tacos that need to be prepared today is %d", countpizza,countburger,countpasta,countsalad,counttaco);
}


