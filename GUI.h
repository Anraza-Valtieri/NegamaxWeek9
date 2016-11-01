#define GRId_SIZE 170
#define MAX_X 800
#define MAX_Y 800
#define STEP MAX_X/(GRId_SIZE*2)-1
#define X_START_OFFSET GRId_SIZE*(STEP)
#define X_END_OFFSET GRId_SIZE*(STEP+1)
#define Y_START_OFFSET GRId_SIZE*(STEP)
#define Y_END_OFFSET GRId_SIZE*(STEP+1)
#define BORDER_OFFSET GRId_SIZE/20
#define ESC 0x1b

int checkPlayAgainKeyPressed();
void initializeGraphics();
void drawHeader();
void drawClosingScreen();
void drawGridCell(int x, int y, int color);
void draw_O(int x, int y, int color);
void draw_X(int x, int y, int color);
void setGridValue(int x, int y, gridValue g);
int isClickOutOfBoard();
void printAtBottom(char *text);
int getMouseX();
int getMouseY();
int checkEscKeyPressed();
void initializeBoard();