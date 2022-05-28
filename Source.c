/*
	- Project based on the "peg game" commonly found at Cracker Barrel
	- Planning on writing an algorithm (likely just a DFS through the game tree) to ``solve" 
	the game from various starting configurations, as well as make a playable version
	- just trying to learn some C....
*/


#include"pegboard.h"
#include"gamesolver.h"
#include"playgame.h"

int main(void)
{
	/*FILE* fptr;
	fopen_s(&fptr, "output.txt", "w");
	assert(fptr != NULL);

	BoardState testBoard;
	GAMESTATE results;
	initBoardState(&testBoard, 0);
	 
	BOOL btest = makemove(&testBoard, 1, 8, 0, fptr);
	if (btest)
	{
		printf("1\n");
	}
	printBoardState(&testBoard, 0);

	results = solvepeggame(&testBoard, fptr, 0);

	printf("Final Results: ");
	printGameState(results);
	printf("\n");

	fprintf(fptr, "Final Results: ");
	fprintGameState(results, fptr);
	fprintf(fptr, "\n");

	fclose(fptr);*/

	playgame(0);

	return 0;
}