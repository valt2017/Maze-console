#include "stdafx.h"
#include "Obrazovka.h"

Obrazovka::Obrazovka(bool Erase)
{
  if(Erase)
    Cls();
  SetColor(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
}

Obrazovka::~Obrazovka()
{
  SetColor(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
}

void Obrazovka::SetCurXY(unsigned int valX, unsigned int valY, unsigned int Clr)
{
  COORD coord = {0,0};
  if(valX < MAX_X)
    coord.X = valX;
  if(valY < MAX_Y)
    coord.Y = valY;
  if(Clr != 0)
    SetColor(Clr);
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void Obrazovka::SetColor(unsigned int Clr)
{
  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Clr);
}

unsigned int Obrazovka::GetCurX()
{
  CONSOLE_SCREEN_BUFFER_INFO SBInfo;
  GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &SBInfo);
  return SBInfo.dwCursorPosition.X;
}

unsigned int Obrazovka::GetCurY()
{
  CONSOLE_SCREEN_BUFFER_INFO SBInfo;
  GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &SBInfo);
  return SBInfo.dwCursorPosition.Y;
}

void Obrazovka::Cls()
{
  system("cls");
}

