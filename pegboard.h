/*
	- This header will include a definition of the actual board used to play the game
	- Not sure how to organize the various functions across the project files
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

// Define legal moves for each board position bitwise
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
#define		ClearBit(var, bit) (var &= ~(1 << bit))

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
uint16_t getMoves(uint8_t pos)
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
	uint16_t index = (uint16_t)pow(2, pos1) + (uint16_t)pow(2, pos2);

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

	return 255;
}

// function to initialize a BoardState struct
	// arg to choose the 1 free position, could add more options later
		// i.e. if you want it to solve from a boardstate mid game
void initBoardState(BoardState* board, uint8_t openpos)
{
	assert(board != NULL);
	assert(openpos >= 0 && openpos <= 14);

	for (uint8_t i = 0; i < 15; i++)
	{
		SetBit(board->board, i);
	}
	ClearBit(board->board, openpos);

	board->numpegs = NUMHOLES - 1;
}

char postochar(BoardState* board, uint8_t pos)
{
	assert(board != NULL);
	assert(pos >= 0 && pos <= 14);
	
	if (GetBit(board->board, pos))
	{
		return PEGCHAR;
	}
	return NONPEGCHAR; // otherwise the position is empty
}

void printIndent(uint32_t numspaces)
{
	for (uint32_t i = 0; i < numspaces; i++)
	{
		printf("\t");
	}
}

void fprintIndent(FILE* fptr, uint32_t numspaces)
{
	assert(fptr != NULL);
	for (uint32_t i = 0; i < numspaces; i++)
	{
		fprintf(fptr, "\t");
	}
}

void printbinrep(uint16_t num)
{
	if (num > 1)
	{
		printbinrep(num / 2);
	}

	printf("%d", num % 2);
}

void fprintbinrep(FILE* fptr, uint16_t num)
{
	assert(fptr != NULL);
	if (num > 1)
	{
		fprintbinrep(num / 2, fptr);
	}

	fprintf(fptr, "%d", num % 2);
}

// function to check if the ending conditions of the game have been met
		// checks if there's only 1 peg left first, otherwise there's any legal moves left on the board
// returns FALSE if the game can continue to played, TRUE if ending conditions have been met
BOOL checkendgame(BoardState* board)
{
	assert(board != NULL);

	// check to see if there's any possible moves, if so return TRUE, otherwise FALSE
	for (uint8_t currenthole = 0; currenthole < NUMHOLES; currenthole++) // for each position on the board
	{
		if (GetBit(board->board, currenthole)) // if there's a peg in that spot
		{
			for (uint8_t move = 0; move < NUMHOLES; move++) // iterate through the possible moves for that peg
			{
				if (checkmove(board, currenthole, move)) // check if the move is allowed
				{
					return FALSE; // if it is, return FALSE, otherwise keep checking for other moves
				}
			}
		}
	}

	return TRUE; // if we've reached this point there are no legal moves remaining
}

void printBoardState(BoardState* board, uint32_t numspaces)
{
	assert(board != NULL);
	if (board->numpegs < 10)
	{
		printIndent(numspaces);
		printf(" %d    / \\\n", board->numpegs);
	}
	else
	{
		printIndent(numspaces);
		printf(" %d   / \\\n", board->numpegs);
	}
	printIndent(numspaces);
	printf("     / %c \\\n", postochar(board, 0));
	printIndent(numspaces);
	printf("    / %c %c \\\n", postochar(board, 1), postochar(board, 2));
	printIndent(numspaces);
	printf("   / %c %c %c \\\n", postochar(board, 3), postochar(board, 4), postochar(board, 5));
	printIndent(numspaces);
	printf("  / %c %c %c %c \\\n", postochar(board, 6), postochar(board, 7), postochar(board, 8), postochar(board, 9));
	printIndent(numspaces);
	printf(" / %c %c %c %c %c \\\n", postochar(board, 10), postochar(board, 11), postochar(board, 12), postochar(board, 13), postochar(board, 14));
	printIndent(numspaces);
	printf("---------------\n");
}

void fprintBoardState(FILE* fptr, BoardState* board, uint32_t numspaces)
{
	assert(board != NULL);
	assert(fptr != NULL);
	if (board->numpegs < 10)
	{
		fprintIndent(numspaces, fptr);
		fprintf(fptr, " %d    / \\\n", board->numpegs);
	}
	else
	{
		fprintIndent(numspaces, fptr);
		fprintf(fptr, " %d   / \\\n", board->numpegs);
	}
	fprintIndent(numspaces, fptr);
	fprintf(fptr, "     / %c \\\n", postochar(board, 0));
	fprintIndent(numspaces, fptr);
	fprintf(fptr, "    / %c %c \\\n", postochar(board, 1), postochar(board, 2));
	fprintIndent(numspaces, fptr);
	fprintf(fptr, "   / %c %c %c \\\n", postochar(board, 3), postochar(board, 4), postochar(board, 5));
	fprintIndent(numspaces, fptr);
	fprintf(fptr, "  / %c %c %c %c \\\n", postochar(board, 6), postochar(board, 7), postochar(board, 8), postochar(board, 9));
	fprintIndent(numspaces, fptr);
	fprintf(fptr, " / %c %c %c %c %c \\\n", postochar(board, 10), postochar(board, 11), postochar(board, 12), postochar(board, 13), postochar(board, 14));
	fprintIndent(numspaces, fptr);
	fprintf(fptr, "---------------\n");
}

void printNumberedBoard(BoardState* board)
{
	assert(board != NULL);

	printf("         0 \n");
	printf("       1  2 \n");
	printf("     3  4  5 \n");
	printf("    6  7  8  9 \n");
	printf("  10 11 12 13 14 \n");
}

