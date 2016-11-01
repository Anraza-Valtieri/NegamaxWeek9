#include "TicTacToe2D.h"
#include "GUI.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include "graphics2.h"


int isClickOutOfBoard(){
	int mouseX = mouseclickx(), mouseY = mouseclicky();
	if (mouseX < X_START_OFFSET || 
		mouseX > X_START_OFFSET+BOARD_SIZE*GRId_SIZE ||
		mouseY < Y_START_OFFSET || 
		mouseY > Y_START_OFFSET + BOARD_SIZE*GRId_SIZE)
		return 1;
	return 0;
}

void initializeBoard(){
	int i, j;
	for (i = 0; i <= BOARD_SIZE - 1; i++){
		for (j = 0; j <= BOARD_SIZE - 1; j++){
			setGridValue(i, j, EMPTY);
		}
	}
	drawHeader();
}

int getMouseX(){
	return (mouseclickx() - X_START_OFFSET) / GRId_SIZE;
}

int getMouseY(){
	return (mouseclicky() - Y_START_OFFSET) / GRId_SIZE;
}

void printAtBottom(char *text){
	settextstyle(10, HORIZ_DIR, 5);
	outtextxy(20, MAX_Y-100, text);
	getch();
}

void initializeGraphics(){
	int GraphDriver = 0, GraphMode = 0;
	initgraph(&GraphDriver, &GraphMode, "", MAX_X, MAX_Y); // Start Window
	cleardevice();
}

void drawHeader(){
	setcolor(WHITE);
	settextstyle(10, HORIZ_DIR, 5);
	outtextxy(20, 20, "Press ESC to quit Game.");
	settextstyle(10, HORIZ_DIR, 2);
	setcolor(RED);
	outtextxy(20, 70, "TIC-TAC-TOE © SIT 2015 - ICT1002");
}

int checkEscKeyPressed(){
	if (kbhit()) {
		char keyPressed = getch();
		if (keyPressed == ESC){
			return 1;
		}
	}
	return 0;
}

int checkPlayAgainKeyPressed(){
	cleardevice();
	printAtBottom("Play again? (Y/N)");
	int validResponse = 0;
	int playAnotherGame = 0;
	char keyPressed;
	do {
		if (kbhit()){
			keyPressed = getch();
			if ((keyPressed == 'y') || (keyPressed == 'Y')) {
				playAnotherGame = 1;
				validResponse = 1;
			}
			if ((keyPressed == 'n') || (keyPressed == 'N') || (keyPressed == ESC)) {
				playAnotherGame = 0;
				validResponse = 1;
			}
		}
	} while (validResponse == 0);  
	return playAnotherGame;
}

void drawClosingScreen() {
	cleardevice();
	setcolor(RED);
	outtextxy(20, 150, "Thanks for playing");
	settextstyle(10, HORIZ_DIR, 2);
	outtextxy(20, 200, "TIC-TAC-TOE © SIT 2015 - ICT1002");
	settextstyle(10, HORIZ_DIR, 5);
	setcolor(WHITE);
	outtextxy(20, 300, "Press any key to quit...");
}

void drawGridCell(int x, int y, int color){
	setcolor(color);
	setlinestyle(SOLID_LINE, 0, GRId_SIZE / 20);
	setfillstyle(SOLID_FILL, color);

	bar(x*GRId_SIZE + X_START_OFFSET,
		y * GRId_SIZE + Y_START_OFFSET,
		x * GRId_SIZE + X_END_OFFSET,
		y * GRId_SIZE + Y_END_OFFSET);
	setcolor(WHITE);
	rectangle(x*GRId_SIZE + X_START_OFFSET,
		y * GRId_SIZE + Y_START_OFFSET,
		x * GRId_SIZE + X_END_OFFSET,
		y * GRId_SIZE + Y_END_OFFSET); //Outline
}

void draw_O(int x, int y, int color){
	setcolor(color);
	setlinestyle(SOLID_LINE, 0, GRId_SIZE / 20);
	circle(x*GRId_SIZE + (X_END_OFFSET + X_START_OFFSET) / 2,
		y * GRId_SIZE + (Y_END_OFFSET + Y_START_OFFSET) / 2,
		GRId_SIZE / 2 - BORDER_OFFSET);

}

void draw_X(int x, int y, int color){
	setcolor(color);
	setlinestyle(SOLID_LINE, 0, GRId_SIZE / 20);

	line(x*GRId_SIZE + X_START_OFFSET + BORDER_OFFSET,
		y * GRId_SIZE + Y_START_OFFSET + BORDER_OFFSET,
		x * GRId_SIZE + X_END_OFFSET - BORDER_OFFSET,
		y * GRId_SIZE + Y_END_OFFSET - BORDER_OFFSET);
	line(x*GRId_SIZE + X_START_OFFSET + BORDER_OFFSET,
		y * GRId_SIZE + Y_END_OFFSET - BORDER_OFFSET,
		x * GRId_SIZE + X_END_OFFSET - BORDER_OFFSET,
		y * GRId_SIZE + Y_START_OFFSET + BORDER_OFFSET);
}

void setGridValue(int x, int y, gridValue g){
	int color;

	switch (g) {
	case EMPTY:
		color = DARKGRAY;
		drawGridCell(x, y, color);
		break;
	case O_VALUE:
		color = GREEN;
		draw_O(x, y, color);
		break;
	case X_VALUE:
		color = 12;
		draw_X(x, y, color);
		break;
	}
}