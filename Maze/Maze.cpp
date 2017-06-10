// Maze.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>
#include <fstream>
#include <conio.h>
#include "obrazovka.h"

using namespace std;
COORD Cur = { 0,0 };
COORD Ciel = { 0,0 };
const char CURSOR = 'O';
const char CIEL = 'C';
const char STENA = '#';
const char VOLNA = ' ';

COORD Najdi(char ** pIn, int iX, int iY, char znak)
{
	int i, j;
	COORD lokal = { 1,1 };
	for (j = 0; j < iY; j++)
		for (i = 0; i < iX; i++)
			if (pIn[j][i] == znak)
			{
				lokal.X = i;
				lokal.Y = j;
				return lokal;
			}
	return lokal;
}

void VypisPole(char ** pIn, int iY)
{
	int i;
	for (i = 0; i < iY; i++)
		cout << pIn[i] << endl;
}

char ** NahrajPole(char * Subor, int * pX, int * pY)
{
	int i = 0, iRozX = 0, iRozY = 0;
	char ** pIn;
	ifstream pFin(Subor);

	if (!pFin)
	{
		cout << "Chyba pri otvarani suboru: " << Subor << endl;
		exit(EXIT_FAILURE);
	}
	pFin >> iRozX >> iRozY;
	while (pFin.get() != '\n')
		continue;
	*pX = iRozX;
	*pY = iRozY;
	pIn = new char*[iRozY * sizeof(char*)];
	if (pIn == NULL)
	{
		cout << "Maticu sa nepodarilo alokovat" << endl;
		pFin.close();
		return NULL;
	}
	for (i = 0; i < iRozY; i++)
	{
		pIn[i] = new char[(iRozX + 2) * sizeof(char)]; // '\n'+ '\0'
		if (pIn[i] == NULL)
		{
			cout << "Maticu sa nepodarilo alokovat" << endl;
			pFin.close();
			return NULL;
		}
		pFin.getline(pIn[i], iRozX + 2); // '\n'+ '\0'
		pIn[i][iRozX] = '\0';
	}
	pFin.close();
	return pIn;
}

void UvolniPole(char ** pIn, int iRozY)
{
	int i;
	for (i = 0; i < iRozY; i++)
		delete pIn[i];
	delete pIn;
}

int main(int argc, char ** argv)
{
	Obrazovka obr;
	int iX, iY;
	char znak;

	if (argc != 2)
	{
		cout << "chyba: subor s levelom sa nenasiel.";
		exit(EXIT_FAILURE);
	}
	char ** Pole = NahrajPole(argv[1], &iX, &iY);

	Cur = Najdi(Pole, iX, iY, CURSOR);
	Ciel = Najdi(Pole, iX, iY, CIEL);
	obr.Cls();
	VypisPole(Pole, iY);
	do
	{
		znak = getch();
		if (znak == '6')
			if (Pole[Cur.Y][Cur.X + 1] != STENA)
			{
				Pole[Cur.Y][Cur.X] = VOLNA;
				obr.SetCurXY(Cur.X, Cur.Y, BACKGROUND_GREEN); cout << VOLNA;
				Pole[Cur.Y][++Cur.X] = CURSOR;
				obr.SetCurXY(Cur.X, Cur.Y, FOREGROUND_RED | BACKGROUND_GREEN); cout << CURSOR;
				obr.SetColor(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
			}
		if (znak == '4')
			if (Pole[Cur.Y][Cur.X - 1] != STENA)
			{
				Pole[Cur.Y][Cur.X] = VOLNA;
				obr.SetCurXY(Cur.X, Cur.Y, BACKGROUND_GREEN); cout << VOLNA;
				Pole[Cur.Y][--Cur.X] = CURSOR;
				obr.SetCurXY(Cur.X, Cur.Y, FOREGROUND_RED | BACKGROUND_GREEN); cout << CURSOR;
				obr.SetColor(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
			}
		if (znak == '8')
			if (Pole[Cur.Y - 1][Cur.X] != STENA)
			{
				Pole[Cur.Y][Cur.X] = VOLNA;
				obr.SetCurXY(Cur.X, Cur.Y, BACKGROUND_GREEN); cout << VOLNA;
				Pole[--Cur.Y][Cur.X] = CURSOR;
				obr.SetCurXY(Cur.X, Cur.Y, FOREGROUND_RED | BACKGROUND_GREEN); cout << CURSOR;
				obr.SetColor(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
			}
		if (znak == '2')
			if (Pole[Cur.Y + 1][Cur.X] != STENA)
			{
				Pole[Cur.Y][Cur.X] = VOLNA;
				obr.SetCurXY(Cur.X, Cur.Y, BACKGROUND_GREEN); cout << VOLNA;
				Pole[++Cur.Y][Cur.X] = CURSOR;
				obr.SetCurXY(Cur.X, Cur.Y, FOREGROUND_RED | BACKGROUND_GREEN); cout << CURSOR;
				obr.SetColor(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
			}
		if (Cur.Y == Ciel.Y && Cur.X == Ciel.X)
		{
			break;
		}
		//obr.SetCurXY(0,iY+2); cout << Cur.X <<" "<<Cur.Y;
	} while (znak != 'q');
	UvolniPole(Pole, iY);
	return 0;
}
