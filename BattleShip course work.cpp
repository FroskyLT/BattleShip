#include <iomanip>
#include <iostream>
#include <map>
#include <cstdlib>
#include <ctime>
#include "coordinates.h"
#include "shooting.h"
using namespace std;

const int il = 10;
class Ships {
public:
	static int MyShips[il][il];
	static int EShips[il][il];
	static int ShotsMap[il][il];
	Ships() = default;
	~Ships() {}
	void ShowMap(int sh[][il]) {  //a1 a4 f3 h3 c9 e9 j2 j3 c5 d5 e7 f7 h8 j10 i5 a10
		cout << setw(3) << " ";
		for (char i = 'A'; i < 'K'; i++) cout << setw(2) << i;
		cout << endl;
		for (int i = 0; i < 10; i++)
		{
			cout << setw(2) << i + 1 << "|";
			for (int j = 0; j < 10; j++)
			{
				if (sh[i][j] == 0) cout << setw(2) << '.';
				else if (sh[i][j] == 1) cout << setw(2) << 'D';
				else if (sh[i][j] == -1) cout << setw(2) << 'X';
				else  cout << setw(2) << '*';
				if (j == 9) cout << setw(2) << "|";
			}
			cout << endl;
		}
	}
	void GameMap() {
		cout << setw(3) << " ";
		for (char i = 'A'; i < 'K'; i++) cout << setw(2) << i;
		cout << setw(20) << " ";
		for (char i = 'A'; i < 'K'; i++) cout << setw(2) << i;
		cout << endl;

		for (int i = 0; i < 10; i++)
		{
			cout << setw(2) << i + 1 << "|";
			for (int j = 0; j < 10; j++)
			{
				if (MyShips[i][j] == 0) cout << setw(2) << '.'; // the field of our ship
				else if (MyShips[i][j] == 1) cout << setw(2) << 'D';
				else if (MyShips[i][j] == -1) cout << setw(2) << 'X';
				else  cout << setw(2) << '*';
				if (j == 9)
				{
					cout << setw(2) << "|";
					cout << setw(15) << " ";
					cout << setw(2) << i + 1 << "|";
					for (int k = 0; k < 10; k++)
					{
						if (ShotsMap[i][k] == 0) cout << setw(2) << '.'; // battlefield
						else if (ShotsMap[i][k] == -1) cout << setw(2) << 'X';
						else if (ShotsMap[i][k] == 2) cout << setw(2) << '*';
						if (k == 9) cout << setw(2) << "|";
					}
				}
			}
			cout << endl;
		}
		cout << setw(8) << " " << "Your Field" << setw(41) << "BattleField" << endl;
		cout << endl;
	}
};
int Ships::MyShips[il][il] = { 0 };
int Ships::EShips[il][il] = { 0 };
int Ships::ShotsMap[il][il] = { 0 };

class AbstractPosition {
protected:
	map<int, int> a;
public:
	AbstractPosition() {
		int j = 4;
		for (int i = 0; i < 4; i++) {
			a.insert(pair<int, int>(j, i + 1));
			j--;
		}
	}
	~AbstractPosition() {
	}
};

class SetPosition : public Ships, public AbstractPosition {
public:
	void ManualSet(int sh[][il]);
	void RandomSet(int sh[][il]);
};

void SetPosition::ManualSet(int sh[][il]) {
	int count = 4;
	while (!a.empty()) {
		ShowMap(sh);
		cout << "Number of unused vessels: " << endl;
		for (int i = 0; i < count; i++) cout << "X";
		cout << " " << a[count] << " vnt.\n";
		if (count > 1) cout << "enter the coordinates e.g. (a1 a" << count << ")" << endl;
		else cout << "enter the coordinates e.g. (a" << count << ")" << endl;

		bool poscheck = 1;
		while (poscheck) {
			int x1, y1; //pradzios koordinates
			int x2, y2; //pabaigos koordinates 
			if (count > 1) { CoordInput(x1, y1); CoordInput(x2, y2); }
			else
			{
				CoordInput(x1, y1);
				x2 = x1;
				y2 = y1;
			}
			if (CoordCheck(x1, y1, x2, y2, count))
			{
				int xs = x1 - 1, xf = x2 + 1; // xs-start xf-finish
				int ys = y1 - 1, yf = y2 + 1;
				if (x1 == 0) xs = 0;
				if (x2 == 9) xf = 9;
				if (y1 == 0) ys = 0;
				if (y2 == 9) yf = 9;

				// laisvo lauko tikrinimas
				int s = 0;
				for (int i = ys; i <= yf; i++)
					for (int j = xs; j <= xf; j++)
					{
						if (sh[i][j] == 0)
							s++;
					}
				if (s == (xf - xs + 1) * (yf - ys + 1))
				{
					if (x1 == x2) for (int i = y1; i <= y2; i++) { sh[i][x1] = 1; }
					if (y1 == y2) for (int i = x1; i <= x2; i++) { sh[y1][i] = 1; }
					poscheck = 0;
					system("CLS");
				}
				else { cout << "a ship cannot be placed here\n"; }
			}
		}
		if (a[count] > 1) a[count]--;
		else {
			a.erase(count);
			count--;
		}
	}
}
void SetPosition::RandomSet(int sh[][il]) {
	int count = 4;
	while (!a.empty()) {
		//ShowMap(sh);
		bool poscheck = 1;
		while (poscheck)
		{
			int x2 = 0, y2 = 0;
			int x1 = rand() % 10;
			int y1 = rand() % 10;
			if (x1 + count <= 10 || y1 + count <= 10)
			{
				if (x1 + count > 10) // jei prireiks vertikaliai
				{
					x2 = x1;
					y2 = y1 + count - 1;
				}
				else if (y1 + count > 10) // jei prireiks horizontaliai
				{
					x2 = x1 + count - 1;
					y2 = y1;
				}
				else // atsitiktinai
				{
					int direction = rand() % 2;
					if (direction == 0) {
						x2 = x1 + count - 1;
						y2 = y1;
					}
					else if (direction == 1)
					{
						x2 = x1;
						y2 = y1 + count - 1;
					}
				}
				int xs = x1 - 1, xf = x2 + 1;
				int ys = y1 - 1, yf = y2 + 1;
				if (x1 == 0) xs = 0;
				if (x2 == 9) xf = 9;
				if (y1 == 0) ys = 0;
				if (y2 == 9) yf = 9;
				// laisvo lauko tikrinimas
				int s = 0;
				for (int i = ys; i <= yf; i++)
					for (int j = xs; j <= xf; j++)
					{
						if (sh[i][j] == 0)
							s++;
					}
				if (s == (xf - xs + 1) * (yf - ys + 1))
				{
					if (x1 == x2) for (int i = y1; i <= y2; i++) { sh[i][x1] = 1; }
					if (y1 == y2) for (int i = x1; i <= x2; i++) { sh[y1][i] = 1; }
					poscheck = 0;
				}
			}
		}
		if (a[count] > 1) a[count]--;
		else {
			a.erase(count);
			count--;
		}
	}
	system("CLS");
}

class Shots : public Ships {
private:
	int MShotted, EShotted; // kai yra pataikyta i laiveli
	bool turn;
	bool remember, left, right, top, bottom;
	int Rx, Ry;
public:
	Shots() :Rx(0), Ry(0), turn(1), MShotted(0), EShotted(0), remember(0), left(0), right(0), top(0), bottom(0) {}
	~Shots(){}
	void operator++();
	void operator--();
	bool EnemyShot() { return MShotted; }
	bool MyShot() { return EShotted; }
	bool Turn() { return turn; }
};

void Shots::operator++() {
	int x, y;
	bool checkpos = 1;
	while (checkpos)
	{
		EShotted = 0;
		CoordInput(x, y);
		if (ShotCheck(x, y))
		{
			if (EShips[y][x] == 1)
			{
				ShotsMap[y][x] = -1; EShips[y][x] = -1;
				checkpos = 0; EShotted = 1;
				turn = true;
				ShotCheck(x, y, EShips, ShotsMap);
			}
			else if (EShips[y][x] == 0)
			{
				ShotsMap[y][x] = 2; EShips[y][x] = 2;
				checkpos = 0;
				turn = false;
			}
			else if (EShips[y][x] == -1) { cout << "a boat already sinked here\n"; }
			else { cout << "you have already shot here\n"; }
		}
	}
}
void Shots::operator--()
{
	bool checkpos = 1;
	while (checkpos)
	{
		MShotted = 0;
		int x = rand() % 10;
		int y = rand() % 10;
		if (ShotCheck(x, y))
		{
			if (!remember) {
				if (MyShips[y][x] == 1) {
					MyShips[y][x] = -1;
					checkpos = 0;
					MShotted++;
					turn = false;
					if (!ShotCheck(x, y, MyShips, MyShips))
					{
						Rx = x;
						Ry = y;
						remember = 1;
					}
				}
				else if (MyShips[y][x] == 0) {
					MyShips[y][x] = 2;
					checkpos = 0;
					turn = true;
				}
			}
			else {
				int xs = 0, xf = 0;
				int ys = 0, yf = 0;

				if (Rx == 0) { xs = 0; left = 1; }
				if (Rx == 9) { xf = 9; right = 1; }
				if (Ry == 0) { ys = 0; top = 1; }
				if (Ry == 9) { yf = 9; bottom = 1; }
				
				int xtemp = Rx;
				while (!left) 
				{
					xtemp--;
					if (EnemyShotCheck(xtemp, Ry, MyShips))
					{
						MyShips[Ry][xtemp] = -1; top = true, bottom = true; MShotted++;
						if (ShotCheck(xtemp, Ry, MyShips, MyShips))
						{
							left = true; right = true; top = true; bottom = true;
						}
					}
					else { left = true; turn = 1; checkpos = 0; MyShips[Ry][xtemp] = 2; }
				}
				xtemp = Rx;
				while (!right && turn == 0)
				{
					xtemp++;
					if (EnemyShotCheck(xtemp, Ry, MyShips))
					{
						MyShips[Ry][xtemp] = -1; top = true, bottom = true; MShotted++;
						if (ShotCheck(xtemp, Ry, MyShips, MyShips))
						{
							left = true; right = true; top = true; bottom = true;
						}
					}
					else { right = true; turn = 1; checkpos = 0; MyShips[Ry][xtemp] = 2; }
				}
				int ytemp = Ry;
				while (!top && turn == 0)
				{
					ytemp--;
					if (EnemyShotCheck(Rx, ytemp, MyShips)) {
						MyShips[ytemp][Rx] = -1; MShotted++;
						if (ShotCheck(Rx, ytemp, MyShips, MyShips))
						{
							left = true; right = true; top = true; bottom = true;
						}
					}
					else { top = true; turn = 1; checkpos = 0; MyShips[ytemp][Rx] = 2; }
				}
				ytemp = Ry;
				while (!bottom && turn == 0)
				{
					ytemp++;
					if (EnemyShotCheck(Rx, ytemp, MyShips)) { 
						MyShips[ytemp][Rx] = -1; MShotted++;
						if (ShotCheck(Rx, ytemp, MyShips, MyShips))
						{
							left = true; right = true; top = true; bottom = true;
						}
					}
					else { bottom = true; turn = 1; checkpos = 0; MyShips[ytemp][Rx] = 2; }
				}

				if (left && right && top && bottom) {
					left = false; right = false; top = false; bottom = false;
					checkpos = 0;
					remember = 0;
				}
			}
		}
	}
}

int main() {
	srand(time(NULL));
	SetPosition Mpos, Epos;
	cout << "Random layout - 0\nSelf-layout - 1\n";
	int temp; cin >> temp;
	if (temp) Mpos.ManualSet(Ships::MyShips);
	else Mpos.RandomSet(Ships::MyShips);
	Epos.RandomSet(Ships::EShips);

	Ships show;
	show.GameMap();

	// show.ShowMap(Ships::EShips);

	Shots shots;
	int MySum = 20, EnemySum = 20;

	while (MySum > 0 && EnemySum > 0)
	{
		if (shots.Turn()) {
			cout << "enter the shooting coordinates: ";
			++shots;
			system("CLS");
			show.GameMap();
			/*show.ShowMap(Ships::EShips);*/
			if (shots.Turn()) { cout << "You hit the boat! Shoot again: \n"; }
		}
		else {
			--shots;
			system("CLS");
			show.GameMap();
			/*show.ShowMap(Ships::EShips);*/
			}
		MySum = MySum - shots.EnemyShot();
		EnemySum = EnemySum - shots.MyShot();
	}
	system("CLS");
	if (MySum == 0) cout << "You lost." << endl;
	else cout << "Congratulations, Victory!" << endl;

	return 0;
}