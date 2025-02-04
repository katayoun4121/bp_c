// Pacman Game in C language
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
// All the elements to be used
// Declared here
#define WIDTH 60
#define HEIGHT 30
#define PACMAN '>'
#define WALL '|'
#define FOOD '$'
#define EMPTY ' '
#define DEMON '*'
#define ENEMY 'E'
#define AWARD '@'
// Global Variables are
// Declared here
int res = 0;
int score = 0;
int pacman_x, pacman_y;
int enemy_x, enemy_y;
int award_x, award_y;
int food = 0;
int curr = 0;
int award = 0;
typedef struct
{
	char type;
	int award;

} pack;
pack board[HEIGHT][WIDTH];
void initialize()
{
	// Putting Walls as boundary in the Game
	for (int i = 0; i < HEIGHT; i++)
	{
		for (int j = 0; j < WIDTH; j++)
		{
			if (i == 0 || j == WIDTH - 1 || j == 0 || i == HEIGHT - 1)
			{
				board[i][j].type = WALL;
			}
			else
				board[i][j].type = EMPTY;
		}
	}
	// Putting Walls inside the Game
	int count = 50;
	while (count != 0)
	{
		int i = (rand() % (HEIGHT + 1));
		int j = (rand() % (WIDTH + 1));
		if (board[i][j].type != WALL && board[i][j].type != PACMAN)
		{
			board[i][j].type = WALL;
			count--;
		}
	}
	int val = 5;
	while (val--)
	{
		int column = (rand() % (WIDTH + 1));
		for (int i = 3; i < HEIGHT - 3; i++)
		{
			if (board[i][column].type != WALL && board[i][column].type != PACMAN)
			{
				board[i][column].type = WALL;
			}
		}
	}
	// Putting Demons in the Game
	count = 10;
	while (count != 0)
	{
		int i = (rand() % (HEIGHT + 1));
		int j = (rand() % (WIDTH + 1));
		if (board[i][j].type != WALL && board[i][j].type != PACMAN)
		{
			board[i][j].type = DEMON;
			count--;
		}
	}
	// putting new char as award named '@'
	int num = 28;
	while (num != 0)
	{
		int i = (rand() % (HEIGHT));
		int j = (rand() % (WIDTH));
		if (board[i][j].type != PACMAN && board[i][j].type != DEMON && board[i][j].type != ENEMY &&board[i][j].type !=WALL)
		{
			board[i][j].award = award ;
			num--;
		}
	}
	// putting new enemy as character E
	count = 20;
	while (count != 0)
	{
		int i = (rand() % (HEIGHT));
		int j = (rand() % (WIDTH));
		if (board[i][j].type != WALL && board[i][j].type != PACMAN && board[i][j].type != DEMON && board[i][j].award!= award)
		{
			board[i][j].type = ENEMY;
			count--;
		}
	}
	// Cursor at Center
	pacman_x = WIDTH / 15;
	pacman_y = 18;
	board[pacman_y][pacman_x].type = PACMAN;
	// Dollars Placed
	for (int i = 0; i < HEIGHT; i++)
	{
		for (int j = 0; j < WIDTH; j++)
		{
			if (i % 2 == 1 && j % 2 == 0 && board[i][j].type != WALL && board[i][j].type != DEMON && board[i][j].type != PACMAN && board[i][j].type != ENEMY)
			{
				board[i][j].type = FOOD;
				food++;
				board[i][j].award = food;
			}
		}
	}
}
void draw()
{
	// Clear screen
	system("cls");
	// Drawing All the elements in the screen
	for (int i = 0; i < HEIGHT; i++)
	{
		for (int j = 0; j < WIDTH; j++)
		{
			printf("%c", board[i][j].type);
		}
		printf("\n");
	}
	printf("Score: %d\n", score);
}
// Function enables to move the Cursor
void move(int move_x, int move_y)
{
	int x = pacman_x + move_x;
	int y = pacman_y + move_y;
	if (board[y][x].type != WALL)
	{
		if (board[y][x].type == FOOD)
		{
			score++;
			food--;
			curr++;
			award++;
			if (food == 0)
			{
				res = 2;
				return;
			}
		}
		else if (board[y][x].type == DEMON && board[y][x].type == ENEMY && board[y][x].type == WALL)
		{
			res = 1;
		}
		else if (board[y][x].award == '@')
		{
			award++;
		}
		board[pacman_y][pacman_x].type = EMPTY;
		pacman_x = x;
		pacman_y = y;
		board[pacman_y][pacman_x].type = PACMAN;
	}
}
// placing the enemy E
void PlaceEnemy()
{
	enemy_x = rand() % HEIGHT;
	enemy_y = rand() % WIDTH;
	board[enemy_x][enemy_y].type = 'E';
}
// placing the awards
void PlaceAward()
{
	award_x = rand() % HEIGHT - 1;
	award_y = rand() % WIDTH - 1;
	board[award_x][award_y].award = '@';
}
// function for moving the enemy
void MoveEnemy()
{
	int direction = rand() % 4;
	board[enemy_x][enemy_y].type = ' ';
	if (
		direction == 0 && enemy_x > 0)
		enemy_x--;
	else if (direction == 1 && enemy_x < HEIGHT - 1)
		enemy_x++;
	else if (direction == 2 && enemy_y > 0)
		enemy_y--;
	else if (direction == 3 && enemy_y < WIDTH - 1)
		enemy_y++;
	board[enemy_x][enemy_y].type = 'E';
}
//function for making the computer to play tha Game.
void MoveComputer(char board[HEIGHT][WIDTH], int *x , int*y){
	int direction= rand()%4;
	board[*y][*x]=' ';
	switch(direction){
		case 0:if(*y>0)(*y)--;
		break;
		case 1: if(*y<HEIGHT-1)(*y)++;
		break;
		case 2:if(*x>0)(*x)--;
		break;
		case 3:if(*x<WIDTH-1)(*x)++;
		break;
	}
	board[*y][*x]='C';
}
// Main Function
int main()
{
	initialize();
	PlaceEnemy();
	char ch;
	food -= 28;
	int totalFood = food;
	int computer_x=WIDTH/2;
	int computer_y=HEIGHT/2;
	char board[HEIGHT][WIDTH];
	// Instructions to Play
	printf(" Use buttons for w(up), a(left) , d(right) and "
		   "s(down)\nAlso, Press q for quit and press 'k' to watch the computer playing the Game.\n");
	printf("Enter Y to continue: \n");
	ch = getch();
	if (ch !='Y' && ch != 'y' && ch!='K' && ch!='k')
	{
		printf("Exit Game!.\n");
		return 1;
	}
	while (1)
	{
		draw();
		printf("Total Food count: %d\n", totalFood);
		printf("Total Food eaten: %d\n", curr);
		printf("your total award is: %d\n", award);
		if (res == 1)
		{
			// Clear screen
			system("cls");
			printf("Game Over! Dead by Demon or ENEMY.\n Your Score: "
				   "%d\n",
				   score);
			return 1;
		}
		if (res == 2)
		{
			// Clear screen
			system("cls");
			printf("You Win! \n Your Score: %d\n", score);
			return 1;
		}
		// Taking the Input from the user
		ch = getch();
		// Moving According to the
		// input character
		switch (ch)
		{
		case 'w':
			move(0, -1);
			break;
		case 's':
			move(0, 1);
			break;
		case 'a':
			move(-1, 0);
			break;
		case 'd':
			move(1, 0);
			break;
		case 'q':
			printf("Game Over! Your Score: %d\n", score);
            printf("your total award is: %d\n", award);
			case 'k':
			MoveComputer(board, &computer_x, &computer_y);
			sleep(2);
			break;
			return 0;
		}
		MoveEnemy();
	}
	return 0;
}
