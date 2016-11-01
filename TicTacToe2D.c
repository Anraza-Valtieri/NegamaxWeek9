#include "TicTacToe2D.h"
#include "GUI.h"
#include "graphics2.h"
#include <stdio.h>
#include <stdlib.h>


int turn = 1;
int player, comp;
int board[BOARD_SIZE][BOARD_SIZE] = { EMPTY };
int playAnotherGame = 1;
int gameOver = 0;

void initializeGame() {
	/*Rewrite this function consider that we are using 2D array now*/
	/*Insert your own code (1)*/
	int i, j;
	for (i = 0; i < BOARD_SIZE; i++)
		for (j = 0; j < BOARD_SIZE; j++) {
			board[i][j] = EMPTY;
			printf("i = %d j = %d value is %d\n", i, j, board[i][j]);
		}
			

	turn = 1;
	gameOver = 0;
}

int check_draw()
{
	if (turn > BOARD_SIZE*BOARD_SIZE)
	{
		printAtBottom("Game draws");
		gameOver = 1;
		return 1;
	}
	return FALSE;
}


gridValue assignValueToCell(int x, int y)
{
	/*Insert your own code (2)*/
	printf("assignValueToCell called %d %d\n", x, y);
	if (turn % 2)
		board[x][y] = X_VALUE;
	else
		board[x][y] = O_VALUE;
	turn++;
	printf("assignValueToCell exited %d %d\n", x, y);
	return board[x][y];
}

int isWinning(int p)
{
	// p==1 then X   p==0  then  O
	int i, j;
	int win_value;

	if (p == 1)
		win_value = X_VALUE * X_VALUE * X_VALUE; // 15
	else
		win_value = O_VALUE * O_VALUE * O_VALUE; // 12
	printf("isWinning called %d \n", win_value);
	/*Insert your own code (3)*/
	i = 0;
	j = 0;
	while (i <= BOARD_SIZE) {//row check
		if (board[i][j] * board[i][j + 1] * board[i][j + 2] == win_value) {
			printf("isWinning row check %d %d\n", i, j);
			return 1;
		}
		i++;
	}

	i = 0;
	j = 0;
	while (j <= BOARD_SIZE) {//column check
		if (board[i][j] * board[i + 1][j] * board[i + 2][j] == win_value) {
			printf("isWinning column check %d %d\n", i, j);
			return 1;
		}
		j++;
	}

	if (board[0][0] * board[1][1] * board[2][2] == win_value) {
		printf("isWinning diag check %d %d\n", i, j);
		return 1;
	}

	if (board[0][2] * board[1][1] * board[2][0] == win_value) {
		printf("isWinning row check %d %d\n", i, j);
		return 1;
	}
	return 0;

	return FALSE;
}
/*********************************************************************
** Function: check_win
** Description: Checks for three in a row in all directions.
** Parameters:
** Pre-Conditions: None.
** Post-Conditions: Returns the character that that the three in a row consists of.
*********************************************************************/
char check_win() {
	// Check horizontal, vertical & diagonal through [0][0]
	if (board[0][0] != EMPTY && (board[0][0] == board[0][1] && board[0][0] == board[0][2] ||
		board[0][0] == board[1][0] && board[0][0] == board[2][0] ||
		board[0][0] == board[1][1] && board[0][0] == board[2][2]))

		return board[0][0];

	// Check horizontal, vertical & diagonal through [1][1]
	if (board[1][1] != EMPTY && (board[1][1] == board[1][0] && board[1][1] == board[1][2] ||
		board[1][1] == board[0][1] && board[1][1] == board[2][1] ||
		board[1][1] == board[2][0] && board[1][1] == board[0][2]))

		return board[1][1];

	// Check horizontal, vertical & diagonal through [2][2]
	if (board[2][2] != EMPTY && (board[2][2] == board[0][2] && board[2][2] == board[1][2] ||
		board[2][2] == board[2][0] && board[2][2] == board[2][1]))

		return board[2][2];

	return 0;
}

int negamax(char player1, char player2);
int pick_best_move( char player1, char player2) {

	int best_move_score = -9999;
	int best_move_row = -9999;
	int best_move_col = -9999;
	int score_for_this_move = 0;

	if (player1 == 1)
		player1 = X_VALUE;
	else
		player1 = O_VALUE;

	if (player2 == 1)
		player1 = X_VALUE;
	else
		player1 = O_VALUE;

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (board[i][j] == EMPTY) {
				board[i][j] = player1; //Try test move.
				printf("pick_best_move - board[%d][%d] \n", i, j);
				score_for_this_move = -(negamax(player2, player1));
				printf("pick_best_move - score_for_this_move = %d\n", score_for_this_move);
				board[i][j] = EMPTY; //Put back test move.
				if (score_for_this_move >= best_move_score) {
					best_move_score = score_for_this_move;
					best_move_row = i;
					best_move_col = j;
					printf("pick_best_move - score_for_this_move %d >= best_move_score %d = Choice %d,%d\n", score_for_this_move, best_move_score, i, j);
				}
			}
		}
	}
	return ((best_move_row * BOARD_SIZE) + best_move_col);
}

int negamax(char player1, char player2) {

	int best_move_score = -9999;
	int score_for_this_move = 0;

	//If player 1 wins, then the score is high (good for player1)
	if (check_win() == player1)
	return 1000;

	//If player 2 loses, then the score is low (bad for player1)
	else if (check_win() == player2)
	return -1000;

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (board[i][j] == EMPTY) {
				board[i][j] = player1; //Try test move.
				//printf("negamax - board[%d][%d] \n", i,j);
				score_for_this_move = -(negamax(player2, player1));
				//printf("negamax - score_for_this_move = %d\n", score_for_this_move);
				board[i][j] = EMPTY; //Put back test move.
				if (score_for_this_move >= best_move_score) {
					//printf("negamax - score_for_this_move %d >= best_move_score %d\n", score_for_this_move, best_move_score);
					best_move_score = score_for_this_move;
				}
			}
		}
}

if (best_move_score == -9999 || best_move_score == 0)
return 0;

else if (best_move_score < 0)
	return best_move_score + 1;

else if (best_move_score > 0)
return best_move_score - 1; //As the game goes longer, and the recursion goes deeper, the moves near the end are less favorable than in the beginning.

}
int isNearWinning(int p, int attempt)
{
	// p==1 then X   p==0  then  O
	int i, j = 0;
	int win_value;

	if (p == 1)
		win_value = X_VALUE * X_VALUE * EMPTY; 
	else
		win_value = O_VALUE * O_VALUE * EMPTY;

	/*if (p == 1 && attempt == 2)
		win_value = X_VALUE * EMPTY * EMPTY;
	else
		win_value = O_VALUE * EMPTY * EMPTY;*/

	printf("isNearWinning called %d \n", win_value);
	/*Insert your own code (3)*/

	if (board[0][0] * board[1][1] * board[2][2] > win_value) {
		printf("isNearWinning diag check %d %d\n", 0, 0);
		for (i = 0; i < BOARD_SIZE; i++) {
			if (board[i][1] == EMPTY)
				return ((i*BOARD_SIZE) + 1);
		}		
	}

	if (board[0][2] * board[1][1] * board[2][0] > win_value) {
		printf("isNearWinning row check %d %d\n", 0, 2);
		for (i = 2; i > 0; i--) {
			if (board[i][1] == EMPTY)
				return ((i*BOARD_SIZE) + 1);
		}
	}
	//row check
	for (i = 0; i < 3; i++) {
		if (board[i][j] * board[i][j + 1] * board[i][j + 2] == win_value) {
			printf("isNearWinning row check %d %d\n", i, j);
			if (board[i][j] != EMPTY) {
				if (board[i][j + 1] == board[i][j]) {
					if (board[i][j + 2] == board[i][j]) {
						return 1;
					}return ((i*BOARD_SIZE) + j + 2);
				}return ((i*BOARD_SIZE) + j + 1);
			}return ((i*BOARD_SIZE) + j);
		}
	}
	//column check
	i = 0;
	j = 0;
	for (j = 0; j < 3; j++) {
		if (board[i][j] * board[i + 1][j] * board[i + 2][j] == win_value) {
			printf("isNearWinning column check %d %d\n", i, j);
			if (board[i][j] != EMPTY) {
				if (board[i+1][j] == board[i][j]) {
					if (board[i+2][j] == board[i][j]) {
						return 1;
					}return (((i+2)*BOARD_SIZE)+j);
				}return (((i+1)*BOARD_SIZE)+j);
			}return ((i*BOARD_SIZE)+j);
		}
	}
	return -1;
	return FALSE;
}
int getPossibleWinningPos() {
	return pick_best_move(comp, player);
}
/*
int getPossibleWinningPos2() {
	printf("getPossibleWinningPos Called\n");

	int i, j, t;

	if (turn > 2) {
		printf("getPossibleWinningPos EXIT turn > 2 Exit\n");
		t = isNearWinning(comp, 1);
		if (t == -1) {
			t = isNearWinning(player, 1);
			if (t > -1) {
				printf("getPossibleWinningPos EXIT turn > 2 result in favor of AI Exit\n");
				return t;
			}
			else
			{
				t = isNearWinning(player, 1);
				if (t > -1) {
					printf("getPossibleWinningPos EXIT turn > 2 result in favor of Player Exit\n");
					return t;
				}
				else {
					for (i = 0; i < 3; i++) {
						for (j = 0; j < 3; j++) {
							if (board[i][j] == EMPTY) {
								printf("getPossibleWinningPos EXIT turn > 2 but no result Exit\n");
								t = isNearWinning(comp, 1);
								if (t > -1) {
									printf("getPossibleWinningPos EXIT turn > 2 result in favor of AI LEVEL 2 Exit\n");
									return t;
								}
								else
								{
									t = isNearWinning(player, 1);
									if (t > -1) {
										printf("getPossibleWinningPos EXIT turn > 2 result in favor of Player Level 2 Exit\n");
										return t;
									}
								}
								return (i * BOARD_SIZE) + j;
							}
						}
					}
				}
			}
		}
		printf("getPossibleWinningPos EXIT turn > 2 result in favor of Player Level 0.5 Exit\n");
		return t;
	}
	else { // First move, does not really matter.
		if (board[1][1] == EMPTY) // Favor the center
			return (1 * BOARD_SIZE) + 1;
		else {
			for (i = 0; i < 3; i++) {
				for (j = 0; j < 3; j++) {
					if (board[i][j] == EMPTY) {
						if (rand(0, 20) > 1) {
							printf("getPossibleWinningPos EXIT turn < 2 Exit\n");
							return (i * BOARD_SIZE) + j;
						}
						return (1 * BOARD_SIZE) + 1;
					}
				}
			}
		}
	}
}*/

int getPlayertype(int p) {
	if (p == 1)
		return X_VALUE;
	else
		return O_VALUE;
}

void computer_turn()
{
	// p==1 then X   p==0  then  O
	int pos = getPossibleWinningPos();
	printf("computer_turn pos %d\n", pos);
	int x = (pos / BOARD_SIZE), y = (pos % BOARD_SIZE);
	setGridValue(x, y, assignValueToCell(x, y));

	if (isWinning(comp) == TRUE)
	{
		printAtBottom("Sorry! Computer won. ");
		gameOver = 1;
	}
}

void player_turn()
{
	int mouseX, mouseY;
	//printf("player_turn \n");
	if (mouseup()) {
		if (isClickOutOfBoard())
			return;
		mouseX = getMouseX();
		mouseY = getMouseY();
		printf("Mousex %d, MouseY %d\n", mouseX, mouseY);
		if (board[mouseX][mouseY] != EMPTY) {
			printf("Mousex %d, MouseY %d is not EMPTY.\n", mouseX, mouseY);
			return;
		}

		setGridValue(mouseX, mouseY, assignValueToCell(mouseX, mouseY));

		if (isWinning(player) == TRUE)
		{
			printAtBottom("Congratulations! You won!");
			gameOver = 1;
		}
	}
		//printf("player_turn exited \n");
}

void menu()
{
	int choice;
	char term;
	system("cls");
	printf("\n--------TIC-TAC-TOE MENU--------");
	printf("\n1 : Play with X");
	printf("\n2 : Play with O");
	printf("\n3 : Exit");
	printf("\nEnter your choice:>");
	scanf("%d", &choice);
	while (getchar() != '\n');

	switch (choice)
	{
	case 1:
		player = 1;
		comp = 0;
		break;
	case 2:
		player = 0;
		comp = 1;
		break;
	case 3:
		exit(1);
	default:
		printf("\nInvalid value");
		menu();
	}
}


void main()
{
	menu();
	initializeGraphics();
	cleardevice();

	while (playAnotherGame == TRUE) {
		cleardevice();
		initializeGame();
		initializeBoard();
		clearmouse();
		while (!gameOver) {
			if (checkEscKeyPressed()){
				gameOver = 1;
				continue;
			}
				
			if (check_draw())
				continue;

			if (player == turn % 2){
				player_turn();
			}
			else {
				computer_turn();
			}
		}
		playAnotherGame = checkPlayAgainKeyPressed();
	}
	drawClosingScreen();
	getch();
}




