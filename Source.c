/*
	- Project based on the "peg game" commonly found at Cracker Barrel
	- Planning on writing an algorithm (likely just a DFS through the game tree) to ``solve" 
	the game from various starting configurations, as well as make a playable version
	- just trying to learn some C....
*/


#include"pegboard.h"
#include"gamesolver.h"

int main(void)
{
	BoardState testBoard;
	GAMESTATE results;
	initBoardState(&testBoard, 0);

	printBoardState(&testBoard, 0);

	results = solvepeggame(&testBoard, 0);

	printf("Final Results: ");
	printGameState(results);
	printf("\n");

	return 0;
}