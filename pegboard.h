/*
	- This header will include a definition of the actual board used to play the game
	- Not sure how to organize the various functions across the project files so there
	may or may not be some code in here as well
*/
#pragma once

#include<stdint.h>
#include<fcntl.h>
#include<stdio.h>
#include<Windows.h>
#include<minwindef.h>
#include<assert.h>
#include<math.h>

#define		NUMHOLES		15

#define		PEGCHAR			219
#define		NONPEGCHAR		176

// Define legal moves for each position bitwise
#define		MOVES0			0x28		// 3, 5
#define		MOVES1			0x140		// 6, 8
#define		MOVES2			0x280		// 7, 9
#define		MOVES3			0x1421		// 0, 5, 10, 12
#define		MOVES4			0x2800		// 11, 13
#define		MOVES5			0x5009		// 0, 3, 12, 14
#define		MOVES6			0x102		// 1, 8
#define		MOVES7			0x204		// 2, 9
#define		MOVES8			0x42		// 1, 6
#define		MOVES9			0x84		// 2, 7
#define		MOVES10			0x1008		// 3, 12
#define		MOVES11			0x2010		// 4, 13
#define		MOVES12			0x4428		// 3, 5, 10, 14
#define		MOVES13			0x810		// 4, 11
#define		MOVES14			0x1020		// 5, 12

#define		GetBit(var, bit) ((var & (1 << bit)) != 0) 
#define		SetBit(var, bit) (var |= (1 << bit))
#define		FlipBit(var, bit) (var ^= (1 << bit))

/*
	- Struct to track the current state of a game
	- board will be used bitwise for the 15 available positions
		- 0 for unoccupied, aka no peg in that hole
		- 1 for occupied, aka a peg is in that hole
	- numpegs will just track the number of remaining pegs on the board
*/
typedef struct BoardState {
	uint16_t board;
	uint8_t numpegs;
}BoardState;


// Function to return the bitwise legal move representation of a given position
uint8_t getMoves(uint8_t pos)
{
	assert(pos >= 0 && pos <= 14);
	switch (pos) {
	case 0:
		return MOVES0;
	case 1:
		return MOVES1;
	case 2:
		return MOVES2;
	case 3:
		return MOVES3;
	case 4:
		return MOVES4;
	case 5:
		return MOVES5;
	case 6:
		return MOVES6;
	case 7:
		return MOVES7;
	case 8:
		return MOVES8;
	case 9:
		return MOVES9;
	case 10:
		return MOVES10;
	case 11:
		return MOVES11;
	case 12:
		return MOVES12;
	case 13:
		return MOVES13;
	case 14:
		return MOVES14;
	}
}

// Function to get intermediate peg a given position must
// "jump over" for each move to another hole
uint8_t getIntermediateHole(uint8_t pos1, uint8_t pos2)
{
	assert(pos1 >= 0 && pos1 <= 14);
	assert(pos2 >= 0 && pos2 <= 14);
	uint16_t index = pow(2, pos1) + pow(2, pos2);

	switch (index) {
	case 9:			// 0 to 3, 3 to 0
		return 1;
	case 33:		// 0 to 5, 5 to 0
		return 2;
	case 66:		// 1 to 6, 6 to 1
		return 3;
	case 258:		// 1 to 8, 8 to 1
		return 4;
	case 132:		// 2 to 7, 7 to 2
		return 4;
	case 516:		// 2 to 9, 9 to 2
		return 5;
	case 40:		// 3 to 5, 5 to 3
		return 4;
	case 1032:		// 3 to 10, 10 to 3
		return 6;
	case 4104:		// 3 to 12, 12 to 3
		return 7;
	case 2064:		// 4 to 11, 11 to 4
		return 7;
	case 8208:		// 4 to 13, 13 to 4
		return 8;
	case 4128:		// 5 to 12, 12 to 5
		return 8;
	case 16416:		// 5 to 14, 14 to 5
		return 9;
	case 320:		// 6 to 8, 8 to 6
		return 7;
	case 640:		// 7 to 9, 9 to 7
		return 8;
	case 5120:		// 10 to 12, 12 to 10
		return 11;
	case 10240:		// 11 to 13, 13 to 11
		return 12;
	case 20480:		// 12 to 14, 14 to 12
		return 13;
	}
}



// function to initialize a BoardState struct
	// arg to choose the 1 free position, could add more options later
		// i.e. if you want it to solve from a boardstate mid game

void initBoardState(BoardState* board, uint8_t openpos)
{
	assert(openpos >= 0 && openpos <= 14);
	for (uint8_t i = 0; i < 15; i++)
	{
		SetBit(board->board, i);
	}
	FlipBit(board->board, openpos);

	board->numpegs = NUMHOLES - 1;
}

int postochar(BoardState* board, uint8_t pos)
{
	assert(pos >= 0 && pos <= 14);
	
	if (GetBit(board->board, pos))
	{
		return PEGCHAR;
	}
	return NONPEGCHAR; // otherwise the position is empty
}

void printbinrep(uint16_t num)
{
	if (num > 1)
	{
		printbinrep(num / 2);
	}

	printf("%d", num % 2);
}

void printBoardState(BoardState* board)
{
	//printf("Test: %hu \n", board->board);
	//printbinrep(board->board);
	//printf("\n");

	if (board->numpegs < 10)
	{
		printf(" %d    / \\\n", board->numpegs);
	}
	else
	{
		printf(" %d   / \\\n", board->numpegs);
	}
	printf("     / %c \\\n", postochar(board, 0));
	printf("    / %c %c \\\n", postochar(board, 1), postochar(board, 2));
	printf("   / %c %c %c \\\n", postochar(board, 3), postochar(board, 4), postochar(board, 5));
	printf("  / %c %c %c %c \\\n", postochar(board, 6), postochar(board, 7), postochar(board, 8), postochar(board, 9));
	printf(" / %c %c %c %c %c \\\n", postochar(board, 10), postochar(board, 11), postochar(board, 12), postochar(board, 13), postochar(board, 14));
	printf("---------------\n");
}


