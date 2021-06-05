#include <iostream> 
#include <conio.h>
#include <time.h>
#include <fstream>
#include <string>
#include "help.h"
//#pragma comment(linker, "/STACK:20000000")

using namespace std;

int score = 0;

void placegems(int game[][8]);
void flamingdeletion(int board[][8], int row, int col);
void destroyerdeletion(int board[][8], int row, int col);
bool isdestroyergem(int board[8][8], int row, int col);
bool isflaminggem(int board[8][8], int row, int col);

void randomizeboard(int arr[][8], int rows) 
//function to randomize the elements of 2d array. It takes as input, a 2d array with 8 columns, and its number of rows as input.
{
	//the srand function seeds random values to be used in the rand function.
	//time(0) ensures that the values seeded are not the same each time.
	for (int rownumber = 0; rownumber < 8; rownumber++)	//this loop runs through each of the 8 rows of the array.
	{
		for (int columnnumber = 0; columnnumber < 8; columnnumber++)//this loop goes to each column of the array, for each row.
		{
			arr[rownumber][columnnumber] = 1 + rand() % 5;		//to assign a random value from 1 to 5 to each element of the array.
		}
	}
}

void printboard(int arr[][8], int rows) //prints the values of the array on the screen, row by row.
{ //This function is only for debugging purposes
	for (int rownumber = 0; rownumber < 8; rownumber++)
	{
		for (int columnnumber = 0; columnnumber < 8; columnnumber++)
		{
			cout << arr[rownumber][columnnumber] << " ";
		}
		cout << endl;
	}
}

bool findmatches(int arr[8][8])
//This function takes an array and its number of rows and scans the whole array for vertical or horizontal repeating values.
//Returns true if any matches of 3 or more consecutively same, horizontal or vertical values is found.
{
	for (int i = 0; i < 8; i++)//this loop runs through each of the 8 rows of the array.
	{
		for (int j = 0; j < 8; j++)//this loop goes to each column of the array, for each row.
		{
			if (i < 6) //prevents the check from going out of bounds
			{
				if ((arr[i][j] % 10 == arr[i + 1][j] % 10) && (arr[i][j] % 10 == arr[i + 2][j] % 10))
				//checks for three vertically matching values
				{
					return true;
				}
			}
		}
	}
	for (int i = 0; i < 8; i++)//this loop runs through each of the 8 rows of the array.
	{
		for (int j = 0; j < 8; j++)//this loop goes to each column of the array, for each row.
		{
			if (j < 6) //prevents the check from going out of bounds
			{
				if ((arr[i][j] % 10 == arr[i][j + 1] % 10) && (arr[i][j] % 10 == arr[i][j + 2] % 10))
				//checks for three horizontally matching values
				{
					return true;
				}
			}
		}
	}
	return false;
}

void elbowmatch(int arr[8][8])
/*This function checks for any elbow matches. The elbow matches are
of four types in total. If you rotate the letter "L" by 90 degrees
3 times, you can better understand all four of the elbow matches.
Whenever this function finds an elbow match, it converts the corner
of the elbow into a destroyer gem, and destroys all other elements
of the elbow. The four nested loops have different starting and
ending values in order to cater for the four different types of
elbows.*/
{
	int value;
	for (int i = 0; i < 6; i++)//loop runs through rows of the backend array.
	{
		for (int j = 0; j < 6; j++)//loop runs through columns of the backend array.
		{
			if ((arr[i][j]!=0) && ((arr[i][j] % 10) == (arr[i][j + 1] % 10)) && ((arr[i][j] % 10) == (arr[i][j + 2] % 10)) && ((arr[i][j] % 10) == (arr[i + 1][j] % 10)) && ((arr[i][j] % 10) == (arr[i][j + 2] % 10)))
			{
				value = arr[i][j];
				//if match is made, presence of special gems needs to be checked.
				for (int k = i; k < i + 3; k++) //
				{
					for (int l = j; l < j + 3; l++)
					{
						if (k == i || l == j)
						{
							if (isdestroyergem(arr, k, l) == true)
							{
								destroyerdeletion(arr, k, l);
							}
							if (isflaminggem(arr, k, l) == true)
							{
								flamingdeletion(arr, k, l);
							}
						}
					}
				}
				arr[i][j] = value + 20;		//Destroyer gem is made
				arr[i][j + 1] = 0;			//Rest of the gems are destroyed
				arr[i][j + 2] = 0;
				arr[i + 1][j] = 0;
				arr[i + 2][j] = 0;
				score = score + 5;
				placegems(arr);
			}
		}
	}
	for (int i = 2; i < 8; i++)
	{
		for (int j = 2; j < 8; j++)
		{
			if ((arr[i][j] != 0) && ((arr[i][j] % 10) == (arr[i][j - 1] % 10)) && ((arr[i][j - 1] % 10) == (arr[i][j - 2] % 10)) && ((arr[i][j] % 10) == (arr[i - 1][j] % 10)) && ((arr[i - 1][j]%10) == (arr[i - 2][j]%10)))
			{
				value = arr[i][j];
				//if match is made, presence of special gems needs to be checked.
				for (int k = i-2; k < i + 1; k++)
				{
					for (int l = j-2; l < j + 1; l++)
					{
						if (k == i || l == j )
						{
							if (isdestroyergem(arr, k, l) == true)
							{
								destroyerdeletion(arr, k, l);
							}
							if (isflaminggem(arr, k, l) == true)
							{
								flamingdeletion(arr, k, l);
							}
						}
					}
				}
				arr[i][j] = value+20;	//Destroyer gem is made
				arr[i][j - 1] = 0;		//Rest of the gems are destroyed
				arr[i][j - 2] = 0;
				arr[i - 1][j] = 0;
				arr[i - 2][j] = 0;
				score = score + 5;
				placegems(arr);
			}
		}
	}
	for (int i = 0; i < 6; i++)
	{
		for (int j = 2; j < 8; j++)
		{
			if ((arr[i][j] != 0) && ((arr[i][j] % 10) == (arr[i][j - 1] % 10)) && ((arr[i][j - 1] % 10) == (arr[i][j - 2] % 10)) && ((arr[i][j] % 10) == (arr[i + 1][j] % 10)) && ((arr[i][j] % 10) == (arr[i + 2][j] % 10)))
			{
				value = arr[i][j];
				//if match is made, presence of special gems needs to be checked.
				for (int k = i; k < i + 3; k++)
				{
					for (int l = j - 2; l < j + 1; l++)
					{
						if (k == i || l == j)
						{
							if (isdestroyergem(arr, k, l) == true)
							{
								destroyerdeletion(arr, k, l);
							}
							if (isflaminggem(arr, k, l) == true)
							{
								flamingdeletion(arr, k, l);
							}
						}
					}
				}
				arr[i][j] = value + 20;		//Destroyer gem is made
				arr[i][j - 1] = 0;			//Rest of the gems are destroyed
				arr[i][j - 2] = 0;
				arr[i - 1][j] = 0;
				arr[i - 2][j] = 0;
				score = score + 5;
				placegems(arr);
			}
		}
	}
	for (int i = 2; i < 8; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			if ((arr[i][j] != 0) && ((arr[i][j] % 10) == (arr[i - 1][j] % 10)) && ((arr[i][j] % 10) == (arr[i - 2][j] % 10)) && ((arr[i][j] % 10) == (arr[i][j + 1] % 10)) && ((arr[i][j] % 10) == (arr[i][j + 2] % 10)))
			{
				value = arr[i][j];
				//if match is made, presence of special gems needs to be checked.
				for (int k = i - 2; k < i + 1; k++)
				{
					for (int l = j; l < j + 3; l++)
					{
						if (k == i || l == j)
						{
							if (isdestroyergem(arr, k, l) == true)
							{
								destroyerdeletion(arr, k, l);
							}
							if (isflaminggem(arr, k, l) == true)
							{
								flamingdeletion(arr, k, l);
							}
						}
					}
				}
				arr[i][j] = value + 20;		//Destroyer gem is made
				arr[i - 1][j] = 0;			//Rest of the gems are destroyed
				arr[i - 2][j] = 0;
				arr[i][j+2] = 0;
				arr[i][j+1] = 0;
				score = score + 5;
				placegems(arr);
			}
		}
	}
}

void flamingdeletion(int board[8][8], int row, int col)
/*This function is responsible for blasting the flaming gem.
It has to deal seperately with the flaming gems that lie between
the first and last row and the first and last column. This is 
because the flaming gems in the border rows and columns, as
well as the corners, blast differently as compared to the middle
ones.*/
{
	int a, b;
	if (row != 0 && row != 7 && col != 0 && col != 7)//avoiding first and last row and column.
	{
		for (int k = row - 1; k <= row + 1; k++)
		{
			for (int l = col-1; l <= col + 1; l++)
			{
				a = k;
				b = l;
				if ((k!=a || l!=b) && isflaminggem(board,k,l)==true)
				{
					flamingdeletion(board, k, l);
				}
				else if ((k != a || l != b) && isdestroyergem(board, k, l) == true)
				{
					destroyerdeletion(board, k, l);
				}
				board[k][l] = 0;
				score = score + 6;
				placegems(board);
			}
		}
	}
	else if (row == 0 && col == 0) //dealing with top left corner
	{
		for (int k = row ; k <= row + 1; k++)
		{
			for (int l = col; l <= col + 1; l++)
			{
				a = k;
				b = l;
				if ((k != a || l != b) && isflaminggem(board, k, l) == true)
				{
					flamingdeletion(board, k, l);
				}
				else if ((k != a || l != b) && isdestroyergem(board, k, l) == true)
				{
					destroyerdeletion(board, k, l);
				}
				board[k][l] = 0;
				score = score + 4;
				placegems(board);
			}
		}
	}
	else if (row == 0 && col == 7) //dealing with top right corner
	{
		for (int k = row; k <= row+1; k++)
		{
			for (int l = col-1; l <= col; l++)
			{
				a = k;
				b = l;
				if ((k != a || l != b) && isflaminggem(board, k, l) == true)
				{
					flamingdeletion(board, k, l);
				}
				else if ((k != a || l != b) && isdestroyergem(board, k, l) == true)
				{
					destroyerdeletion(board, k, l);
				}
				board[k][l] = 0;
				score = score + 4;
				placegems(board);
			}
		}
	}
	else if (row == 7 && col == 0) //dealing with bottom left corner
	{
		for (int k = row - 1; k <= row; k++)
		{
			for (int l = col; l <= col + 1; l++)
			{
				a = k;
				b = l;
				if ((k != a || l != b) && isflaminggem(board, k, l) == true)
				{
					flamingdeletion(board, k, l);
				}
				else if ((k != a || l != b) && isdestroyergem(board, k, l) == true)
				{
					destroyerdeletion(board, k, l);
				}
				board[k][l] = 0;
				score = score + 4;
				placegems(board);
			}
		}
	}
	else if (row == 7 && col == 7) //dealing with bottom right corner
	{
		for (int k = row - 1; k <= row; k++)
		{
			for (int l = col -1; l <= col ; l++)
			{
				a = k;
				b = l;
				if ((k != a || l != b) && isflaminggem(board, k, l) == true)
				{
					flamingdeletion(board, k, l);
				}
				else if ((k != a || l != b) && isdestroyergem(board, k, l) == true)
				{
					destroyerdeletion(board, k, l);
				}
				board[k][l] = 0;
				score = score + 4;
				placegems(board);
			}
		}
	}
	else if (col > 0 && col < 7 && row == 0) //dealing with first row, exluding corner gems.
	{
		for (int k = row ; k <= row + 1; k++)
		{
			for (int l = col - 1; l <= col + 1; l++)
			{
				a = k;
				b = l;
				if ((k != a || l != b) && isflaminggem(board, k, l) == true)
				{
					flamingdeletion(board, k, l);
				}
				else if ((k != a || l != b) && isdestroyergem(board, k, l) == true)
				{
					destroyerdeletion(board, k, l);
				}
				board[k][l] = 0;
				score = score + 6;
				placegems(board);
			}
		}
	}
	else if (col > 0 && col < 7 && row == 7) //dealing with last row, excluding corner gems.
	{
		for (int k = row - 1; k <= row; k++)
		{
			for (int l = col - 1; l <= col + 1; l++)
			{
				a = k;
				b = l;
				if ((k != a || l != b) && isflaminggem(board, k, l) == true)
				{
					flamingdeletion(board, k, l);
				}
				else if ((k != a || l != b) && isdestroyergem(board, k, l) == true)
				{
					destroyerdeletion(board, k, l);
				}
				board[k][l] = 0;
				score = score + 6;
				placegems(board);
			}
		}
	}
	else if (row > 0 && row < 7 && col == 0) //dealing with first column, excluding corner gems.
	{
		for (int k = row - 1; k <= row + 1; k++)
		{
			for (int l = col; l <= col + 1; l++)
			{
				a = k;
				b = l;
				if ((k != a || l != b) && isflaminggem(board, k, l) == true)
				{
					flamingdeletion(board, k, l);
				}
				else if ((k != a || l != b) && isdestroyergem(board, k, l) == true)
				{
					destroyerdeletion(board, k, l);
				}
				board[k][l] = 0;
				score = score + 6;
				placegems(board);
			}
		}
	}
	else if (row > 0 && row < 7 && col == 7) //dealing with last column, excluding corner gems.
	{
		for (int k = row - 1; k <= row + 1; k++)
		{
			for (int l = col - 1; l <= col; l++)
			{
				a = k;
				b = l;
				if ((k != a || l != b) && isflaminggem(board, k, l) == true)
				{
					flamingdeletion(board, k, l);
				}
				else if ((k != a || l != b) && isdestroyergem(board, k, l) == true)
				{
					destroyerdeletion(board, k, l);
				}
				board[k][l] = 0;
				score = score + 6;
				placegems(board);
			}
		}
	}
}

void destroyerdeletion(int board[8][8], int row, int col)
/*This function deals with the deletion of destroyer gems. Whenever
a match contains a destroyer gem, this function is called. It has
two different for loops, one keeps the row number constant and 
destroys all the gems in that respective column. And the other 
loop does the opposite.*/
{
	for (int i = 0, j = col; i < 8; i++)
	{
		if ((i!=row || j!=col) && isflaminggem(board,i,j)==true)
		{
			flamingdeletion(board, i, j);
		}
		else if ((i != row || j != col) && isdestroyergem(board, i, j) == true)
		{
			destroyerdeletion(board, i, j);
		}
		else
		{
			board[i][j] = 0;

		}
		score = score + 8;
		placegems(board);
	}
	for (int i = row, j = 0; j < 8; j++)
	{
		if ((i != row || j != col) && isflaminggem(board, i, j) == true)
		{
			flamingdeletion(board, i, j);
		}
		else if ((i != row || j != col) && isdestroyergem(board, i, j) == true)
		{
			destroyerdeletion(board, i, j);
		}
		else
		{
			board[i][j] = 0;

		}
		score = score + 8;
		placegems(board);
	}
}

bool isflaminggem(int board[8][8], int row, int col)
/*This is a boolean function that returns true if the 
value and a specified location in a specified array is 
the value of a flaming gem.*/
{
	if (board[row][col] > 10 && board[row][col] < 20)
	{
		return true;
	}
}

bool isdestroyergem(int board[8][8], int row, int col)
/*This is a boolean function that returns true if the
value and a specified location in a specified array is
the value of a destroyer gem.*/
{
	if (board[row][col] > 20)
	{
		return true;
	}
}

bool isanyempty(int board[8][8])
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (board[i][j] == 0)
			{
				return true;
			}
		}
	}
	return false;
}

void cubedeletion(int board[8][8], int value)
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (board[i][j] % 10 == value)
			{
				if (isdestroyergem(board, i, j) == true)
				{
					destroyerdeletion(board, i, j);
				}
				if (isflaminggem(board, i, j) == true)
				{
					flamingdeletion(board, i, j);
				}
				board[i][j] = 0;
				placegems(board);
			}
		}
	}
}

void deleteduplicates(int board[8][8])
/*This function is responsible for destroying gems whenever it finds
that 3 or 4 gems are vertically or horizontally consecutive. If it 
finds 4 consecutive values, it turns one of them into a flaming gem.*/
{
	int value;
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (j < 4)
			{
				if ((board[i][j]!=0) && (board[i][j] % 10 == board[i][j + 1]) % 10 && (board[i][j + 1] % 10 == board[i][j + 2] % 10) && (board[i][j + 2] % 10 == board[i][j + 3] % 10) && (board[i][j + 3] % 10 == board[i][j + 4] % 10))
				{
					for (int k = i, l = j; l < j + 5; l++)
					{
						if (isdestroyergem(board, k, l) == true)
						{
							destroyerdeletion(board, k, l);
						}
						if (isflaminggem(board, k, l) == true)
						{
							flamingdeletion(board, k, l);
						}
					}
					board[i][j] = 0;
					board[i][j + 1] = 0;
					board[i][j + 3] = 0;
					board[i][j + 4] = 0;
					placegems(board);
					board[i][j + 2] = 69;
					placegems(board);
					score = score + 5;
				}
			}
			if (i < 4)
			{
				if ((board[i][j] != 0) && (board[i][j] % 10 == board[i + 1][j]) % 10 && (board[i + 1][j] % 10 == board[i + 2][j] % 10) && (board[i + 2][j] % 10 == board[i + 3][j] % 10) && (board[i + 3][j] % 10 == board[i + 4][j] % 10))
				{
					value = board[i][j];
					for (int k = i, l = j; k < i + 4; k++)
					{
						if (isdestroyergem(board, k, l) == true)
						{
							destroyerdeletion(board, k, l);
						}
						if (isflaminggem(board, k, l) == true)
						{
							flamingdeletion(board, k, l);
						}
					}
					board[i][j] = 0;
					board[i + 1][j] = 0;
					board[i + 3][j] = 0;
					board[i + 4][j] = 0;
					placegems(board);
					board[i + 2][j] = 69;
					placegems(board);
					score = score + 5;
				}
			}
		}
	}
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (j < 5)
			{
				if ((board[i][j]!=0) && ((board[i][j] % 10) == (board[i][j + 1] % 10)) && ((board[i][j + 1] % 10) == (board[i][j + 2] % 10)) && ((board[i][j + 2] % 10) == (board[i][j + 3] % 10)))
				{
					value = board[i][j];
					for (int k = i, l = j; l < j + 4; l++)
					{
						if (isdestroyergem(board, k, l) == true)
						{
							destroyerdeletion(board, k, l);
						}
						if (isflaminggem(board, k, l) == true)
						{
							flamingdeletion(board, k, l);
						}
					}
					board[i][j + 2] = value + 10;
					board[i][j] = 0;
					board[i][j + 1] = 0;
					board[i][j + 3] = 0;
					score = score + 4;
					placegems(board);
				}
				else if ((board[i][j] != 0) && ((board[i][j] % 10) == (board[i][j + 1] % 10)) && ((board[i][j + 1] % 10) == (board[i][j + 2] % 10)))
				{
					for (int k = i, l = j; l < j + 3; l++)
					{
						if (isdestroyergem(board, k, l) == true)
						{
							destroyerdeletion(board, k, l);
						}
						if (isflaminggem(board, k, l) == true)
						{
							flamingdeletion(board, k, l);
						}
					}
					board[i][j] = 0;
					board[i][j + 1] = 0;
					board[i][j + 2] = 0;
					score = score + 3;
					placegems(board);
				}
			}
			if (j == 5)
			{
				if ((board[i][j] != 0) && ((board[i][j] % 10) == (board[i][j + 1] % 10)) && ((board[i][j + 1] % 10) == (board[i][j + 2] % 10)))
				{
					for (int k = i, l = j; l < j + 3; l++)
					{
						if (isdestroyergem(board, k, l) == true)
						{
							destroyerdeletion(board, k, l);
						}
						if (isflaminggem(board, k, l) == true)
						{
							flamingdeletion(board, k, l);
						}
					}
					board[i][j] = 0;
					board[i][j + 1] = 0;
					board[i][j + 2] = 0;
					score = score + 3;
					placegems(board);
				}
			}
		}
	}
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (i < 5)
			{
				if ((board[i][j] != 0) && ((board[i][j] % 10) == (board[i + 1][j] % 10)) && ((board[i + 1][j] % 10) == (board[i + 2][j] % 10)) && ((board[i + 2][j] % 10) == (board[i + 3][j] % 10)))
				{
					value = board[i][j];
					for (int k = i, l = j; k < i+4; k++)
					{
						if (isdestroyergem(board, k, l) == true)
						{
							destroyerdeletion(board, k, l);
						}
						if (isflaminggem(board, k, l) == true)
						{
							flamingdeletion(board, k, l);
						}
					}
					board[i + 2][j] = value + 10;
					board[i][j] = 0;
					board[i + 1][j] = 0;
					board[i + 3][j] = 0;
					score = score + 4;
					placegems(board);
				}
				else if ((board[i][j] != 0) && ((board[i][j] % 10) == (board[i + 1][j] % 10)) && ((board[i + 1][j] % 10) == (board[i + 2][j] % 10)))
				{
					for (int k = i, l = j; k < i+3; k++)
					{
						if (isdestroyergem(board, k, l) == true)
						{
							destroyerdeletion(board, k, l);
						}
						if (isflaminggem(board, k, l) == true)
						{
							flamingdeletion(board, k, l);
						}
					}
					board[i][j] = 0;
					board[i + 1][j] = 0;
					board[i + 2][j] = 0;
					score = score + 3;
					placegems(board);
				}
			}
			if (i == 5)
			{
				if ((board[i][j] != 0) && ((board[i][j] % 10) == (board[i + 1][j] % 10)) && ((board[i + 1][j] % 10) == (board[i + 2][j] % 10)))
				{
					for (int k = i, l = j; k < i+3; k++)
					{
						if (isdestroyergem(board, k, l) == true)
						{
							destroyerdeletion(board, k, l);
						}
						if (isflaminggem(board, k, l) == true)
						{
							flamingdeletion(board, k, l);
						}
					}
					board[i][j] = 0;
					board[i + 1][j] = 0;
					board[i + 2][j] = 0;
					score = score + 3;
					placegems(board);
				}
			}
		}
	}
}

void moveemptytotop(int arr[8][8])
{
	//These two loops are for searching through whole array
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (arr[i][j] == 0)
				//This loop is for vertical swapping.
				for (int k = i; k > 0; k--)
				{
				swap(arr[k][j], arr[k - 1][j]);
				placegems(arr);
				}
		}
	}
}

void addnewgems(int array[][8], int rows)
{
	srand(time(0));	//Seeds random number by current time value to ensure randomness.
	for (int rownumber = 0; rownumber < rows; rownumber++)
	{
		for (int columnnumber = 0; columnnumber < 8; columnnumber++)
		{
			if (array[rownumber][columnnumber] == 0)
			{
				array[rownumber][columnnumber] = 1 + rand() % 5; //Places a random value from 1 to 5 in the array.
				placegems(array);
			}
		}
	}
}

void cursor(int row, int col, int r, int g, int b)
{
	myLine(col, row, col + 43, row, r, g, b);
	myLine(col, row + 43, col + 43, row + 43, r, g, b);
	myLine(col, row, col, row + 43, r, g, b);
	myLine(col + 43, row, col + 43, row + 43, r, g, b);
}

/*The following functions are all graphics related*/

void displayboard()
/*Prints 9 vertical and 9 horizontal lines
on the screen using for loops. This draws 
the board for our gems.*/
{
	for (int i = 150; i <= 550; i = i + 50)//to print vertical lines
	{
		myLine(i, 50, i, 450, 255,255,255);
	}
	for (int j = 50; j <= 450; j = j + 50)//to print horizontal lines
	{
		myLine(150, j, 550, j,255,255,255);
	}
}

/*The following are all the gems used in this game
There are a total of 16 gems. Gem1,Gem2,Gem3,Gem4 and Gem5.
Each Gem has 2 of its own special gems. For example, Gem1
will have a gem1flaming and a gem1destroyer. There is also
an empty gem, which is basically a black square, used to 
delete any gem from the board.*/
void empty(int k, int l)
{
	myRect(k + 5, l + 5, k + 45, l + 45, 0, 0, 0, 0, 0, 0);
}

void gem1(int k, int l)
{
	myTriangle(k + 8, l + 8, k + 40, l + 40, 237, 67, 55, 237, 67, 55);
}

void gem1flaming(int k, int l)
{
	myTriangle(k + 8, l + 8, k + 40, l + 40, 255, 255, 255, 237, 67, 55);
}

void gem1destroyer(int k, int l)
{
	myTriangle(k + 8, l + 8, k + 40, l + 40, 135, 206, 250, 237, 67, 55);
}

void gem2(int k, int l)
{
	myRect(k + 8, l + 8, k + 40, l + 40, 192, 216, 144, 192, 216, 144);
}

void gem2flaming(int k, int l)
{
	myRect(k + 8, l + 8, k + 40, l + 40, 255, 255, 255, 192, 216, 144);
}

void gem2destroyer(int k, int l)
{
	myRect(k + 8, l + 8, k + 40, l + 40, 135, 206, 250, 192, 216, 144);
}

void gem3(int k, int l)
{
	myRhombus(k + 8, l + 8, k + 40, l + 40, 255, 252, 127, 255, 252, 127);
}

void gem3flaming(int k, int l)
{
	myRhombus(k + 8, l + 8, k + 40, l + 40, 255, 255, 255, 255, 252, 127);
}

void gem3destroyer(int k, int l)
{
	myRhombus(k + 8, l + 8, k + 40, l + 40, 135, 206, 250, 255, 252, 127);
}

void gem4(int k, int l)
{
	myEllipse(k + 8, l + 8, k + 40, l + 40, 255, 126, 71, 255, 126, 71);
}

void gem4flaming(int k, int l)
{
	myEllipse(k + 8, l + 8, k + 40, l + 40, 255, 255, 255, 255, 126, 71);
}

void gem4destroyer(int k, int l)
{
	myEllipse(k + 8, l + 8, k + 40, l + 40, 135, 206, 250, 255, 126, 71);
}

void gem5(int k, int l)
{
	myDiamond(k + 8, l + 8, k + 40, l + 40, 65, 105, 225, 65, 105, 225);
}

void gem5flaming(int k, int l)
{
	myDiamond(k + 8, l + 8, k + 40, l + 40, 255, 255, 225, 65, 105, 225);
}

void gem5destroyer(int k, int l)
{
	myDiamond(k + 8, l + 8, k + 40, l + 40, 135, 206, 250, 65, 105, 225);
}

void cubegem(int k, int l)
{
	myCube(k + 8, l + 8, k + 40, l + 40, 255, 255, 255);
}

void placegems(int game[][8])
/*This function uses nested for loops to map 
and translate an array, into graphics. It uses
if statements to place specific gems according
their specific values, at intervals of 50 pixels,
on the screen. This is how the board is filled
with gems.*/
{
	for (int ycoordinates = 50, i = 0; ycoordinates < 450; ycoordinates = ycoordinates + 50, i++)
	{
		int l = ycoordinates;
		for (int xcoordinates = 150, j = 0; xcoordinates < 550; xcoordinates = xcoordinates + 50, j++)
		{
			int k = xcoordinates;

			if (game[i][j] == 0)
			{
				empty(k, l);
			}
			else if (game[i][j] == 1)
			{
				gem1(k, l);
			}
			else if (game[i][j] == 2)
			{
				gem2(k, l);
			}
			else if (game[i][j] == 3)
			{
				gem3(k, l);
			}
			else if (game[i][j] == 4)
			{
				gem4(k, l);
			}
			else if (game[i][j] == 5)
			{
				gem5(k, l);
			}
			else if (game[i][j] == 11)
			{
				gem1flaming(k, l);
			}
			else if (game[i][j] == 21)
			{
				gem1destroyer(k, l);
			}
			else if (game[i][j] == 12)
			{
				gem2flaming(k, l);
			}
			else if (game[i][j] == 22)
			{
				gem2destroyer(k, l);
			}
			else if (game[i][j] == 13)
			{
				gem3flaming(k, l);
			}
			else if (game[i][j] == 23)
			{
				gem3destroyer(k, l);
			}
			else if (game[i][j] == 14)
			{
				gem4flaming(k, l);
			}
			else if (game[i][j] == 24)
			{
				gem4destroyer(k, l);
			}
			else if (game[i][j] == 15)
			{
				gem5flaming(k, l);
			}
			else if (game[i][j] == 25)
			{
				gem5destroyer(k, l);
			}
			else if (game[i][j] == 69)
			{
				cubegem(k, l);
			}
		}
	}
}

void deletegems(int board[8][8])
/*This function was made for debugging purposes.
It places an empty gem over all of the gems of
the board. Hence deleting all the gems from 
display.*/
{
	for (int ycoordinates = 50, i = 0; ycoordinates < 450; ycoordinates = ycoordinates + 50, i++)
	{
		int l = ycoordinates;
		for (int xcoordinates = 150, j = 0; xcoordinates < 550; xcoordinates = xcoordinates + 50, j++)
		{
			int k = xcoordinates;
			empty(k, l);
		}
	}
}

void removespecificgem(int board[8][8],int i,int j)
/*This function takes an array and a rownumber and a columnnumber
as input. And it then removes or deletes the gem at that location
from display. It does not alter the actual array.*/
{
	for (int ycoordinates = 50, a = 0; ycoordinates < 450; ycoordinates = ycoordinates + 50, a++)
	{
		int l = ycoordinates;
		for (int xcoordinates = 150, b=0; xcoordinates < 550; xcoordinates = xcoordinates + 50, b++)
		{
			int k = xcoordinates;
			if (a == i && b == j)
			{
				empty(k, l);
			}
		}
	}
}

int main()
{
	ofstream storedata("savedata.txt");
	ifstream readdata("savedata.txt");
	srand(time(0));
	int game[8][8];
	int starttime = time(0);
	while (findmatches(game) == true)
	{
		randomizeboard(game, 8);
	}
	//printboard(game, 8);
	displayboard();
	placegems(game);
	int row = 53, col = 153;
	int key = 0;
	int i = 0, j = 0;
	isCursorKeyPressed(key);
	int timediff=60-(time(0)-starttime);
	while (timediff>=0)
	{
		gotoxy(0, 0);
		printboard(game, 8);
		gotoxy(2, 40);
		cout << "Time Remaining:";
		if (timediff > 9)
		{
			gotoxy(24, 40);
			cout << timediff << endl << endl;
		}
		else
		{
			gotoxy(24, 40);
			cout << " "<< timediff << endl << endl;
		}
		cout << "	   Score:	"<< score;
		cursor(row, col, 255, 255, 255);
		bool pressed = isCursorKeyPressed(key);
		if (key == 1 || key == 2 || key == 3 || key == 4 || key == 5)
		{
	
			if (key == 1 && j != 0 && pressed == true)	//move left
			{
				col = col - 50;
				cursor(row, col + 50, 0, 0, 0);
				j--;
			}
			if (key == 2 && i != 0 && pressed == true)	//move up
			{
				row = row - 50;
				cursor(row + 50, col, 0, 0, 0);
				i--;
			}
			if (key == 3 && j != 7 && pressed == true) //move right
			{
				col = col + 50;
				cursor(row, col - 50, 0, 0, 0);
				j++;
			}
			if (key == 4 && i != 7 && pressed == true)	//move down
			{
				row = row + 50;
				cursor(row - 50, col, 0, 0, 0);
				i++;
			}
			if (key == 6)	//save game
			{
				gotoxy(15, 20);
				printboard(game, 8);
				/*for (int i = 0; i < 8; i++)
				{
					for (int j = 0; j < 8; j++)
					{
						storedata << game[i][j];
					}
				}
				storedata << timediff;*/
			}
			if (key == 7 )	//load game
			{
				gotoxy(15, 20);
				printboard(game, 8);
				/*for (int i = 0; i < 8; i++)
				{
					for (int j = 0; j < 8; j++)
					{
						readdata >> game[i][j];
					}
				}
				readdata >> timediff;*/
			}
			if (key == 5 && pressed == true)
			{
				while (key == 5)
				{
					if (game[i][j] == 69)
					{
						pressed = isCursorKeyPressed(key);
						cursor(row, col, 0, 255, 0);
						if (key == 3 && j != 7 && pressed == true) //move right
						{
							swap(game[i][j], game[i][j + 1]);
							removespecificgem(game, i, j);
							removespecificgem(game, i, j + 1);
							placegems(game);
							game[i][j + 1] = 0;
							placegems(game);
							cubedeletion(game, game[i][j]);
						}
						if (key == 4 && i != 7 && pressed == true)	//move down
						{
							swap(game[i][j], game[i + 1][j]);
							removespecificgem(game, i, j);
							removespecificgem(game, i + 1, j);
							placegems(game);
							game[i + 1][j] = 0;
							placegems(game);
							cubedeletion(game, game[i][j]);
						}
						if (key == 2 && i != 0 && pressed == true)	//move up
						{
							swap(game[i][j], game[i - 1][j]);
							removespecificgem(game, i, j);
							removespecificgem(game, i - 1, j);
							placegems(game);
							game[i - 1][j] = 0;
							placegems(game);
							cubedeletion(game, game[i][j]);
						}
						if (key == 1 && j != 0 && pressed == true)	//move left
						{
							swap(game[i][j], game[i][j - 1]);
							removespecificgem(game, i, j);
							removespecificgem(game, i, j - 1);
							placegems(game);
							game[i][j - 1] = 0;
							placegems(game);
							cubedeletion(game, game[i][j]);
						}
						placegems(game);
					}
					else
					{
						pressed = isCursorKeyPressed(key);
						cursor(row, col, 0, 255, 0);
						if (key == 3 && j != 7 && pressed == true) //move right
						{
							swap(game[i][j], game[i][j + 1]);
							removespecificgem(game, i, j);
							removespecificgem(game, i, j + 1);
							if (findmatches(game) == false)
							{
								swap(game[i][j], game[i][j + 1]);
							}
						}
						if (key == 4 && i != 7 && pressed == true)	//move down
						{
							swap(game[i][j], game[i + 1][j]);
							removespecificgem(game, i, j);
							removespecificgem(game, i + 1, j);
							if (findmatches(game) == false)
							{
								swap(game[i][j], game[i + 1][j]);
							}
						}
						if (key == 2 && i != 0 && pressed == true)	//move up
						{
							swap(game[i][j], game[i - 1][j]);
							removespecificgem(game, i, j);
							removespecificgem(game, i - 1, j);
							if (findmatches(game) == false)
							{
								swap(game[i][j], game[i - 1][j]);
							}
						}
						if (key == 1 && j != 0 && pressed == true)	//move left
						{
							swap(game[i][j], game[i][j - 1]);
							removespecificgem(game, i, j);
							removespecificgem(game, i, j - 1);
							if (findmatches(game) == false)
							{
								swap(game[i][j], game[i][j-1]);
							}
						}
						placegems(game);
					}
				}
				while (findmatches(game) == true || isanyempty(game)==true)
				{
					elbowmatch(game);
					deleteduplicates(game);
					moveemptytotop(game);
					addnewgems(game, 8);
					placegems(game);
				}
			}
			cursor(row, col, 255, 255, 255);
		}
		timediff = 60 - (time(0) - starttime);
	}
	gotoxy(0, 0);
	cout << "**********************************Game Over**********************************" << endl;
	cout << "**************************press any key to end game**************************";
	system("Pause");
}