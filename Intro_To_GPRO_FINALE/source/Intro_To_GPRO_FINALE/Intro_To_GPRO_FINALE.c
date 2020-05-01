
#include <stdlib.h>

//Displays board based off of height and width specifications
void displayBoard(int board, int height, int width){

	system("CLS"); //Clear screen to make everything look nice

	//Starts by showing the line of X values
	printf("\n X:");
	for (int i = 0; i < width; i++) {
		printf("--%d--", i + 1); //Prints i + 1 so that it runs X:--1----2--...
	}
	printf("\nY\n"); //Prints Y for Y values
	//Make rows
	for (int i = 0; i < height; i++) {
		print("%d ", i); // Prints Y values
		for (int j = 0; j < width; j++) {
			//printf(" %c%c ", SPACE); //PRINT SPACE===============================================================================================================================================================
			if (j != width - 1) { //Line for grid
				printf("|");
			}
		}
		if (i != height - 1) {
			printf("\n| ---------------------------------------\n"); //Creates space between the rows
		}
		else {
			printf("\n\n"); //Space to make it look nice
		}
	}
}