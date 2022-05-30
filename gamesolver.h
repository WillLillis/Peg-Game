#pragma once
#include"pegboard.h"

#define		WINSTATE	1
#define		LOSSSTATE	0

typedef	int	GAMESTATE;

void printGameState(GAMESTATE state)
{
	assert(state == WINSTATE || state == LOSSSTATE);
	if (state == WINSTATE)
	{
		printf("WINSTATE\n");
	}
	else if (state == LOSSSTATE)
	{
		printf("LOSSSTATE\n");
	}
}

void fprintGameState(FILE* fptr, GAMESTATE state)
{
	assert(state == WINSTATE || state == LOSSSTATE);
	if (state == WINSTATE)
	{
		fprintf(fptr, "WINSTATE\n");
	}
	else if (state == LOSSSTATE)
	{
		fprintf(fptr, "LOSSSTATE\n");
	}
}

// function that checks if a given move is allowed, but doesn't make said move
// returns TRUE if the move is allowed, and FALSE otherwise
BOOL checkmove(BoardState* board, uint8_t pos1, uint8_t pos2)
{
	assert(board != NULL);
	assert(pos1 >= 0 && pos1 <= 14);
	assert(pos2 >= 0 && pos2 <= 14);

	// if it's a legal move, and if there's a peg in the position we're moving from, the hole we're moving to is empty, and there's one in the intermediate position
	if (GetBit(getMoves(pos1), pos2) && GetBit(board->board, pos1) && !GetBit(board->board, pos2) && GetBit(board->board, getIntermediateHole(pos1, pos2)))
	{
		return TRUE;
	}

	return FALSE;
}

// function to do all the necessary work to make a move on the board
// attempts to move a peg from pos1 to pos2, 
// returns TRUE if it was a legal move, FALSE otherwise
BOOL makemove(BoardState* board, uint8_t pos1, uint8_t pos2, uint32_t numspaces)
{
	assert(board != NULL);
	assert(pos1 >= 0 && pos1 <= 14);
	assert(pos2 >= 0 && pos2 <= 14);
	
	// if it's a legal move, and if there's a peg in the position we're moving from, the hole we're moving to is empty, and there's one in the intermediate position
	if (GetBit(getMoves(pos1), pos2) && GetBit(board->board, pos1) && !GetBit(board->board, pos2) && GetBit(board->board, getIntermediateHole(pos1, pos2)))
	{
		ClearBit(board->board, pos1); // clear the peg out of the initial hole
		ClearBit(board->board, getIntermediateHole(pos1, pos2)); // and clear the peg from the intermediate hole
		SetBit(board->board, pos2); // and then finally move the peg to the new hole
		board->numpegs--;
		//printIndent(numspaces);
		//printf("Moved from %d to %d\n", pos1, pos2);
		return TRUE;
	}
	return FALSE; // if we get here it's not a legal move
}

// accompanying function that does all the work to undo a move on the board
// moves a peg from pos1 back to pos2
// if the undo move can be done, TRUE is returned, otherwise FALSE
BOOL undomove(BoardState* board, uint8_t pos1, uint8_t pos2, uint32_t numspaces)
{
	// if it's a legal move, and if there's a peg in the position we're moving back from, the hole we're moving back to is empty, and there's not one in the intermediate position
	if (GetBit(getMoves(pos1), pos2) && GetBit(board->board, pos2) && !GetBit(board->board, pos1) && !GetBit(board->board, getIntermediateHole(pos1, pos2)))
	{
		ClearBit(board->board, pos2); // clear the peg out of the initial hole
		SetBit(board->board, getIntermediateHole(pos1, pos2)); // put the peg back in the intermediate hole
		SetBit(board->board, pos1); // and then finally move the peg to the new hole
		board->numpegs++;
		//printIndent(numspaces);
		//printf("Undid a move back from %d to %d\n", pos1, pos2);
		return TRUE;
	}
	//printIndent(numspaces);
	//printf("Failure\n");
	return FALSE; // if we're here we can't undo the move
}

// function to do all the necessary work to make a move on the board
// attempts to move a peg from pos1 to pos2, 
// returns TRUE if it was a legal move, FALSE otherwise
BOOL fmakemove(FILE* fptr, BoardState* board, uint8_t pos1, uint8_t pos2, uint32_t numspaces)
{
	assert(pos1 >= 0 && pos1 <= 14);
	assert(pos2 >= 0 && pos2 <= 14);

	// if it's a legal move, and if there's a peg in the position we're moving from, the hole we're moving to is empty, and there's one in the intermediate position
	if (GetBit(getMoves(pos1), pos2) && GetBit(board->board, pos1) && !GetBit(board->board, pos2) && GetBit(board->board, getIntermediateHole(pos1, pos2)))
	{
		ClearBit(board->board, pos1); // clear the peg out of the initial hole
		ClearBit(board->board, getIntermediateHole(pos1, pos2)); // and clear the peg from the intermediate hole
		SetBit(board->board, pos2); // and then finally move the peg to the new hole
		board->numpegs--;
		fprintIndent(numspaces, fptr);
		fprintf(fptr, "Moved from %d to %d\n", pos1, pos2);
		return TRUE;
	}
	return FALSE; // if we get here it's not a legal move
}

// accompanying function that does all the work to undo a move on the board
// moves a peg from pos1 back to pos2
// if the undo move can be done, TRUE is returned, otherwise FALSE
BOOL fundomove(FILE* fptr, BoardState* board, uint8_t pos1, uint8_t pos2, uint32_t numspaces)
{
	// if it's a legal move, and if there's a peg in the position we're moving back from, the hole we're moving back to is empty, and there's not one in the intermediate position
	if (GetBit(getMoves(pos1), pos2) && GetBit(board->board, pos2) && !GetBit(board->board, pos1) && !GetBit(board->board, getIntermediateHole(pos1, pos2)))
	{
		ClearBit(board->board, pos2); // clear the peg out of the initial hole
		SetBit(board->board, getIntermediateHole(pos1, pos2)); // put the peg back in the intermediate hole
		SetBit(board->board, pos1); // and then finally move the peg to the new hole
		board->numpegs++;
		fprintIndent(numspaces, fptr);
		fprintf(fptr, "Undid a move back from %d to %d\n", pos1, pos2);
		return TRUE;
	}
	fprintIndent(numspaces, fptr);
	fprintf(fptr, "Failure\n");
	return FALSE; // if we're here we can't undo the move
}

// function to recursively explore possible moves until a winning set is found
GAMESTATE solvepeggame(BoardState* board, uint32_t numspaces)
{
	assert(board != NULL);
	GAMESTATE results;
	BOOL legalmove;
	uint16_t tempstate = 0;

	printBoardState(board, numspaces); // here for testing, will likely be overwhelming number of prints
	printIndent(numspaces);
	printbinrep(board->board);
	printf("\n");

	/*fprintBoardState(board, numspaces, fptr);
	fprintIndent(numspaces, fptr);
	fprintbinrep(board->board, fptr);
	fprintf(fptr, "\n");*/

	if (board->numpegs == 1)
	{
		return WINSTATE;
	}
	for (uint8_t currenthole = 0; currenthole < NUMHOLES; currenthole++) // for each position on the board
	{
		if (GetBit(board->board, currenthole)) // if there's a peg in that spot
		{
			for (uint8_t move = 0; move < NUMHOLES; move++) // iterate through the possible moves for that peg
			{
				tempstate = board->board;
				if ((legalmove = makemove(board, currenthole, move, numspaces))) // try to make the move
				{
					results = solvepeggame(board, numspaces + 1); // if the move was valid try playing the game from that point
					if (results == WINSTATE) // if it's a winning move...
					{
						return WINSTATE; //...we're done, return the success back up the series of calls
					}
					// if it's not a winning move, undo it and just keep trying other ones out
					legalmove = undomove(board, currenthole, move, numspaces); 
					assert(legalmove);
				}
			}
		}
	}

	return LOSSSTATE; // if we get to this point there's no winning moves, give up
}

// function to recursively explore possible moves until a winning set is found, prints debug statements to file
GAMESTATE fsolvepeggame(FILE* fptr, BoardState* board, uint32_t numspaces)
{
	assert(board != NULL);
	assert(fptr != NULL);
	GAMESTATE results;
	BOOL legalmove;
	uint16_t tempstate = 0;

	fprintBoardState(board, numspaces, fptr);
	fprintIndent(numspaces, fptr);
	fprintbinrep(board->board, fptr);
	fprintf(fptr, "\n");

	if (board->numpegs == 1)
	{
		fprintbinrep(board->board, fptr);
		fprintf(fptr, "\n");
		return WINSTATE;
	}
	for (uint8_t currenthole = 0; currenthole < NUMHOLES; currenthole++) // for each position on the board
	{
		if (GetBit(board->board, currenthole)) // if there's a peg in that spot
		{
			for (uint8_t move = 0; move < NUMHOLES; move++) // iterate through the possible moves for that peg
			{
				tempstate = board->board;
				if ((legalmove = fmakemove(fptr, board, currenthole, move, numspaces, fptr))) // try to make the move
				{
					results = fsolvepeggame(fptr, board, fptr, numspaces + 1); // if the move was valid try playing the game from that point
					if (results == WINSTATE) // if it's a winning move...
					{
						fprintbinrep(tempstate, fptr);
						fprintf(fptr, "\n");
						return WINSTATE; //...we're done, return the success back up the series of calls
					}
					// if it's not a winning move, undo it and just keep trying other ones out
					legalmove = fundomove(fptr, board, currenthole, move, numspaces, fptr);
					assert(legalmove);
				}
			}
		}
	}

	return LOSSSTATE; // if we get to this point there's no winning moves, give up
}