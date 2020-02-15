#include <iostream>
#include <windows.h>
#include <thread>
#include <chrono>
#include <string>
#include <conio.h>
#include "render.hpp"

using namespace std;

void Cmd(World* pWorld)
{
	short row = 0;
	double mult = 1;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	double* arr[] = { &pWorld->gravity, &pWorld->mWind.viscosity, &pWorld->mWind.density, &pWorld->mWind.Vel.x,
		&pWorld->mWind.Vel.y, &pWorld->mRailgun.angle, &pWorld->mRailgun.force, &pWorld->mRailgun.length, &pWorld->bMass, &pWorld->bRadius };

	while (true)
	{
		cout << " Gravity:" << "\t\t" << *arr[0] << endl;
		cout << " Medium viscosity:" << "\t" << *arr[1] << endl;
		cout << " Medium density:" << "\t" << *arr[2] << endl;
		cout << " Medium vel x:" << "\t\t" << *arr[3] << endl;
		cout << " Medium vel y:" << "\t\t" << *arr[4] << endl;
		cout << " Railgun angle:" << "\t\t" << *arr[5] << endl;
		cout << " Railgun force:" << "\t\t" << *arr[6] << endl;
		cout << " Railgun length:" << "\t" << *arr[7] << endl;
		cout << " Bullet mass:" << "\t\t" << *arr[8] << endl;
		cout << " Bullet radius:" << "\t\t" << *arr[9] << endl << endl;
		cout << " Parametr mult:" << "\t\t" << mult << endl;

		SetConsoleCursorPosition(hConsole, COORD{ 0, row });
		cout << "*";
		SetConsoleCursorPosition(hConsole, COORD{ 0, 10 });

		int c = int(_getch());
		switch (c)
		{
		case 32:
			pWorld->Fire();
			break;

		case 119:
			row--;
			break;

		case 115:
			row++;
			break;

		case 97:
			*arr[row] -= mult;
			break;

		case 100:
			*arr[row] += mult;
			break;
		
		case 101:
			mult *= 2;
			break;

		case 113:
			mult /= 2;
			break;

		case 102:
			*arr[row] = 0;
			break;
		}

		if (row < 0)
			row = 9;
		if (row > 9)
			row = 0;
		system("cls");
	}
}

int main(int argc, char** argv)
{
	Window* pWindow = new Window(1024, 1024);
	World* pWorld = new World();

	thread t1(Cmd, pWorld);

	chrono::time_point RealTime = chrono::high_resolution_clock::now();
	chrono::time_point VirtualTime = chrono::high_resolution_clock::now();

	const double TickTime = double(1) / double(256);
	unsigned long int TimeDelta = 1000000000 * TickTime;

	while (true)
	{
		RealTime = chrono::high_resolution_clock::now();
		if (chrono::duration_cast<std::chrono::nanoseconds>(VirtualTime - RealTime).count() < 0)
		{
			VirtualTime += chrono::nanoseconds(TimeDelta);
			pWorld->Tick(TickTime);
			pWindow->Update(*pWorld);
			pWindow->Events();
		}
	}

	return 0;
}