
#include <stdlib.h>
#include <stdio.h>

//Colin Keilbach

//Prints Piece when needed
const void printPiece(int board[], int index, char pieces[][2]) {

	//Gets space type
	int currentSpace = 0;
	currentSpace = board[index];

	//Prints the value for that space
 	printf(" %c%c ", pieces[currentSpace][0], pieces[currentSpace][1]);

}

//Displays board based off of height and width specifications
const void displayBoard(int board[], int height, int width, char pieces[][2]){

	system("CLS"); //Clear screen to make everything look nice

	//Starts by showing the line of X values
	printf("\n X");
	for (int i = 0; i < width; i++) {
		printf("--%d--", i + 1); //Prints i + 1 so that it runs X--1----2--...
	}
	printf("\nY\n"); //Prints Y for Y values

	//Make rows
	for (int i = 0; i < height; i++) {
		printf("%d ", i + 1); // Prints Y values
		for (int j = 0; j < width; j++) {

			//prints space
			printPiece(board, (i * height + j), pieces);

			if (j != width - 1) { //Line for grid
				printf("|");
			}
		}

		//Makes sure that it only prints the line in between rows
		if (i != height - 1) {
			printf("\n| ---------------------------------------\n"); //Creates space between the rows
		}
		else {
			printf("\n\n"); //Space to make it look nice
		}
	}
}

void displayWin(int player) {
	printf("Player %d Wins!!", player);
}