#pragma once

//Colin Keilbach

//Prints board
const void displayBoard(int board[], int height, int width, char pieces[][2]);

//Prints pieces
const void printPiece(int board[], int index, char pieces[][2]);

//Outputs Win
void displayWin(int player);