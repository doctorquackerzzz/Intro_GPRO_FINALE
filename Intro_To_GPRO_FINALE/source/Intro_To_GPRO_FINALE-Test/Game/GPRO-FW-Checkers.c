
#include <stdio.h>
#include "Intro_To_GPRO_FINALE/Intro_To_GPRO_FINALE.h"

//-----------------------------------------------------------------------------
// DECLARATIONS

#define GS_CHECKERS_PLAYERS					2
#define GS_CHECKERS_BOARD_WIDTH				8
#define GS_CHECKERS_BOARD_HEIGHT			8

enum gs_checkers_space_state
{
	// invalid space state
	gs_checkers_space_invalid = -1,

	// states visible to both players
	gs_checkers_space_open,			// space is open
	gs_checkers_space_black,		// space is occupied by black piece
	gs_checkers_space_white,		// space is occupied by white piece
	gs_checkers_space_black_king,	// space is occupied by black king piece
	gs_checkers_space_white_king,	// space is occupied by white king piece
};
#ifndef __cplusplus
typedef		enum gs_checkers_space_state	gs_checkers_space_state;
#endif	// !__cplusplus

// checkers game state
typedef		unsigned char					gs_checkers_index;
typedef		gs_checkers_space_state			gs_checkers[GS_CHECKERS_BOARD_WIDTH][GS_CHECKERS_BOARD_HEIGHT];


#define	GS_VALIDATE_COORDINATE(x,y,w,h)			(x < w && y < h)
#define GS_CHECKERS_VALID(x,y)					GS_VALIDATE_COORDINATE(x,y,GS_CHECKERS_BOARD_WIDTH,GS_CHECKERS_BOARD_HEIGHT)
//-----------------------------------------------------------------------------

inline gs_checkers_space_state gs_checkers_getSpaceState(gs_checkers const game, gs_checkers_index const xpos, gs_checkers_index const ypos)
{
	if (GS_CHECKERS_VALID(xpos, ypos))
		return (game[xpos][ypos]);
	return gs_checkers_space_invalid;
}

inline gs_checkers_space_state gs_checkers_setSpaceState(gs_checkers game, gs_checkers_space_state const state, gs_checkers_index const xpos, gs_checkers_index const ypos)
{
	if (GS_CHECKERS_VALID(xpos, ypos))
		return (game[xpos][ypos] = state);
	return gs_checkers_space_invalid;
}

inline gs_checkers_index gs_checkers_reset(gs_checkers game)
{
	gs_checkers_index xpos, ypos, total;
	for (xpos = 0; xpos < GS_CHECKERS_BOARD_WIDTH; ++xpos)
		for (ypos = 0; ypos < GS_CHECKERS_BOARD_HEIGHT; ++ypos)
			game[xpos][ypos] = gs_checkers_space_open;
	total = (xpos * ypos);
	for (xpos = 0; xpos < 3; ++xpos)
		for (ypos = xpos % 2; ypos < GS_CHECKERS_BOARD_HEIGHT; ypos += 2)
		{
			game[xpos][GS_CHECKERS_BOARD_HEIGHT - ypos - 1] = gs_checkers_space_black;
			game[GS_CHECKERS_BOARD_WIDTH - xpos - 1][ypos] = gs_checkers_space_white;
		}
	return total;
}

//Colin's Functions
void gs_checkers_userInput(gs_checkers, int); //Gets user input

void gs_checkers_checkKings(gs_checkers); //Makes correct pieces into kings

int gs_checkers_checkWin(gs_checkers); //Checks for win

void gs_checkers_move_black(gs_checkers, int, int); //Moves Black

void gs_checkers_move_white(gs_checkers, int, int); //Moves White

void gs_checkers_move_black_king(gs_checkers, int, int); //Moves Black Kings

void gs_checkers_move_white_king(gs_checkers, int, int); //Moves White Kings

//-----------------------------------------------------------------------------
// DEFINITIONS

int launchCheckers()
{
	char gs_checkers_pieces[5][2] = {
		' ', ' ',
		'B', 'B',
		'W', 'W',
		'B', 'K',
		'W', 'K'
	};

	gs_checkers game = { 0 };

	gs_checkers_reset(game);

	int player = 0;

	do {
		displayBoard(game, GS_CHECKERS_BOARD_HEIGHT, GS_CHECKERS_BOARD_WIDTH, gs_checkers_pieces);

		gs_checkers_userInput(game, player);

		gs_checkers_checkKings(game);

		//Switch active player
		if (player == 1)
			player = 0;
		else
			player = 1;

	} while (gs_checkers_checkWin(game) == 0);

	displayBoard(game, GS_CHECKERS_BOARD_HEIGHT, GS_CHECKERS_BOARD_WIDTH, gs_checkers_pieces);

	displayWin(gs_checkers_checkWin(game));

	system("puase");

	return 0;
}

//Gets all of the user input
void gs_checkers_userInput(gs_checkers game, int player) { //player 0 = black 1 = white
	int piece_x, piece_y;

	gs_checkers_space_state piece;

	int good = 0; //used to find if the piece or move is good

	if (player == 0)
		printf("--Black's Move--\n");
	else
		printf("--White's Move--\n");

	//Find Piece
	do {
		//Get Input to find piece
		printf("Select a piece to move\nX: ");
		scanf("%d", &piece_x);
		printf("Y: ");
		scanf("%d", &piece_y);
		
		//Gets the right piece
		piece_x--;
		piece_y--;

		//Get piece state
		piece = gs_checkers_getSpaceState(game, piece_y, piece_x);
		
		//Check piece validity
		switch (piece) {
		case gs_checkers_space_open:
			good = 0;
			break;
		case gs_checkers_space_white:
			if (player == 1)
				good = 1;
			else
				good = 0;
			break;
		case gs_checkers_space_white_king:
			if (player == 1)
				good = 1;
			else
				good = 0;
			break;
		case gs_checkers_space_black:
			if (player == 0)
				good = 1;
			else
				good = 0;
			break;
		case gs_checkers_space_black_king:
			if (player == 0)
				good = 1;
			else
				good = 0;
			break;
		}

		//Print error if needed
		if (good == 0)
			printf("ERROR: Invalid Piece");
	} while (good == 0);//Run again if invalid piece

	//Runs Move Function For Piece
	switch (piece) {
	case gs_checkers_space_white:
		gs_checkers_move_white(game, piece_x, piece_y);
		break;
	case gs_checkers_space_white_king:
		gs_checkers_move_white_king(game, piece_x, piece_y);
		break;
	case gs_checkers_space_black:
		gs_checkers_move_black(game, piece_x, piece_y);
		break;
	case gs_checkers_space_black_king:
		gs_checkers_move_black_king(game, piece_x, piece_y);
		break;
	}

	gs_checkers_checkKings(game); //Sets piece that should be kinged to kings
}

void gs_checkers_checkKings(gs_checkers game) {
	for (int i = 0; i < GS_CHECKERS_BOARD_WIDTH; i++) {
		if (gs_checkers_getSpaceState(game, 0, i) == gs_checkers_space_white)
			gs_checkers_setSpaceState(game, gs_checkers_space_white_king, 0, i);
		if (gs_checkers_getSpaceState(game, 7, i) == gs_checkers_space_black)
			gs_checkers_setSpaceState(game, gs_checkers_space_black_king, 7, i);
	}
}

int gs_checkers_checkWin(gs_checkers game) {
	int black = 0, white = 0;

	for (int i = 0; i < GS_CHECKERS_BOARD_HEIGHT; i++) {
		for (int j = 0; j < GS_CHECKERS_BOARD_WIDTH; j++) {
			if (gs_checkers_getSpaceState(game, j, i) == gs_checkers_space_white)
				white++;
			if (gs_checkers_getSpaceState(game, j, i) == gs_checkers_space_black)
				black++;
		}
	}

	if (black == 0)
		return 1;
	else if (white == 0)
		return 2;
	else
		return 0;
}

void gs_checkers_move_black(gs_checkers game, int piece_x, int piece_y) {
	//Move info
	int move_x, move_y;
	gs_checkers_space_state move;

	int good = 0;//Checks if move is good

	do {
		do {
			//Get move info
			printf("Select a place to move to\nX: ");
			scanf("%d", &move_x);
			printf("Y: ");
			scanf("%d", &move_y);

			//Gets the right space
			move_x--;
			move_y--;

			move = gs_checkers_getSpaceState(game, move_y, move_x);

			if (move != gs_checkers_space_open)
				printf("ERROR: Invalid Move");
		} while (move != gs_checkers_space_open);

		//Move
		if ((move_y == piece_y + 1) && ((move_x == piece_x + 1) || (move_x == piece_x - 1))) {
			gs_checkers_setSpaceState(game, gs_checkers_space_black, move_y, move_x); //Move piece to space
			gs_checkers_setSpaceState(game, gs_checkers_space_open, piece_y, piece_x); //Clear piece's previous space
			good = 1; //Move Complete
		}

		//Jump Right
		if ((move_y == piece_y + 2) && (move_x == piece_x + 2)) {
			gs_checkers_space_state jump = gs_checkers_getSpaceState(game, piece_y + 1, piece_x + 1); //Jumped piece
			if ((jump == gs_checkers_space_white) || (jump == gs_checkers_space_white_king)) { //Check jumped piece is on opposite team
				gs_checkers_setSpaceState(game, gs_checkers_space_black, move_y, move_x); //Move piece to space
				gs_checkers_setSpaceState(game, gs_checkers_space_open, piece_y + 1, piece_x + 1); //Clear jumped piece
				gs_checkers_setSpaceState(game, gs_checkers_space_open, piece_y, piece_x); //Clear piece's previous space
				good = 1; //Move Complete
			}
		}

		//Jump Left
		if ((move_y == piece_y + 2) && (move_x == piece_x - 2)) {
			gs_checkers_space_state jump = gs_checkers_getSpaceState(game, piece_y + 1, piece_x - 1); //Jumped piece
			if ((jump == gs_checkers_space_white) || (jump == gs_checkers_space_white_king)) { //Check jumped piece is on opposite team
				gs_checkers_setSpaceState(game, gs_checkers_space_black, move_y, move_x); //Move piece to space
				gs_checkers_setSpaceState(game, gs_checkers_space_open, piece_y + 1, piece_x - 1); //Clear jumped piece
				gs_checkers_setSpaceState(game, gs_checkers_space_open, piece_y, piece_x); //Clear piece's previous space
				good = 1; //Move Complete
			}
		}
	} while (good == 0);
}

void gs_checkers_move_white(gs_checkers game, int piece_x, int piece_y) {
	//Move info
	int move_x, move_y;
	gs_checkers_space_state move;

	int good = 0;//Checks if move is good

	do {
		do {
			//Get move info
			printf("Select a place to move to\nX: ");
			scanf("%d", &move_x);
			printf("Y: ");
			scanf("%d", &move_y);

			//Gets the right space
			move_x--;
			move_y--;

			move = gs_checkers_getSpaceState(game, move_y, move_x);

			if (move != gs_checkers_space_open)
				printf("ERROR: Invalid Move");
		} while (move != gs_checkers_space_open);

		//Move
		if ((move_y == piece_y - 1) && ((move_x == piece_x + 1) || (move_x == piece_x - 1))) {
			gs_checkers_setSpaceState(game, gs_checkers_space_white, move_y, move_x); //Move piece to space
			gs_checkers_setSpaceState(game, gs_checkers_space_open, piece_y, piece_x); //Clear piece's previous space
			good = 1; //Move Complete
		}

		//Jump Right
		if ((move_y == piece_y - 2) && (move_x == piece_x + 2)) {
			gs_checkers_space_state jump = gs_checkers_getSpaceState(game, piece_y - 1, piece_x + 1); //Jumped piece
			if ((jump == gs_checkers_space_black) || (jump == gs_checkers_space_black_king)) { //Check jumped piece is on opposite team
				gs_checkers_setSpaceState(game, gs_checkers_space_white, move_y, move_x); //Move piece to space
				gs_checkers_setSpaceState(game, gs_checkers_space_open, piece_y - 1, piece_x + 1); //Clear jumped piece
				gs_checkers_setSpaceState(game, gs_checkers_space_open, piece_y, piece_x); //Clear piece's previous space
				good = 1; //Move Complete
			}
		}

		//Jump Left
		if ((move_y == piece_y - 2) && (move_x == piece_x - 2)) {
			gs_checkers_space_state jump = gs_checkers_getSpaceState(game, piece_y - 1, piece_x - 1); //Jumped piece
			if ((jump == gs_checkers_space_black) || (jump == gs_checkers_space_black_king)) { //Check jumped piece is on opposite team
				gs_checkers_setSpaceState(game, gs_checkers_space_white, move_y, move_x); //Move piece to space
				gs_checkers_setSpaceState(game, gs_checkers_space_open, piece_y - 1, piece_x - 1); //Clear jumped piece
				gs_checkers_setSpaceState(game, gs_checkers_space_open, piece_y, piece_x); //Clear piece's previous space
				good = 1; //Move Complete
			}
		}

		if (good == 0)
			printf("ERROR: Move is Invalid\n");
	} while (good == 0);
}

void gs_checkers_move_black_king(gs_checkers game, int piece_x, int piece_y) {
	//Move info
	int move_x, move_y;
	gs_checkers_space_state move;

	int good = 0;//Checks if move is good

	do {
		do {
			//Get move info
			printf("Select a place to move to\nX: ");
			scanf("%d", &move_x);
			printf("Y: ");
			scanf("%d", &move_y);

			//Gets the right space
			move_x--;
			move_y--;

			move = gs_checkers_getSpaceState(game, move_y, move_x);

			if (move != gs_checkers_space_open)
				printf("ERROR: Invalid Move");
		} while (move != gs_checkers_space_open);

		//Move
		if (((move_y == piece_y + 1) || (move_y == piece_y - 1)) && ((move_x == piece_x + 1) || (move_x == piece_x - 1))) {
			gs_checkers_setSpaceState(game, gs_checkers_space_black_king, move_y, move_x); //Move piece to space
			gs_checkers_setSpaceState(game, gs_checkers_space_open, piece_y, piece_x); //Clear piece's previous space
			good = 1; //Move Complete
		}

		//Jump Forward Right
		if ((move_y == piece_y + 2) && (move_x == piece_x + 2)) {
			gs_checkers_space_state jump = gs_checkers_getSpaceState(game, piece_y + 1, piece_x + 1); //Jumped piece
			if ((jump == gs_checkers_space_white) || (jump == gs_checkers_space_white_king)) { //Check jumped piece is on opposite team
				gs_checkers_setSpaceState(game, gs_checkers_space_black_king, move_y, move_x); //Move piece to space
				gs_checkers_setSpaceState(game, gs_checkers_space_open, piece_y + 1, piece_x + 1); //Clear jumped piece
				gs_checkers_setSpaceState(game, gs_checkers_space_open, piece_y, piece_x); //Clear piece's previous space
				good = 1; //Move Complete
			}
		}

		//Jump Forward Left
		if ((move_y == piece_y + 2) && (move_x == piece_x - 2)) {
			gs_checkers_space_state jump = gs_checkers_getSpaceState(game, piece_y + 1, piece_x - 1); //Jumped piece
			if ((jump == gs_checkers_space_white) || (jump == gs_checkers_space_white_king)) { //Check jumped piece is on opposite team
				gs_checkers_setSpaceState(game, gs_checkers_space_black_king, move_y, move_x); //Move piece to space
				gs_checkers_setSpaceState(game, gs_checkers_space_open, piece_y + 1, piece_x - 1); //Clear jumped piece
				gs_checkers_setSpaceState(game, gs_checkers_space_open, piece_y, piece_x); //Clear piece's previous space
				good = 1; //Move Complete
			}
		}

		//Jump Back Right
		if ((move_y == piece_y - 2) && (move_x == piece_x + 2)) {
			gs_checkers_space_state jump = gs_checkers_getSpaceState(game, piece_y - 1, piece_x + 1); //Jumped piece
			if ((jump == gs_checkers_space_white) || (jump == gs_checkers_space_white_king)) { //Check jumped piece is on opposite team
				gs_checkers_setSpaceState(game, gs_checkers_space_black_king, move_y, move_x); //Move piece to space
				gs_checkers_setSpaceState(game, gs_checkers_space_open, piece_y - 1, piece_x + 1); //Clear jumped piece
				gs_checkers_setSpaceState(game, gs_checkers_space_open, piece_y, piece_x); //Clear piece's previous space
				good = 1; //Move Complete
			}
		}

		//Jump Back Left
		if ((move_y == piece_y - 2) && (move_x == piece_x - 2)) {
			gs_checkers_space_state jump = gs_checkers_getSpaceState(game, piece_y - 1, piece_x - 1); //Jumped piece
			if ((jump == gs_checkers_space_white) || (jump == gs_checkers_space_white_king)) { //Check jumped piece is on opposite team
				gs_checkers_setSpaceState(game, gs_checkers_space_black_king, move_y, move_x); //Move piece to space
				gs_checkers_setSpaceState(game, gs_checkers_space_open, piece_y - 1, piece_x - 1); //Clear jumped piece
				gs_checkers_setSpaceState(game, gs_checkers_space_open, piece_y, piece_x); //Clear piece's previous space
				good = 1; //Move Complete
			}
		}
	} while (good == 0);
}

void gs_checkers_move_white_king(gs_checkers game, int piece_x, int piece_y) {
	//Move info
	int move_x, move_y;
	gs_checkers_space_state move;

	int good = 0;//Checks if move is good

	do {
		do {
			//Get move info
			printf("Select a place to move to\nX: ");
			scanf("%d", &move_x);
			printf("Y: ");
			scanf("%d", &move_y);

			//Gets the right space
			move_x--;
			move_y--;

			move = gs_checkers_getSpaceState(game, move_y, move_x);

			if (move != gs_checkers_space_open)
				printf("ERROR: Invalid Move");
		} while (move != gs_checkers_space_open);

		//Move
		if (((move_y == piece_y + 1) || (move_y == piece_y - 1)) && ((move_x == piece_x + 1) || (move_x == piece_x - 1))) {
			gs_checkers_setSpaceState(game, gs_checkers_space_white_king, move_y, move_x); //Move piece to space
			gs_checkers_setSpaceState(game, gs_checkers_space_open, piece_y, piece_x); //Clear piece's previous space
			good = 1; //Move Complete
		}

		//Jump Back Right
		if ((move_y == piece_y + 2) && (move_x == piece_x + 2)) {
			gs_checkers_space_state jump = gs_checkers_getSpaceState(game, piece_y + 1, piece_x + 1); //Jumped piece
			if ((jump == gs_checkers_space_black) || (jump == gs_checkers_space_black_king)) { //Check jumped piece is on opposite team
				gs_checkers_setSpaceState(game, gs_checkers_space_white_king, move_y, move_x); //Move piece to space
				gs_checkers_setSpaceState(game, gs_checkers_space_open, piece_y + 1, piece_x + 1); //Clear jumped piece
				gs_checkers_setSpaceState(game, gs_checkers_space_open, piece_y, piece_x); //Clear piece's previous space
				good = 1; //Move Complete
			}
		}

		//Jump Back Left
		if ((move_y == piece_y + 2) && (move_x == piece_x - 2)) {
			gs_checkers_space_state jump = gs_checkers_getSpaceState(game, piece_y + 1, piece_x - 1); //Jumped piece
			if ((jump == gs_checkers_space_black) || (jump == gs_checkers_space_black_king)) { //Check jumped piece is on opposite team
				gs_checkers_setSpaceState(game, gs_checkers_space_white_king, move_y, move_x); //Move piece to space
				gs_checkers_setSpaceState(game, gs_checkers_space_open, piece_y + 1, piece_x - 1); //Clear jumped piece
				gs_checkers_setSpaceState(game, gs_checkers_space_open, piece_y, piece_x); //Clear piece's previous space
				good = 1; //Move Complete
			}
		}

		//Jump Forward Right
		if ((move_y == piece_y - 2) && (move_x == piece_x + 2)) {
			gs_checkers_space_state jump = gs_checkers_getSpaceState(game, piece_y - 1, piece_x + 1); //Jumped piece
			if ((jump == gs_checkers_space_black) || (jump == gs_checkers_space_black_king)) { //Check jumped piece is on opposite team
				gs_checkers_setSpaceState(game, gs_checkers_space_white_king, move_y, move_x); //Move piece to space
				gs_checkers_setSpaceState(game, gs_checkers_space_open, piece_y - 1, piece_x + 1); //Clear jumped piece
				gs_checkers_setSpaceState(game, gs_checkers_space_open, piece_y, piece_x); //Clear piece's previous space
				good = 1; //Move Complete
			}
		}

		//Jump Forward Left
		if ((move_y == piece_y - 2) && (move_x == piece_x - 2)) {
			gs_checkers_space_state jump = gs_checkers_getSpaceState(game, piece_y - 1, piece_x - 1); //Jumped piece
			if ((jump == gs_checkers_space_black) || (jump == gs_checkers_space_black_king)) { //Check jumped piece is on opposite team
				gs_checkers_setSpaceState(game, gs_checkers_space_white_king, move_y, move_x); //Move piece to space
				gs_checkers_setSpaceState(game, gs_checkers_space_open, piece_y - 1, piece_x - 1); //Clear jumped piece
				gs_checkers_setSpaceState(game, gs_checkers_space_open, piece_y, piece_x); //Clear piece's previous space
				good = 1; //Move Complete
			}
		}
	} while (good == 0);
}

//-----------------------------------------------------------------------------
