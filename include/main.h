#include <stdbool.h>

void initGame(bool *gameOver, bool *playerTurn, int b1[10][10], int b2[10][10]);
bool playerTurn(int enemy[10][10]);
bool computerTurn(int enemy[10][10]);
void generateShips(int board[10][10]);
void showBoards(int b1[10][10], int b2[10][10]);