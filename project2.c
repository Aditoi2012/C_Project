/* ENGGEN131 Project - C Project - 2021 */
/* Container Yard */

/* << Include your information here - name, user name, ID number >> */

#include <stdio.h>
#define NUM_ROWS 8
#define NUM_COLS 8

#define VACANT 0
#define BOUNDARY -1
#define ENTRY -2
#define EXIT -3

void InitialiseFloor(int floor[NUM_ROWS][NUM_COLS], char entryboundary, int index);
void PrintFloor(int floor[NUM_ROWS][NUM_COLS]);
double FloorAreaAvailable(int floor[NUM_ROWS][NUM_COLS], double length, double width);
void AddContainer(int floor[NUM_ROWS][NUM_COLS], int position, int size, int direction);
int LocateContainer(int floor[NUM_ROWS][NUM_COLS], char move, int *rowStart, int *colStart, int *rowEnd, int *colEnd);
int MoveContainer(int floor[NUM_ROWS][NUM_COLS], int r0, int c0, int r1, int c1, int isBlocked);

/*
Your comment should go here – it should describe the purpose of the function and a
brief summary of the algorithm you have used to solve the task (this comment must
be written in your own words
*/
int main()
{
	int floor[NUM_ROWS][NUM_COLS];

	/* Simple test code for Tasks 1 and 2 */
	int rowA, colA, rowB, colB;
	int result, isBlocked;
	InitialiseFloor(floor, 'R', 3);
	AddContainer(floor, 25, 2, 0);
	PrintFloor(floor);
	// Move container A:
	isBlocked = LocateContainer(floor, 'A', &rowA, &colA,
								&rowB, &colB);
	result = MoveContainer(floor, rowA, colA, rowB, colB,
						   isBlocked);
	printf("Result = %d\n", result);
	PrintFloor(floor);
}
/*
This function sets up the grid layout of the program. It is done with
integer values of 0, -1, -2, -3 corresponding to vacant space, boundary
entry and exit respectively. It does so by iterating a for loop where
the boundary and vacant spaces are created. Then, using if variables,
it checks where to put the entry and exit on the boundary.
*/
void InitialiseFloor(int floor[NUM_ROWS][NUM_COLS], char entryboundary, int index)
{
	int i, j;
	i = 0;
	j = 0;

	/*
	This iterates through the required number of rows and columns and 
	makes the boundary and empty space.
	*/
	for (i = 0; i < NUM_ROWS; i++)
	{
		for (j = 0; j < NUM_COLS; j++)
		{
			if (i == NUM_ROWS - 1 || j == NUM_ROWS - 1 || i == 0 || j == 0)
			{
				floor[i][j] = BOUNDARY;
			}
			else
			{
				floor[i][j] = VACANT;
			}
		}
	}

	/*
	This checks where to put the entry and exit of the grid on the
	boundary by running it through if variables.
	*/

	if (entryboundary == 'L')
	{
		floor[index][0] = ENTRY;
		floor[index][NUM_COLS - 1] = EXIT;
	}
	else if (entryboundary == 'R')
	{
		floor[index][NUM_COLS - 1] = ENTRY;
		floor[index][0] = EXIT;
	}
	else if (entryboundary == 'T')
	{
		floor[0][index] = ENTRY;
		floor[NUM_COLS - 1][index] = EXIT;
	}
	else
	{
		floor[NUM_COLS - 1][index] = ENTRY;
		floor[0][index] = EXIT;
	}
}

/*
This function prints the grid with response to the orginal numeric
grid. It iterates through the grid provided and checks for the 
corresponding integers and prints a character accordingly.
Author: Aditya Sohani
*/
void PrintFloor(int floor[NUM_ROWS][NUM_COLS])
{
	int i = 0;
	int j = 0;
	/*
	This iterates through the grid and checks
	for the integer value and sets the grid
	element to a character so that it's easier
	to see.
	*/
	for (i = 0; i < NUM_ROWS; i++)
	{
		for (j = 0; j < NUM_COLS; j++)
		{
			if (floor[i][j] == -1)
			{
				printf("@");
			}
			else if (floor[i][j] == 0)
			{
				printf(" ");
			}
			else if (floor[i][j] == -2)
			{
				printf("U");
			}
			else if (floor[i][j] == -3)
			{
				printf("X");
			}
			// This is for any other characters
			// other than numbers i.e. containers.
			else
			{
				printf("%c", floor[i][j]);
			}
		}
		printf("\n");
	}
}
/*
This function calculates the remaining area of the grid. It does so
by going through the entire grid and checking for elements where there
is an empty space i.e. vacancy. It does with for loop to iterate
and if variable to check if it's a free spot.
Author: Aditya Sohani
*/
double FloorAreaAvailable(int floor[NUM_ROWS][NUM_COLS], double length, double width)
{
	double free = 0;
	int counter = 0;
	double cellArea = 0;
	cellArea = length * width;
	//calculate the area of each grid cell
	int i;
	int j;
	for (i = 0; i < NUM_ROWS; i++)
	{
		for (j = 0; j < NUM_COLS; j++)
		{
			if (floor[i][j] == VACANT)
			{
				//Adds to the number vacant spots
				counter = counter + 1;
			}
		}
	}
	// Free space is the cell area multiplied by the
	// number of cells.
	free = counter * cellArea;
	return free;
}

/*
This function adds container to the grid given the direction,
position, the size. It determines the row and column of the
given position and then checks if container would not obstruct
with anything including boundary. 
*/
void AddContainer(int floor[NUM_ROWS][NUM_COLS], int position, int size, int direction)
{
	int i;
	int k;
	int l;
	int posR = position / NUM_COLS;
	int posC = position % NUM_COLS;
	int check = 1;
	char letter = '@';

	//This determines the letter that needs to be assigned
	//to the container.
	for (k = 0; k < NUM_ROWS; k++)
	{
		for (l = 0; l < NUM_COLS; l++)
		{
			if (floor[k][l] >= letter)
			{
				letter = floor[k][l];
			}
		}
	}

	//This checks if the position given is feasible and then checks if the
	//size is below the boundary and then gives assigns the container letter.
	if ((posR < NUM_ROWS - 1 && posR != 0) && posC > 0 && posC < NUM_COLS)
	{
		if (floor[posR][posC] == VACANT && direction == 0 && (posC + size < NUM_COLS))
		{
			for (i = posC; i < posC + size; i++)
			{
				if (floor[posR][i] != VACANT)
				{
					check = 0;
				}
			}

			if (check == 1)
			{
				for (i = posC; i < posC + size; i++)
				{
					floor[posR][i] = letter + 1;
				}
			}
		}

		else if (floor[posR][posC] == VACANT && direction == 1 && (posR + size < NUM_COLS))
		{
			for (i = posR; i < posR + size; i++)
			{
				if (floor[i][posC] != VACANT)
				{
					check = 0;
				}
			}

			if (check == 1)
			{
				for (i = posR; i < posR + size; i++)
				{
					floor[i][posC] = letter + 1;
				}
			}
		}
	}
	return;
}

/*
This function checks if the container in the grid is blocked or not.
This does so but checking the corresponding elements next to it.
It also finds the first occuring and last occuring instance of the 
container.
*/

int LocateContainer(int floor[NUM_ROWS][NUM_COLS], char move, int *rowStart, int *colStart, int *rowEnd, int *colEnd)
{
	int i, j;
	int rowCounter = 0;
	int colCounter = 0;
	int horizontal = 0;

	// Iterates through the grid and if it finds the container
	// in it, it stores the starting and ending column and row.
	for (i = 0; i < NUM_ROWS; i++)
	{
		for (j = 0; j < NUM_COLS; j++)
		{
			if (floor[i][j] == move && floor[i][j + 1] == move)
			{
				colCounter = colCounter + 1;
				*colEnd = j + 1;
				*rowEnd = i;
				horizontal = 1;
			}
			else if (floor[i][j] == move && floor[i + 1][j] == move)
			{
				rowCounter = rowCounter + 1;
				*rowEnd = i + 1;
				*colEnd = j;
			}
		}
	}

	// This calculates the start column and row for the container.
	*rowStart = *rowEnd - rowCounter;
	*colStart = *colEnd - colCounter;

	// This checks if the there is vacant spot next to the container.
	if (horizontal == 1 && (floor[*rowEnd][*colEnd + 1] == VACANT || floor[*rowEnd][*colStart - 1] == VACANT))
	{
		return 1;
	}
	else if (horizontal == 0 && (floor[*rowEnd + 1][*colEnd] == VACANT || floor[*rowStart - 1][*colEnd] == VACANT))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

/*
	This function moves the container to most extent
	given the rows and columns of the starting and 
	ending point of the container. It also checks if
	it is next to the entry/exit of the grid and returns
	a corresponding value if it is.

*/

int MoveContainer(int floor[NUM_ROWS][NUM_COLS], int r0, int c0, int r1, int c1, int isBlocked)
{
	int i, j;
	int altc0 = c0;
	int altc1 = c1;
	int altr0 = r0;
	int altr1 = r1;
	int horizontal = 0;
	// This checks if it is horizontal or vertical
	if (r0 == r1)
	{
		horizontal = 1;
		//Checks if the left value of the first point
		//is vacant and then executes code
		if (floor[r0][c0 - 1] == VACANT)
		{
			for (i = 0; i < altc0 - 1; i++)
			{
				if (floor[r0][c0 - 1] == VACANT)
				{
					for (j = c0; j <= altc1; j++)
					{
						floor[r0][j - 1] = floor[r0][j];
						floor[r0][j] = VACANT;
					}
					//updates the value of the two end points
					c0 = c0 - 1;
					c1 = c1 - 1;
				}
			}
		}
		//Else if it checks if the element to the right is
		else if (floor[r0][c1 + 1] == VACANT)
		{
			for (i = 0; i < NUM_COLS - altc1 - 2; i++)
			{
				if (floor[r0][c1 + 1] == VACANT)
				{
					for (j = c1; j >= altc0; j--)
					{
						floor[r0][j + 1] = floor[r0][j];
						floor[r0][j] = VACANT;
					}
					c1 = c1 + 1;
					c0 = c0 + 1;
				}
			}
		}
	}

	//Checks if the columns are the same i.e vertical
	else if (c1 == c0)
	{
		//Checks if element above is vacant
		if (floor[r0 - 1][c0] == VACANT)
		{
			for (i = 0; i < altr0 - 1; i++)
			{
				if (floor[r0 - 1][c0] == VACANT)
				{
					for (j = r0; j <= altr1; j++)
					{
						floor[j - 1][c0] = floor[j][c0];
						floor[j][c0] = VACANT;
					}
					//Updates rows
					r0 = r0 - 1;
					r1 = r1 - 1;
				}
			}
		}
		//Else if element below is vacant
		else if (floor[r1 + 1][c0] == VACANT)
		{
			for (i = 0; i < NUM_ROWS - 2 - altr1; i++)
			{
				if (floor[r1 + 1][c0] == VACANT)
				{
					for (j = r1; j >= altr0; j--)
					{
						floor[j + 1][c0] = floor[j][c0];
						floor[j][c0] = VACANT;
					}
					//Updates rows
					r1 = r1 + 1;
					r0 = r0 + 1;
				}
			}
		}
	}
	//If it is horizontal, it will check the two end points
	//neighbouring element and see if it is entry or exit
	if (horizontal == 1)
	{
		if (floor[r0][c1 + 1] == ENTRY || floor[r0][c0 - 1] == ENTRY)
		{
			return 1;
		}
		else if (floor[r0][c1 + 1] == EXIT || floor[r0][c0 - 1] == EXIT)
		{
			return 2;
		}
		else if (isBlocked == 0)
		{
			return -1;
		}

		else
		{
			return 0;
		}
	}
	//Else it is vertical, it will check the two end points
	//neighbouring element and see if it is entry or exit
	else if (horizontal == 0)
	{
		if (floor[r0 - 1][c0] == ENTRY || floor[r1 + 1][c0] == ENTRY)
		{
			return 1;
		}
		else if (floor[r0 - 1][c0] == EXIT || floor[r1 + 1][c0] == EXIT)
		{
			return 2;
		}
		else if (isBlocked == 0)
		{
			return -1;
		}

		else
		{
			return 0;
		}
	}
	return 0;
}
