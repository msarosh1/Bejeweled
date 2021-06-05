#include <iostream> 
#include <conio.h>
#include <time.h>

using namespace std;

void randomizeboard(int arr[][8], int rows) 
//function to randomize the elements of 2d array. It takes as input, a 2d array with 8 columns, and its number of rows as input.
{
	srand(time(0));		//the srand function seeds random values to be used in the rand function.
	//time(0) ensures that the values seeded are not the same each time.
	for (int rownumber = 0; rownumber < 8; rownumber++)	//this loop runs through each of the 8 rows of the array.
	{
		for (int columnnumber = 0; columnnumber < 8; columnnumber++)//this loop goes to each column of the array, for each row.
			arr[rownumber][columnnumber] = 1 + rand() % 5;		//to assign a random value from 1 to 5 to each element of the array.
	}
}

void printboard(int arr[][8], int rows)
{
	for (int rownumber = 0; rownumber < 8; rownumber++)
	{
		for (int columnnumber = 0; columnnumber < 8; columnnumber++)
		{
			cout << arr[rownumber][columnnumber] << " ";
		}
		cout << endl;
	}
}



bool findmatches(int arr[][8], int rows)
//This function takes an array and its number of rows and scans the whole array for vertical or horizontal repeating values.
//Returns true if any matches of 3 or more consecutively same, horizontal or vertical values is found.
{
	bool match = false;
	for (int rownumber = 0; rownumber < rows; rownumber++)//this loop runs through each of the 8 rows of the array.
	{
		for (int columnnumber = 0; columnnumber < 8; columnnumber++)//this loop goes to each column of the array, for each row.
		{
			if (rownumber == 0 || rownumber == 7 || columnnumber == 0 || columnnumber == 7)
			//checks if it is the first or last row, or the first or last column of the array.
			{
				if (rownumber != columnnumber && ((rownumber + columnnumber) != 7))
				/*ensures that the following code does not run for the corner values of the array.
				To prevent the check from going out of bounds.*/
				{
					if (rownumber == 0 || rownumber == 7)
					//ensures that it is the first or the last row of the array.
					{
						if ((arr[rownumber][columnnumber - 1] == arr[rownumber][columnnumber]) && (arr[rownumber][columnnumber + 1] == arr[rownumber][columnnumber]))
						//checks for a horizonatal match of 3 consecutive values.
						{
							match = true;//indicates that a match has been found;
							break;//prevents the loop from searching further.
						}
					}
					else //for the first and last column.
						if ((arr[rownumber - 1][columnnumber] == arr[rownumber][columnnumber]) && (arr[rownumber + 1][columnnumber] == arr[rownumber][columnnumber]))
						//checks for a vertical match of three consecutive values.
						{
							match = true;//indicates that a match has been found;
							break;//prevents the loop from searching further.
						}
				}
			}
			else
			//Performs the following check for all the rows and columns except the first and last ones.
				if (((arr[rownumber][columnnumber - 1] == arr[rownumber][columnnumber]) && (arr[rownumber][columnnumber + 1] == arr[rownumber][columnnumber])) || ((arr[rownumber - 1][columnnumber] == arr[rownumber][columnnumber]) && (arr[rownumber + 1][columnnumber] == arr[rownumber][columnnumber])))
				//checks for vertical and horizontal matches of three consecutive values. 
				{
					match = true; // indicates that a match has been found;
					break; //prevents the loop from searching further.
				}
		}
	}
	return match;//returns true if consecutive values are found. Otherwise returns false.
}

void consecutive4(int arr[][8])
{
	for (int rownumber = 0; rownumber < 8; rownumber++)
	{
		for (int columnnumber = 0; columnnumber < 8; columnnumber++)
		{
			if (columnnumber < 5)
			{
				if ((arr[rownumber][columnnumber] == arr[rownumber][columnnumber + 1]) && (arr[rownumber][columnnumber + 1] == arr[rownumber][columnnumber + 2]) && (arr[rownumber][columnnumber + 2] == arr[rownumber][columnnumber + 3]))
				{
					arr[rownumber][columnnumber] = arr[rownumber][columnnumber] + 10;
					arr[rownumber][columnnumber + 1] = 0;
					arr[rownumber][columnnumber + 2] = 0;
					arr[rownumber][columnnumber + 3] = 0;
				}
			}
			if (rownumber < 5)
			{
				if ((arr[rownumber][columnnumber] == arr[rownumber + 1][columnnumber]) && (arr[rownumber + 1][columnnumber] == arr[rownumber + 2][columnnumber]) && (arr[rownumber + 2][columnnumber] == arr[rownumber + 3][columnnumber]))
				{
					arr[rownumber][columnnumber] = arr[rownumber][columnnumber] + 10;
					arr[rownumber + 1][columnnumber] = 0;
					arr[rownumber + 2][columnnumber] = 0;
					arr[rownumber + 3][columnnumber] = 0;
				}
			}
		}
	}
}

void elbowmatch(int arr[8][8])
{
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			if (arr[i][j] == arr[i][j + 1] && arr[i][j + 1] == arr[i][j + 2] && arr[i][j] == arr[i + 1][j] && arr[i + 1][j] == arr[i + 2][j])
				arr[i][j] = arr[i][j] + 20;
		}
	}
	for (int i = 7; i > 2; i--)
	{
		for (int j = 7; j > 2; j--)
		{
			if (arr[i][j] == arr[i][j - 1] && arr[i][j - 1] == arr[i][j - 2] && arr[i][j] == arr[i - 1][j] && arr[i - 1][j] == arr[i - 2][j])
				arr[i][j] = arr[i][j] + 20;
		}
	}
}

void removeduplicates(int arr[][8])
{
	for (int rownumber = 0; rownumber < 8; rownumber++)
	{
		for (int columnnumber = 0; columnnumber < 8; columnnumber++)
		{
			if (columnnumber < 6)
			{
				if ((arr[rownumber][columnnumber] == arr[rownumber][columnnumber + 1]) && (arr[rownumber][columnnumber + 1] == arr[rownumber][columnnumber + 2]))
				{
					arr[rownumber][columnnumber] = 0;
					arr[rownumber][columnnumber + 1] = 0;
					arr[rownumber][columnnumber + 2] = 0;
				}
			}
			if (rownumber < 6)
			{
				if ((arr[rownumber][columnnumber] == arr[rownumber + 1][columnnumber]) && (arr[rownumber + 1][columnnumber] == arr[rownumber + 2][columnnumber]))
				{
					arr[rownumber][columnnumber] = 0;
					arr[rownumber + 1][columnnumber] = 0;
					arr[rownumber + 2][columnnumber] = 0;
				}
			}
		}
	}
}

void moveemptytotop(int arr[][8], int rows)
{
	for (int rownumber = 0; rownumber < rows; rownumber++)
	{
		for (int columnnumber = 0; columnnumber < 8; columnnumber++)
		{
			if (arr[rownumber][columnnumber] == 0)
				for (int k = rownumber; k > 0; k--)
				{
				swap(arr[k][columnnumber], arr[k - 1][columnnumber]);
				}
		}
	}
}

void addnewgems(int array[][8], int rows)
{
	srand(time(0));
	for (int rownumber = 0; rownumber < rows; rownumber++)
	{
		for (int columnnumber = 0; columnnumber < 8; columnnumber++)
		{
			if (array[rownumber][columnnumber] == 0)
			{
				array[rownumber][columnnumber] = 1 + rand() % 5;
			}
		}
	}
}

int main()
{
	int game[8][8];
	randomizeboard(game, 8);
	//while (countmatches(game,8) != 0)
	//{
	//	randomizeboard(game, 8);
	//}
	printboard(game, 8);
	cout << endl << endl << findmatches(game, 8) << endl << endl;
	elbowmatch(game);
	consecutive4(game);
	removeduplicates(game);
	printboard(game, 8);
	moveemptytotop(game, 8);
	cout << endl << endl;
	printboard(game, 8);
	addnewgems(game, 8);
	cout << endl << endl;
	printboard(game, 8);
	_getch();
}