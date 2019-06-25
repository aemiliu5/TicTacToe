// -- Tic-Tac-Toe by Aemilius --
// Project: https://github.com/aemiliu5/TicTacToe (MIT License)
// Compilation: gcc ttt.c -o ttt -lncursesw (Linux)
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#ifdef __linux__
#include <curses.h>
#elif _WIN32
#include <conio.h>
#endif

char playarea[3][3] = { 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a' };
char player, opp;
bool o, gameEnded, selError;

void ChangeToO(int x, int y) { playarea[x-1][y-1] = 'o'; }
void ChangeToX(int x, int y) { playarea[x-1][y-1] = 'x'; }

void ClearConsole()
{
	#ifdef __linux__
	system("clear");
	#elif _WIN32
	system("cls");
	#endif
}

void PrintTable()
{  
	for(int i=0; i < 3; i++) 
	{		
		for(int j=0; j < 3; j++)
			printf("%c ", playarea[j][i]);
			
		printf("\n");
	}
}

void MovePrompt()
{
	int x,y;
	
	printf("Change which square? (x  y):");
	scanf("%d", &x);
	scanf("%d", &y);
	
	if(x < 1 || x > 3 || y < 1 || y > 3) 
	{		
		printf("ERROR: Invalid values!\n");
		MovePrompt();
	}
	else if(playarea[x-1][y-1] == 'x' || playarea[x-1][y-1] == 'o')
	{
		printf("ERROR: Invalid values!\n");
		MovePrompt();
	}
	else
	{
		if(o)	ChangeToO(x, y);
		else	ChangeToX(x, y);
	}
}

void WinGame(char winner)
{
	if(!gameEnded)
	{
		printf("The game ended with %c as the winner! Congrats!\n", winner-'a'+'A');
		gameEnded = true;
	}
}

void CheckIfWon()
{	
	if(!gameEnded)
	{
		// horizontal checks	
		if(playarea[0][0] == 'o' && playarea[0][1] == 'o' && playarea[0][2] == 'o')		WinGame('o');
		if(playarea[1][0] == 'o' && playarea[1][1] == 'o' && playarea[1][2] == 'o')		WinGame('o');
		if(playarea[2][0] == 'o' && playarea[2][1] == 'o' && playarea[2][2] == 'o')		WinGame('o');
			
		if(playarea[0][0] == 'x' && playarea[0][1] == 'x' && playarea[0][2] == 'x')		WinGame('x');
		if(playarea[1][0] == 'x' && playarea[1][1] == 'x' && playarea[1][2] == 'x')		WinGame('x');
		if(playarea[2][0] == 'x' && playarea[2][1] == 'x' && playarea[2][2] == 'x')		WinGame('x');
			
		// vertical checks	
		if(playarea[0][0] == 'o' && playarea[1][0] == 'o' && playarea[2][0] == 'o')		WinGame('o');
		if(playarea[0][1] == 'o' && playarea[1][1] == 'o' && playarea[2][1] == 'o')		WinGame('o');
		if(playarea[0][2] == 'o' && playarea[1][2] == 'o' && playarea[2][2] == 'o')		WinGame('o');
		
		if(playarea[0][0] == 'x' && playarea[1][0] == 'x' && playarea[2][0] == 'x')		WinGame('x');
		if(playarea[0][1] == 'x' && playarea[1][1] == 'x' && playarea[2][1] == 'x')		WinGame('x');
		if(playarea[0][2] == 'x' && playarea[1][2] == 'x' && playarea[2][2] == 'x')		WinGame('x');
			
		// diagonal checks
		if(playarea[0][0] == 'o' && playarea[1][1] == 'o' && playarea[2][2] == 'o')		WinGame('o');
		if(playarea[2][0] == 'o' && playarea[1][1] == 'o' && playarea[0][2] == 'o')		WinGame('o');
		
		if(playarea[0][0] == 'x' && playarea[1][1] == 'x' && playarea[2][2] == 'x')		WinGame('x');
		if(playarea[2][0] == 'x' && playarea[1][1] == 'x' && playarea[0][2] == 'x')		WinGame('x');	
		
	}
}

int ai_GenerateMove(int min_n, int max_n)
{
    return rand() % (max_n - min_n + 1) + min_n;
}

void ai_MakeMove()
{
	int tempx = ai_GenerateMove(1, 3);
	int tempy = ai_GenerateMove(1, 3);
	
	// x moveset
	if(opp == 'x')
	{	
		if(playarea[tempx-1][tempy-1] == 'x' || playarea[tempx-1][tempy-1] == 'o')	ai_MakeMove();
		else																		ChangeToX(tempx, tempy);	
	}	
	// o moveset
	else if(opp == 'o')
	{		
		if(playarea[tempx-1][tempy-1] == 'o' || playarea[tempx-1][tempy-1] == 'x')	ai_MakeMove();
		else																		ChangeToO(tempx, tempy);
	}
}

void Start()
{	
	srand(time(NULL));

	ClearConsole();
	printf("~~~COMMAND LINE TIC-TAC-TOE~~~\n      ~~~BY aemiliu5~~~\n");
	printf("Play as X or O?:");

	if(selError)	printf("\nInvalid value. Please type X or O, then press space.\n");
	
	scanf("%c", &player);

	if(player == 'x' || player == 'X')
	{
		o = false;
		opp = 'o';

		ClearConsole();
		PrintTable();
	}
	else if(player == 'o' || player == 'O')
	{
		o = true;
		opp = 'x';

		ClearConsole();
		PrintTable();
	}
	else
	{
		selError = true;
		Start();
	}
}

void Loop()
{
	Start();
	
	while(!gameEnded) 
	{
		MovePrompt();
		ClearConsole();
		PrintTable();
		ai_MakeMove();
		ClearConsole();
		PrintTable();
		CheckIfWon();
	}
}

int main()
{
	Loop();
	getch();
}