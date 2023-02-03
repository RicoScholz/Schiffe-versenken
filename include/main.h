#include <stdbool.h>

void initGame(bool *pTurn, int *p1Score, int *p2Score, int b1[10][10], int b2[10][10]);
bool playerTurn(int enemy[10][10]);
bool computerTurn(int enemy[10][10]);
int generateShips(int board[10][10]);
void showBoards(int s1, int s2, int b1[10][10], int b2[10][10]);