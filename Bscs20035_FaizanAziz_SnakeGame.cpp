#include<iostream>
#include<windows.h>
using namespace std;
#include<conio.h>
#include<math.h>

#define capacity 50
#define Rows 30
#define Cols 100
#define Up_Arrow 72
#define Down_Arrow 80
#define Left_Arrow 75
#define Right_Arrow 77
#define MAX_NOP 4

enum Direction { UP, DOWN, LEFT, RIGHT };

struct position
{
	int ri = 0;
	int ci = 0;
};

struct Snake
{
	position Ps[capacity];
	int size, score = 0;
	char SS = -37;
	Direction Dir = UP;
};

void gotoRowCol(int rpos, int cpos)
{
	COORD scrn;
	HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
	scrn.X = cpos;
	scrn.Y = rpos;
	SetConsoleCursorPosition(hOuput, scrn);
}

bool IsValid(Snake S, position& FPos)
{
	if (FPos.ri > Rows && FPos.ci > Cols)
		return false;

	for (int i = 0; i < S.size; i++)
	{
		if (S.Ps[i].ri == FPos.ri && S.Ps[i].ci == FPos.ci)
			return false;
	}
	return true;
}

void food_symbols(Snake S[], char FoodSym[], int NOP)
{
	for (int i = 0; i < NOP; i++)
	{
		cout << "Enter food symbol for " << i + 1 << " snake: ";
		cin >> FoodSym[i];


	}
}

void Generate_Food(position& FPos, Snake S, char Sym)
{
	do
	{
		FPos.ri = rand() % Rows;
		FPos.ci = rand() % Cols;
	} while (!IsValid(S, FPos));


}

void Update_food(position& FPos, Snake S, char Sym)
{
	Generate_Food(FPos, S, Sym);
}

void init(Snake& S, position& FPos, char Sym)
{
	S.size = 1;
	Generate_Food(FPos, S, Sym);
}

void init__allsnakes(Snake S[], position FPos[], char FoodSym[], int NOP)
{
	int count = 0;
	for (int i = 0; i < NOP; i++)
	{
		S[i].Ps[0].ci = count;
		S[i].Ps[0].ri = count;
		count += 10;

	}

	for (int i = 0; i < NOP; i++)
	{
		init(S[i], FPos[i], FoodSym[i]);
	}
}

void Change_direction(Snake S[])
{
	char ch;
	ch = _getch();
	int key = int(ch);
	if (key == -32)
	{
		key = _getch();

		if (key == Up_Arrow && S[0].Dir != DOWN)
			S[0].Dir = UP;
		else if (key == Down_Arrow && S[0].Dir != UP)
			S[0].Dir = DOWN;
		else if (key == Left_Arrow && S[0].Dir != RIGHT)
			S[0].Dir = LEFT;
		else if (key == Right_Arrow && S[0].Dir != LEFT)
			S[0].Dir = RIGHT;

	}
	else if (key == 119 && S[1].Dir != DOWN)
		S[1].Dir = UP;
	else if (key == 115 && S[1].Dir != UP)
		S[1].Dir = DOWN;
	else if (key == 97 && S[1].Dir != RIGHT)
		S[1].Dir = LEFT;
	else if (key == 100 && S[1].Dir != LEFT)
		S[1].Dir = RIGHT;
	else if (key == 105 && S[2].Dir != DOWN)
		S[2].Dir = UP;
	else if (key == 107 && S[2].Dir != UP)
		S[2].Dir = DOWN;
	else if (key == 106 && S[2].Dir != LEFT)
		S[2].Dir = LEFT;
	else if (key == 108 && S[2].Dir != RIGHT)
		S[2].Dir = RIGHT;
	else if (key == 116 && S[3].Dir != DOWN)
		S[3].Dir = UP;
	else if (key == 103 && S[3].Dir != UP)
		S[3].Dir = DOWN;
	else if (key == 102 && S[3].Dir != LEFT)
		S[3].Dir = LEFT;
	else if (key == 104 && S[3].Dir != RIGHT)
		S[3].Dir = RIGHT;
}

void Change_SnakeDirection(Snake& S)
{
	switch (S.Dir)
	{
	case UP:
		S.Ps[0].ri--;
		if (S.Ps[0].ri == -1)
			S.Ps[0].ri = Rows - 1;
		break;
	case DOWN:
		S.Ps[0].ri++;
		if (S.Ps[0].ri == Rows)
			S.Ps[0].ri = 0;
		break;
	case LEFT:
		S.Ps[0].ci--;
		if (S.Ps[0].ci == -1)
			S.Ps[0].ci = Cols - 1;
		break;
	case RIGHT:
		S.Ps[0].ci++;
		if (S.Ps[0].ci == Cols)
			S.Ps[0].ci = 0;
		break;

	}

}

void Snake_Extend(Snake& S, position Snake_tail, int& speed, int& counter)
{
	S.size += 2;
	S.score++;

	S.Ps[S.size - 1] = Snake_tail;

	if (S.score == counter)
	{
		speed = 80;
		speed = speed - (S.score + 15);
		counter += 5;
	}
}

void Snake_erase(Snake& S)
{
	for (int i = 0; i < S.size; i++)
	{
		gotoRowCol(S.Ps[i].ri, S.Ps[i].ci);
		cout << " ";

	}
}

void move_snake(Snake& S)
{
	for (int i = S.size; i >= 1; i--)
	{
		S.Ps[i] = S.Ps[i - 1];
	}
	Change_SnakeDirection(S);
}

void Snake_display(Snake& S)
{

	for (int i = 0; i < S.size; i++)
	{
		gotoRowCol(S.Ps[i].ri, S.Ps[i].ci);
		cout << S.SS;
	}
}

void move_multiplesnakes(Snake S[], int NOP)
{
	for (int i = 0; i < NOP; i++)
	{
		move_snake(S[i]);
	}
}

void display_multiplesnakes(Snake S[], int NOP)
{
	for (int i = 0; i < NOP; i++)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), i + 10);
		Snake_display(S[i]);

	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
}

void display_food(position FPos, char Sym)
{
	gotoRowCol(FPos.ri, FPos.ci);
	cout << Sym;
}

void display_foods(position FPos[], char Sym[], int NOP)
{
	for (int i = 0; i < NOP; i++)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), i + 10);
		display_food(FPos[i], Sym[i]);

	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
}

void display_scores(Snake S[], int NOP)
{
	int counter = 0;
	for (int i = 0; i < NOP; i++)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), i + 10);
		gotoRowCol(Rows, counter);
		cout << "Snake " << i + 1 << " Score:" << S[i].score << endl;
		counter += 20;
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
}

void Leaderboard(Snake S[], int NOP)
{
	for (int i = 0; i < NOP; i++)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), i + 10);
		cout << "Total Score of Snake " << i + 1 << ": " << S[i].score << endl;;
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
}

void erase_multiplesnakes(Snake S[], int NOP)
{
	for (int i = 0; i < NOP; i++)
	{
		Snake_erase(S[i]);
	}
}

bool Eat_food(Snake S, position FPos)
{

	if (S.Ps[0].ri == FPos.ri && S.Ps[0].ci == FPos.ci)
		return true;
	return false;
}

void Eat_foods(Snake S[], position FPos[], position Snake_tail[], int& speed, int& counter, char FoodSym[], int NOP)
{
	for (int i = 0; i < NOP; i++)
	{
		if (Eat_food(S[i], FPos[i]))
		{
			Snake_Extend(S[i], Snake_tail[i], speed, counter);
			Update_food(FPos[i], S[i], FoodSym[i]);
		}
	}
}

bool game_over(Snake S)
{
	for (int i = S.size; i >= 1; i--)
	{
		if (S.Ps[0].ri == S.Ps[i].ri && S.Ps[0].ci == S.Ps[i].ci)
			return true;
	}
	return false;
}

bool check_gameovers(Snake S[], int NOP, char FoodSymbol[])
{
	for (int i = 0; i < NOP; i++)
	{
		if (game_over(S[i]))
		{
			S[i].size = 0;
			FoodSymbol[i] = ' ';
			return true;
		}
	}
	return false;
}

bool check_collision(Snake S[], int NOP, char FoodSymbol[])
{

	for (int x = 0; x < NOP; x++)
	{
		for (int j = 0; j < NOP; j++)
		{
			if (x != j)
			{
				for (int i = 0; i < S[j].size; i++)
				{

					if (S[x].Ps[0].ri == S[j].Ps[i].ri && S[x].Ps[0].ci == S[j].Ps[i].ci)
					{
						S[x].size = 0;
						S[x].Ps[i].ci = 0;
						S[x].Ps[i].ri = 0;
						FoodSymbol[x] = ' ';
						return true;
					}
				}
			}
		}
	}
	return false;
}

void Snake_Tails(Snake S[], int NOP, position Snake_tail[])
{
	for (int i = 0; i < NOP; i++)
	{
		Snake_tail[i] = S[i].Ps[S[i].size - 1];
	}
}

void menu()
{
	system("cls");
	cout << "\t\t Controls:" << endl << endl
		<< "\t\t Up \t Down \t Left \t Right" << endl << endl
		<< "Player 1: \tArrowUP ArrowDown ArrowLeft ArrowRight" << endl << endl
		<< "Player 2: \tW S A D" << endl << endl
		<< "Player 3: \tI K J L" << endl << endl
		<< "Player 4: \tT G F H" << endl << endl;
	system("pause");
	system("cls");
}

int main()
{
	int NOP, snake_killed = 0;
	cout << "Enter number of players: ";
	cin >> NOP;
	system("cls");
	char FoodSym[MAX_NOP];
	position FPos[MAX_NOP], Snake_tail[MAX_NOP];
	Snake S[MAX_NOP];
	int speed = 80, counter = 5;

	food_symbols(S, FoodSym, NOP);
	init__allsnakes(S, FPos, FoodSym, NOP);

	menu();
	system("cls");
	do
	{
		Snake_Tails(S, NOP, Snake_tail);
		if (_kbhit())
		{
			Change_direction(S);
		}
		else
		{
			move_multiplesnakes(S, NOP);
			display_multiplesnakes(S, NOP);
			Sleep(speed);
			erase_multiplesnakes(S, NOP);

			Eat_foods(S, FPos, Snake_tail, speed, counter, FoodSym, NOP);
			display_foods(FPos, FoodSym, NOP);
		}

		if (check_gameovers(S, NOP, FoodSym))
		{
			snake_killed++;
		}
		if (check_collision(S, NOP, FoodSym))
		{
			snake_killed++;
		}

		if (snake_killed == NOP)
		{
			system("cls");
			cout << "\t \tGame over!" << endl;
			Leaderboard(S, NOP);
			return 0;
		}

		display_scores(S, NOP);
	} while (true);
}

