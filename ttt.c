// Command Line Tic-Tac-Toe (by aemiliu5)
// Released under the MIT license.
// https://github.com/aemiliu5/TicTacToe
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
bool o, gameEnded;

void cls()
{
	#ifdef __linux__
	system("clear");
	#elif _WIN32
	system("cls");
	#endif
}

void printTable()
{  
	for(int i=0; i < 3; i++) 
	{		
		for(int j=0; j < 3; j++)
			printf("%c ", playarea[j][i]);
			
		printf("\n");
	}
}

void ChangeToO(int x, int y)
{
	playarea[x-1][y-1] = 'o';
}

void ChangeToX(int x, int y)
{
	playarea[x-1][y-1] = 'x';
}

void movePrompt()
{
	int x,y;
	
	printf("Change which square? (x  y):");
	scanf("%d", &x);
	scanf("%d", &y);
	
	if(x < 1 || x > 3 || y < 1 || y > 3) 
	{		
		printf("ERROR: Invalid values!\n");
		movePrompt();
	}
	else if(playarea[x-1][y-1] == 'x' || playarea[x-1][y-1] == 'o')
	{
		printf("ERROR: Invalid values!\n");
		movePrompt();
	}
	else
	{
		if(o)
		ChangeToO(x, y);
		else
		ChangeToX(x, y);
	}
}

void winGame(char winner)
{
	printf("The game ended with %c as the winner! Congrats!\n", winner-'a'+'A');
	gameEnded = true;
}

void checkIfWon()
{	
	if(!gameEnded)
	{
		// horizontal checks	
		if(playarea[0][0] == 'o' && playarea[0][1] == 'o' && playarea[0][2] == 'o')
			winGame('o');
			
		if(playarea[1][0] == 'o' && playarea[1][1] == 'o' && playarea[1][2] == 'o')
			winGame('o');
		
		if(playarea[2][0] == 'o' && playarea[2][1] == 'o' && playarea[2][2] == 'o')
			winGame('o');
			
		if(playarea[0][0] == 'x' && playarea[0][1] == 'x' && playarea[0][2] == 'x')
			winGame('x');
			
		if(playarea[1][0] == 'x' && playarea[1][1] == 'x' && playarea[1][2] == 'x')
			winGame('x');
		
		if(playarea[2][0] == 'x' && playarea[2][1] == 'x' && playarea[2][2] == 'x')
			winGame('x');
			
		// vertical checks	
		if(playarea[0][0] == 'o' && playarea[1][0] == 'o' && playarea[2][0] == 'o')
			winGame('o');
		if(playarea[0][1] == 'o' && playarea[1][1] == 'o' && playarea[2][1] == 'o')
			winGame('o');
		if(playarea[0][2] == 'o' && playarea[1][2] == 'o' && playarea[2][2] == 'o')
			winGame('o');
		if(playarea[0][0] == 'x' && playarea[1][0] == 'x' && playarea[2][0] == 'x')
			winGame('x');
		if(playarea[0][1] == 'x' && playarea[1][1] == 'x' && playarea[2][1] == 'x')
			winGame('x');
		if(playarea[0][2] == 'x' && playarea[1][2] == 'x' && playarea[2][2] == 'x')
			winGame('x');
			
		// diagonal checks
		if(playarea[0][0] == 'o' && playarea[1][1] == 'o' && playarea[2][2] == 'o')
		winGame('o');
		if(playarea[2][0] == 'o' && playarea[1][1] == 'o' && playarea[0][2] == 'o')
		winGame('o');
		
		if(playarea[0][0] == 'x' && playarea[1][1] == 'x' && playarea[2][2] == 'x')
		winGame('x');
		if(playarea[2][0] == 'x' && playarea[1][1] == 'x' && playarea[0][2] == 'x')
		winGame('x');	
		
	}
}

int ai_GenRand(int min_n, int max_n)
{
    return rand() % (max_n - min_n + 1) + min_n;
}

void ai_MakeMove()
{
	int tempx, tempy;	

	tempx = ai_GenRand(1, 3);
	tempy = ai_GenRand(1, 3);
	
	// x moveset
	if(opp == 'x')
	{	
		if(playarea[tempx-1][tempy-1] == 'x' || playarea[tempx-1][tempy-1] == 'o')
			ai_MakeMove();
		else
			ChangeToX(tempx, tempy);	
	}	
	// o moveset
	else if(opp == 'o')
	{		
		if(playarea[tempx-1][tempy-1] == 'o' || playarea[tempx-1][tempy-1] == 'x')
			ai_MakeMove();
		else
			ChangeToO(tempx, tempy);
	}
}

void start()
{	
	srand(time(NULL));

	cls();
	printf("~~~COMMAND LINE TIC-TAC-TOE~~~\n      ~~~BY aemiliu5~~~\n");
	printf("Play as X or O?: ");
	
	scanf("%c", &player);
	if(player == 'x' || player == 'X')
	{
		o = false;
		opp = 'o';
	}
	else if(player == 'o' || player == 'O')
	{
		o = true;
		opp = 'x';
	}
	else
	{
		o = true;
		opp = 'x';
	}

	cls();
	printTable();
}

void loop()
{
	start();
	
	while(!gameEnded) 
	{
		movePrompt();
		cls();
		printTable();
		ai_MakeMove();
		cls();
		printTable();
		checkIfWon();
	}
}

int main()
{
	loop();
	getch();
}

