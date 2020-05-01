#include "Intro_To_GPRO_FINALE/Intro_To_GPRO_FINALE.h"

int main()
{
	char pieces[3][2] = {
		' ', ' ',
		'B', 'B',
		'W', 'W'
	};

	int board[8][8];

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			board[i][j] = 0;
		}
	}


	displayBoard(&board, 8, 8, &pieces);
}