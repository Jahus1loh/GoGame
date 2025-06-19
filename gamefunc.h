#include "conio2.h"
#include <stdio.h>
#include <malloc.h>
#define _CRT_SECURE_NO_WARNINGS

class gameFunc
{
public:

	int** state;
	int** checked;
	int boardSize = 19;
	int number = 0;

	const int startX = 55;
	const int startY = 1;
	int x = startX + 1;
	int y = startY + 1;
	const int legendX = 1;
	int previousTurn = 1;
	int currentTurn, rememberPosX, rememberPosY;
	int whitePrisoners = 0, blackPrisoners = 0, blackTerritory = 0, whiteTerritory = 0;
	float komi = 6.5, whiteScore = 0, blackScore = 0;

	bool doneko = false;
	bool put = false;
	bool approved = true;
	bool gamestarted = false;

	char txt[32];
	char name[30];
	char score[100];

	void createState();
	void createChecked();
	void drawLegend();
	void drawBoard();
	void swapTurn();
	int turn();
	void resetGame();
	void resetChecked();
	void drawGameState();
	bool clearSpot(int x, int y);
	bool hasLiberty(int x, int y);
	int sameColor();
	int oppositeColor();
	bool canEasyCapture(int x, int y);
	bool blockRepeatKo();
	void captureBasic(int x, int y);
	void place(int x, int y, int z);
	bool alreadyChecked(int x, int y);
	int sameNotCheckedCount(int x, int y);
	bool canComplex(int x, int y);
	void clearWrongChecked();
	void changeCapturedToBlankBlack();
	void changeCapturedToBlankWhite();
	void complexCaptureBlack(int x, int y);
	void complexCaptureWhite(int x, int y);
	bool koRule(int x, int y);
	bool adjacentSame(int x, int y);
	void runGame();
};

