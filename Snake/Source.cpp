#include <iostream>
#include <windows.h>
#include <random>
#include <time.h>
#include <conio.h>

using namespace std;

//Global Variables

bool gameOver;
const int width = 20;
const int height = 20;
int playerX, playerY, neggX, neggY, score;
int tailX[100], tailY[100];
enum keyDir {STOP = 0, LEFT, RIGHT, UP, DOWN, QUIT};
keyDir arrowDir;
int tailLength = 0;
char gameTable[width][height];




void Setup()
{
	srand(time(0));
	gameOver = false;
	arrowDir = STOP;
	playerX = width / 2;
	playerY = height / 2;
	neggX = ((rand() % (width-2))+1);
	neggY = ((rand() % (height-3))+1);
	score = 0;
}


// Had assistance trying to figure out how to draw out the snake on the gameBoard; however, there still exists a BUG
// BUG REPORT: when the tail is 'drawn' it pushes every other space (I know why, just don't know how to fix)

void gameBoard()
{
	//clear the screen before inputting the drawing
	//This effectively makes it look like it's "moving"
	system("cls");
	
	//stores ascii characters for each condition into our character array to display later
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (i == 0 || i == height - 1)
				gameTable[i][j] = '#';
			else if (j == 0 || j == width - 1)
				gameTable[i][j] = '#';
			else if (j == playerX && i == playerY)
				gameTable[i][j] = 'O';
			else
				gameTable[i][j] = ' ';
			if (j == neggX && i == neggY)
				gameTable[i][j] = 'N';
			for (int k = 0; k < tailLength; k++) {
				if (j == tailX[k] && i == tailY[k])
					gameTable[i][j] = 'o';
			}
		}
	}

	//display character array
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			cout << gameTable[i][j];
		}
		cout << endl;
	}
	cout << endl;
	cout << "Score: " << score << endl;

}

void playerInput()
{
	//create local variable: ch, which will hold a character value
	char ch;

	//If we push a key on our keyboard, _kbhit() function will "activate" the if loop and call the _getch() function which will get the
	//character we pushed from our keyboard and store it into our ch variable
	if (_kbhit()) {
		ch = _getch();

		//This switch statement will match the character we inputed with the different cases and change the keyDir enumerator value
		//Ultimately allowing the input to be translated to an effect on our game via the gameFunction() function
		switch (ch) {
		case 'a':
			arrowDir = LEFT;
			break;
		case 'd':
			arrowDir = RIGHT;
			break;
		case 'w':
			arrowDir = UP;
			break;
		case 's':
			arrowDir = DOWN;
			break;
		case '1':
			arrowDir = QUIT;
			break;
		}
	}
}

void gameFunction()
{
	//create local variables:
	int prevX, prevY, prev2X, prev2Y;

	//initialize the first value in each array
	tailX[0] = playerX;
	tailY[0] = playerY;

	//set the previous x and y values equal to the head of the snake
	prevX = tailX[0];
	prevY = tailY[0];

	//Going through the whole tail, make each one follow the next one.
	for (int i = 1; i < tailLength; i++) {
		//prev2x and prev2y are our storing variables that allow us to temporarily store the current array
		//and pass it on to the previous one as it traverses down the array
		prev2X = tailX[i];
		prev2Y = tailY[i];
		tailX[i] = prevX;
		tailY[i] = prevY;
		prevX = prev2X;
		prevY = prev2Y;
	}

	//this is in conjunction with the input function above. It will set a value from our enumerator: keyDir
	switch (arrowDir) {
	case LEFT:
		playerX = playerX - 1;
		break;
	case RIGHT:
		playerX = playerX + 1;
		break;
	case UP:
		playerY = playerY - 1;
		break;
	case DOWN:
		playerY = playerY + 1;
		break;
	case QUIT:
		gameOver = true;
		break;
	}

	//if the head hits the tail, it's game over
	for (int j = 0; j < tailLength; j++) {
		if (playerX == tailX[j] && playerY == tailY[j]) {
			gameOver = true;
		}
	}

	//if the head hits the walls, it's game over
	if (playerX == 0 || playerX == width-1 || playerY == 0 || playerY == height-1) {
		gameOver = true;
	}

	//if the head hits a "negg" spot, it will increase the score, produce a new "negg" at a diff. spot, and increase the tailLength counter by 1.
	if (playerX == neggX && playerY == neggY) {
		score += 10;
		neggX = ((rand() % (width - 2)) + 1);
		neggY = ((rand() % (height - 3)) + 1);
		tailLength++;
	}

}


//The bottom of the stack; This is a stackframe that will call other functions on top of the stack.

int main()
{

	// Create and initialize global variables

	Setup();

	// create a while loop so the functions continously run in a loop until the game is over --> This is how we UPDATE a game

	while (!gameOver)
	{
		gameBoard();
		playerInput();
		gameFunction();
		Sleep(100);
	}
	system("pause");
	return 0;
}
