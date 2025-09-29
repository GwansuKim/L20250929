#include <iostream>
#include <conio.h>
#include <Windows.h>

using namespace std;

// C++ -> class
// UE
struct FCharacter
{
	int X;
	int Y;
	string Shape;
};

//typedef :: struct _COORD�� COORD�� ȣ���Ѵ�(C��� ����)
//typedef struct _COORD {
//	SHORT X;
//	SHORT Y;
//} COORD;

FCharacter Characters[3];

char KeyCode;
bool bIsContinue = true;

int MapSize = 0;

HANDLE ScreenBuffers[2];

int CurrentBufferIndex = 0;

void Init()
{
	srand((unsigned int)time(nullptr));

	//0, nullptr, NULL �� ���� �ǹ�
	ScreenBuffers[0] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, nullptr, CONSOLE_TEXTMODE_BUFFER, NULL);
	ScreenBuffers[1] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, nullptr, CONSOLE_TEXTMODE_BUFFER, NULL);

	cout << "���� ũ�⸦ �Է��� �ּ���(NxN) : ";
	cin >> MapSize;
	system("cls");

	/*FCharacter* Data = new FCharacter;

	delete Data;*/

	Characters[0].X = 0;
	Characters[0].Y = 0;
	Characters[0].Shape = "P";

	Characters[1].X = rand() % MapSize;
	Characters[1].Y = rand() % MapSize;
	Characters[1].Shape = "M";

	Characters[2].X = rand() % MapSize;
	Characters[2].Y = rand() % MapSize;
	Characters[2].Shape = "B";
}

void Input()
{
	KeyCode = _getch();
}


bool Predict(int Coordinate)
{
	if (Coordinate < 0)
	{
		return false;
	}
	else if (Coordinate >= MapSize)
	{
		return false;
	}
	else
	{
		return true;
	}
}

void MovePlayer()
{
	if (KeyCode == 'w')
	{
		if (Predict(Characters[0].Y - 1))
		{
			Characters[0].Y--;
		}
	}
	else if (KeyCode == 's')
	{
		if (Predict(Characters[0].Y + 1))
		{
			Characters[0].Y++;
		}
	}
	else if (KeyCode == 'a')
	{
		if (Predict(Characters[0].X - 1))
		{
			Characters[0].X--;
		}
	}
	else if (KeyCode == 'd')
	{
		if (Predict(Characters[0].X + 1))
		{
			Characters[0].X++;
		}
	}
	else if (KeyCode == 'q')
	{
		bIsContinue = false;
	}
}

void MoveMonster(int Index)
{
	int Direction = rand() % 4;
	switch (Direction)
	{
	case 0: //Up
		if (Predict(Characters[Index].Y - 1))
		{
			Characters[Index].Y--;
		}
		break;
	case 1://Down
		if (Predict(Characters[Index].Y + 1))
		{
			Characters[Index].Y++;
		}
		break;
	case 2://Left
		if (Predict(Characters[Index].X - 1))
		{
			Characters[Index].X--;
		}
		break;
	case 3://Right
		if (Predict(Characters[Index].X + 1))
		{
			Characters[Index].X++;
		}
		break;
	default:
		//Error
		break;
	}
}

void Tick()
{
	MovePlayer();
	for (int i = 1; i < 3; i++)
	{
		MoveMonster(i);
	}
}

void Clear()
{
	COORD coordScreen = { 0, 0 };
	DWORD cCharsWritten;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	DWORD dwConSize;

	//��ũ�� ���� ���� ��������
	GetConsoleScreenBufferInfo(ScreenBuffers[CurrentBufferIndex], &csbi);
	dwConSize = csbi.dwSize.X * csbi.dwSize.Y;
	FillConsoleOutputCharacter(ScreenBuffers[CurrentBufferIndex],
		(TCHAR)' ',
		dwConSize,
		coordScreen,
		&cCharsWritten);
}

//call by reference
void RenderCharacter(const FCharacter* Character)
{
	COORD Position;
	Position.X = (SHORT)Character->X;
	Position.Y = (SHORT)Character->Y;

	//Character->Y++; //const ������ �����ʹ� ������ ��� ������

	SetConsoleCursorPosition(ScreenBuffers[CurrentBufferIndex], Position);
	WriteConsole(ScreenBuffers[CurrentBufferIndex], Character->Shape.c_str(), 1, NULL, NULL);
}

void Present()
{
	SetConsoleActiveScreenBuffer(ScreenBuffers[CurrentBufferIndex]);

	CurrentBufferIndex++;
	CurrentBufferIndex %= 2;
}

void Render()
{
	//�׷��� ī�� �׸��� ���
	Clear();

	//RenderAll
	for (int i = 2; i >= 0; i--)
	{
		RenderCharacter(&Characters[i]);
	}

	Present();
}	

int main(int argc, char* argv[])
{
	Init();

	while (bIsContinue)
	{
		Render();
		Input();
		Tick();
	}

	return 0;
}