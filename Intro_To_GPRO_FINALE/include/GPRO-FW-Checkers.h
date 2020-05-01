#pragma once
#include <stdio.h>


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

const char DISPLAY[5][2] = { //Used to show the spaces on the board
		' ', ' ',
		'B', 'B',
		'W', 'W',
		'B', 'K',
		'W', 'K'
};

//Colin's Functions
void gs_checkers_userInput(gs_checkers, int); //Gets user input

void gs_checkers_displayBoard(gs_checkers); //Displays board

void gs_checkers_checkKings(gs_checkers); //Makes correct pieces into kings

int gs_checkers_checkWin(gs_checkers); //Checks for win

void gs_checkers_move_black(gs_checkers, int, int); //Moves Black

void gs_checkers_move_white(gs_checkers, int, int); //Moves White

void gs_checkers_move_black_king(gs_checkers, int, int); //Moves Black Kings

void gs_checkers_move_white_king(gs_checkers, int, int); //Moves White Kings

int launchCheckers();

