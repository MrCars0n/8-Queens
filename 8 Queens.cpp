#include<iostream>
#include<time.h>
#include<stdlib.h>
using namespace std;

bool validMove(int, int);
bool validBoard();
bool openSpaces();
void fillQueens();
void resetBoard();
void printBoard();
void blockUnavailibleSpaces(int, int);

char pieces[] = { '-', '*', 'Q' };

int board[8][8], x, y;

int main()
{
	srand(time(0));

	int count = 0;

	do
	{
		fillQueens();

		if (count > 30000)
		{
			count = 0;
			srand(time(0));
		}
		count += 1;

	} while (validBoard() == false);
	printBoard();
}

bool validMove(int row, int col)
{// checks to see if the queen is on the board.
	if (row >= 0 && row <= 7 && col >= 0 && col <= 7)
		return true;
	else
		return false;
}

void fillQueens()
{// this function places the queens on the board the first queen is placed randomly
 // and the rest of the queens are places around the blocked squares of the previous queens.
	resetBoard();
	int count = 0, randCount = 0;
	//x = rand() % 7;
	//y = rand() % 7;

	while (openSpaces() && count < 8)
	{
		x = rand() % 8;
		y = rand() % 8;

		do
		{
			x = rand() % 8;
			y = rand() % 8;
			//cout << "(" << x + 1 << ", " << y + 1 << ")" << endl;

			if (randCount > 30000)
			{
				randCount = 0;
				srand(time(0));
			}
			randCount += 1;
		} while (board[x][y] != 0);


		board[x][y] = 2;
		blockUnavailibleSpaces(x, y);
		//printBoard();
		count++;
	}
	//if (!openSpaces() && count < 8)
	//{
	//	fillQueens();
	//}

	//printBoard();
}

void blockUnavailibleSpaces(int x, int y)
// this function runs and blocks every spot that can't become a queen with an *
// So it replaces all spots the queen could "Move" in real chess.
{
	for (int r = 0; r < 8; r++)
	{
		for (int c = 0; c < 8; c++)
		{
			if (c != y && r != x)
			{
				if (board[r][y] != 2)
					board[r][y] = 1;
				if (board[x][c] != 2)
					board[x][c] = 1;
				if (r + c == x + y && board[r][c] != 2)
					board[r][c] = 1;
				if (r - c + 7 == x - y + 7 && board[r][c] != 2)
					board[r][c] = 1;
			}

		}
	}
}

void resetBoard()
{
	// Sets all board slots to zero
	for (int row = 0; row < 8; row++)
	{
		for (int col = 0; col < 8; col++)
		{
			board[row][col] = 0;
		}
	}
}

// Prints the 8x8 Board
void printBoard()
{
	// Column numbering along top
	cout << "\t  ";

	for (int i = 1; i <= 8; i++)
	{
		cout << i << " ";
	}

	cout << endl;

	// Printing the grid
	for (int r = 0; r < 8; r++)
	{
		// Row numbering along side
		cout << "\t" << r + 1 << " ";

		// Prints the gird
		for (int c = 0; c < 8; c++)
		{
			//cout << boardForwardSlash[r][c] << " ";
			cout << pieces[board[r][c]] << " ";
		}
		cout << endl;
	}
}

bool openSpaces()
{
	// this function checks to see if there are any open spaces left on the board.
	for (int r = 0; r < 8; r++)
		for (int c = 0; c < 8; c++)
			if (board[r][c] == 0)
				return true;

	return false;
}

bool validBoard()
{
	int count = 0;
	for (int row = 0; row < 8; row++)
	{
		for (int col = 0; col < 8; col++)
		{
			if (board[row][col] == 2)
				count += 1;
		}
	}
	//cout << count << endl;
	return count == 8;
}


