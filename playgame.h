#pragma once

/*
* Code to allow a user to play the actual peg game on the computer
*/

#include <conio.h>
#include <ctype.h>
#include<stdlib.h>
#include<time.h>
#include"pegboard.h"
#include"gamesolver.h"

void printDots(uint8_t num)
{
	for (uint8_t i = 0; i < num; i++)
	{
		printf(".");
	}
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

	while (numdots < 4)
	{
		printf("\t\t\t\t\t      ");
		printf("Press 'SPACE' to play");
		printDots(numdots);
		numdots = (numdots + 1) % 5;
		printf("\n");
		before = clock();
		do {
			difference = clock() - before;
			ms = difference * 1000 / CLOCKS_PER_SEC;
		} while (ms < trig);
		printf("\x1b[1F"); // Move to beginning of previous line
		printf("\x1b[2K"); // Clear entire line
	}
	printf("\t\t\t\t\t      ");
	printf("Press 'SPACE' to play");
	printDots(numdots);
	printf("\n");
	
	do {
		userchoice = toupper(_getch());
	} while (userchoice != 'X' && userchoice != 32);
	
	return userchoice;
}

GAMESTATE userplays(BoardState* board)
{
	printBoardState(board, 0);

	// check if the game is over
	// if not, prompt user for their move
	// make sure the move is legal, if it's not re-prompt
	// if it's ok enact it, 
	// maybe encase all this in a usermoves function of some sort
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
		userplays(&Board);

	}
	


	return results;
}