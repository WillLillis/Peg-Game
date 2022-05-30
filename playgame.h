#pragma once
/*
* Code to allow a user to play the actual peg game on the computer
*/

#include <conio.h>
#include <ctype.h>
#include<stdlib.h>
#include<time.h>
#include<Windows.h>
#include"pegboard.h"
#include"gamesolver.h"

void printDots(uint8_t num)
{
	for (uint8_t i = 0; i < num; i++)
	{
		printf(".");
	}
}

// prints specified number of dots centered on the screen, asyncronously
DWORD WINAPI AsycPrintDots(BOOL* data)
{
	uint32_t ms = 0;
	uint32_t trig = 1000;
	uint8_t numdots = 0;
	clock_t before, difference;

	while (numdots < 4 && *data)
	{
		printf("\t\t\t\t\t\t      ");
		printDots(numdots);
		numdots = (numdots + 1) % 4;
		printf("\n");
		before = clock();
		do {
			difference = clock() - before;
			ms = difference * 1000 / CLOCKS_PER_SEC;
		} while (ms < trig);
		printf("\x1b[1F"); // Move to beginning of previous line
		printf("\x1b[2K"); // Clear entire line
	}

	return 0;
}

/*
* Prints "main menu"/ welcome message for the game, takes in user choice to exit game or play game
*/
char printMenu(void)
{
	uint8_t numdots = 0;
	uint32_t ms = 0;
	uint32_t trig = 1000;
	clock_t before, difference;
	//volatile BOOL threadsync = TRUE;
	BOOL* threadsync = (BOOL*)malloc(sizeof(BOOL));
	assert(threadsync != NULL);
	*threadsync = TRUE;
	char userchoice;

	
	// Layer 1
	printf(" __________"); // top of P
	printf("\t"); // space between P and E
	printf(" __________"); // top of E
	printf("\t"); // space between E and G
	printf(" __________"); // top of G
	printf("\t\t"); // space between "PEG" and "GAME"
	printf(" __________"); // top of G
	printf("\t"); // space between G and A
	printf("     __   "); // top of A
	printf("\t"); // space between A and M
	printf(" ___    ___"); // top of M
	printf("\t"); // space between M and E
	printf(" __________\n"); // top of E

	// Layer 2
	printf("|  ______  |"); // top of P
	printf("\t"); // space between P and E
	printf("|  ________|"); // top of E
	printf("\t"); // space between E and G
	printf("|  ________|"); // top of G
	printf("\t\t"); // space between "PEG" and "GAME"
	printf("|  ________|"); // top of G
	printf("\t"); // space between G and A
	printf("    /  \\"); // top of A
	printf("\t"); // space between A and M
	printf("|   \\  /   |"); // top of M
	printf("\t"); // space between M and E
	printf("|  ________|"); // top of E
	printf("\n");

	// Layer 3
	printf("| |      | |"); // P 
	printf("\t"); // space between P and E
	printf("| |         "); // E
	printf("\t"); // space between E and G
	printf("| |         "); // G
	printf("\t\t"); // space between "PEG" and "GAME"
	printf("| |         "); // G
	printf("\t"); // space between G and A
	printf("   / /\\ \\"); // A
	printf("\t"); // space between A and M
	printf("|    \\/    |"); // M
	printf("\t"); // space between M and E
	printf("| |         "); // E
	printf("\n");

	// Layer 4
	printf("| |      | |"); // P 
	printf("\t"); // space between P and E
	printf("| |         "); // E
	printf("\t"); // space between E and G
	printf("| |         "); // G
	printf("\t\t"); // space between "PEG" and "GAME"
	printf("| |         "); // G
	printf("\t"); // space between G and A
	printf("  / /  \\ \\"); // A
	printf("\t"); // space between A and M
	printf("| |\\    /| |"); // M
	printf("\t"); // space between M and E
	printf("| |         "); // E
	printf("\n");

	// Layer 5
	printf("| |______| |"); // P 
	printf("\t"); // space between P and E
	printf("| |________"); // E
	printf("\t"); // space between E and G
	printf("| |    ____"); // G
	printf("\t\t"); // space between "PEG" and "GAME"
	printf("| |    ____"); // G
	printf("\t"); // space between G and A
	printf(" / /____\\ \\"); // A
	printf("\t"); // space between A and M
	printf("| | \\  / | |"); // M
	printf("\t"); // space between M and E
	printf("| |________"); // E
	printf("\n");

	// Layer 6
	printf("|  ________|"); // P 
	printf("\t"); // space between P and E
	printf("|  ________|"); // E
	printf("\t"); // space between E and G
	printf("| |   |__  |"); // G
	printf("\t\t"); // space between "PEG" and "GAME"
	printf("| |   |__  |"); // G
	printf("\t"); // space between G and A
	printf("/ /______\\ \\"); // A
	printf("\t"); // space between A and M
	printf("| |  \\/  | |"); // M
	printf("\t"); // space between M and E
	printf("|  ________|"); // E
	printf("\n");

	// Layer 7
	printf("| |         "); // P 
	printf("\t"); // space between P and E
	printf("| |         "); // E
	printf("\t"); // space between E and G
	printf("| |      | |"); // G
	printf("\t\t"); // space between "PEG" and "GAME"
	printf("| |      | |"); // G
	printf("\t"); // space between G and A
	printf("| |      | |"); // A
	printf("\t"); // space between A and M
	printf("| |      | |"); // M
	printf("\t"); // space between M and E
	printf("| |         "); // E
	printf("\n");

	// Layer 8
	printf("| |         "); // P 
	printf("\t"); // space between P and E
	printf("| |         "); // E
	printf("\t"); // space between E and G
	printf("| |      | |"); // G
	printf("\t\t"); // space between "PEG" and "GAME"
	printf("| |      | |"); // G
	printf("\t"); // space between G and A
	printf("| |      | |"); // A
	printf("\t"); // space between A and M
	printf("| |      | |"); // M
	printf("\t"); // space between M and E
	printf("| |         "); // E
	printf("\n");

	// Layer 9
	printf("| |         "); // P 
	printf("\t"); // space between P and E
	printf("| |         "); // E
	printf("\t"); // space between E and G
	printf("| |      | |"); // G
	printf("\t\t"); // space between "PEG" and "GAME"
	printf("| |      | |"); // G
	printf("\t"); // space between G and A
	printf("| |      | |"); // A
	printf("\t"); // space between A and M
	printf("| |      | |"); // M
	printf("\t"); // space between M and E
	printf("| |         "); // E
	printf("\n");

	// Layer 10
	printf("| |         "); // P 
	printf("\t"); // space between P and E
	printf("| |________"); // E
	printf("\t"); // space between E and G
	printf("| |______| |"); // G
	printf("\t\t"); // space between "PEG" and "GAME"
	printf("| |______| |"); // G
	printf("\t"); // space between G and A
	printf("| |      | |"); // A
	printf("\t"); // space between A and M
	printf("| |      | |"); // M
	printf("\t"); // space between M and E
	printf("| |________"); // E
	printf("\n");

	// Layer 11
	printf("|_|         "); // P 
	printf("\t"); // space between P and E
	printf("|__________|"); // E
	printf("\t"); // space between E and G
	printf("|__________|"); // G
	printf("\t\t"); // space between "PEG" and "GAME"
	printf("|__________|"); // G
	printf("\t"); // space between G and A
	printf("|_|      |_|"); // A
	printf("\t"); // space between A and M
	printf("|_|      |_|"); // M
	printf("\t"); // space between M and E
	printf("|__________|"); // E
	printf("\n");

	printf("\n\n");
	printf("\t\t\t\t\t\t");
	printf("Press 'X' to exit\n\n");
	printf("\t\t\t\t\t      ");
	printf("Press 'SPACE' to play\n");

	// spawn off a thread to print the dots asyncronously
	HANDLE threadhandle = CreateThread(NULL, 0, AsycPrintDots, threadsync, 0, NULL);

	// get the user's choice (Quit or Play)
	do {
		userchoice = toupper(_getch());
	} while (userchoice != 'X' && userchoice != 32);
	
	// now that the user has chosen, let's tell the dot printing thread to clean up shop
	if (threadsync != NULL)
	{
		*threadsync = FALSE;
	}
	// and then just wait for it to return
	if (threadhandle != NULL)
	{
		WaitForSingleObject(threadhandle, INFINITE);
	}
	
	free(threadsync);
	fflush(stdin);

	return userchoice;
}

void getUserMove(BoardState* board, uint8_t* pos1, uint8_t* pos2)
{
	assert(board != NULL);
	uint16_t retval = 0;
	
	printNumberedBoard(board);

	printf("Enter the position of the peg to move:\n");
	scanf_s("%hhu", pos1, 1);
	fflush(stdin);

	printf("Enter the position to move the peg to:\n");
	scanf_s("%hhu", pos2, 1);
	fflush(stdin);
}

void printgameresults(BoardState* board)
{
	assert(board != NULL);

	uint8_t numpegs = board->numpegs;

	switch (numpegs) {
	case 1: 
		printf("1: YOU'RE GENIUS\n");
		break;
	case 2:
		printf("2: YOU'RE PURTY SMART\n");
		break;
	case 3:
		printf("3: YOU'RE JUST PLAIN DUMB\n");
		break;
	case 4:
		printf(">=4: YOU'RE JUST PLAIN EG-NO-RA-MOOSE\n");
		break;
	}
}

// handles the user once they've selected to play the game
GAMESTATE userplays(BoardState* board)
{
	assert(board != NULL);
	uint8_t pos1, pos2;
	uint16_t usermove;
	BOOL legalmove;
	char s[10];

	while (!checkendgame(board)) // while the ending conditions of the game haven't been met...
	{
		printBoardState(board, 0);

		do {
			getUserMove(board, &pos1, &pos2); // get the user's selection
			legalmove = checkmove(board, pos1, pos2); // make sure they constitute a legal move
		} while (legalmove == FALSE);
		
		makemove(board, pos1, pos2, 0);
		printf("\n\n\nMoved from position %d to position %d:\n", pos1, pos2);
	}

	printf("\n\n\n");
	printgameresults(board);
	printf("\n\n\t\t\t\t\t\tPress any key to continue.\n");

	fflush(stdin);
	scanf_s("%s", s, (unsigned)_countof(s));

	return (board->numpegs == 1) ? WINSTATE : LOSSSTATE;
}


/*
* Main driver function for the game
*/
GAMESTATE playgame(uint8_t startpos)
{

	BoardState Board;
	GAMESTATE results = LOSSSTATE;
	char userchoice; 

	while (TRUE)
	{
		userchoice = printMenu();
		
		if (userchoice == 'X')
		{
			return LOSSSTATE; // quittin's for losers
		}

		initBoardState(&Board, startpos); // otherwise we play
		results = userplays(&Board);
	}
	
	return results;
}