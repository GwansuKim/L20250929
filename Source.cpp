#include <iostream>
#include <conio.h>
#include <stdlib.h>
#include <time.h>

using namespace std;

int Player[2] = { 0, 0 };
char PlayerShape = 'P';

int Monster[2] = { 0, 0 };
char MonsterShape = 'M';

char KeyCode;
bool bIsContinue = true;

int MapSize = 0;


bool Predict(int Coord)
{
	if (Coord < 0)
	{
		return false;
	}
	else if (Coord > MapSize)
	{
		return false;
	}
	else
	{
		return true;
	}
}

void Process()
{
	if (KeyCode == 'w')
	{
		if (Predict(Player[1] - 1))
		{
			Player[1]--;
		}
	}
	else if (KeyCode == 's')
	{
		if (Predict(Player[1] + 1))
		{
			Player[1]++;
		}
	}
	else if (KeyCode == 'a')
	{
		if (Predict(Player[0] - 1))
		{
			Player[0]--;
		}
	}
	else if (KeyCode == 'd')
	{
		if (Predict(Player[0] + 1))
		{
			Player[0]++;
		}
	}
	else if (KeyCode == 'q')
	{
		bIsContinue = false;
	}
}

void Render()
{
	for (int Y = 0; Y <= MapSize; Y++)
	{
		for (int X = 0; X <= MapSize; X++)
		{
			if (Y == Player[1] && X == Player[0])
			{
				cout << PlayerShape;
			}
			else if (Y == Monster[1] && X == Monster[0])
			{
				cout << MonsterShape;
			}
			else
			{
				cout << " ";
			}
		}
		cout << "\n";
	}
}

int main()
{
	srand((unsigned int)time(nullptr));

	cout << "맵의 크기를 입력해 주세요(NxN) : ";
	cin >> MapSize;
	system("cls");

	//최초 렌딩 1회
	cout << PlayerShape;

	Monster[0] = rand() % MapSize;
	Monster[1] = rand() % MapSize;

	while (bIsContinue)
	{
		KeyCode = _getch();

		system("cls");

		Process();
		Render();
	}

	return 0;
}