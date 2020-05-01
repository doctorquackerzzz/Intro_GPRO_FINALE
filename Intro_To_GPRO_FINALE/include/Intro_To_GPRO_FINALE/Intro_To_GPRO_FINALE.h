#pragma once

//Colin Keilbach

//Prints board
void displayBoard(int* board[], int height, int width, char pieces[][2]);

//Prints pieces
void printPiece(int* board[], int x, int y, int height, char pieces[][2]);

//Outputs Win
void displayWin(int player);