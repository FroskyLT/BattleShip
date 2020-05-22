#pragma once

bool ShotCheck(int x, int y, int sh[][10], int sh1[][10] = 0)
{
	bool left = 0, right = 0, top = 0, bottom = 0;

	int xs, xf;
	int ys, yf;
	if (x == 0) { xs = 0; left = 1; }
	if (x == 9) { xf = 9; right = 1; }
	if (y == 0) { ys = 0; top = 1; }
	if (y == 9) { yf = 9; bottom = 1; }

	bool Lcheck = 1, Rcheck = 1, Tcheck = 1, Bcheck = 1;
	int xtemp = x;

	while (!left) { xtemp--;
		if (sh[y][xtemp] == 0 || sh[y][xtemp] == 2) { left = true; xs = xtemp; }
		else if (sh[y][xtemp] == 1) Lcheck = 0;
	}
	xtemp = x;
	while (!right) { xtemp++;
		if (sh[y][xtemp] == 0 || sh[y][xtemp] == 2) { right = true; xf = xtemp; }
		else if (sh[y][xtemp] == 1) Rcheck = 0;
	}
	int ytemp = y;

	while (!top) { ytemp--;
		if (sh[ytemp][x] == 0 || sh[ytemp][x] == 2) { top = true; ys = ytemp; }
		else if (sh[ytemp][x] == 1) Tcheck = 0;
	}
	ytemp = y;
	while (!bottom) { ytemp++;
		if (sh[ytemp][x] == 0 || sh[ytemp][x] == 2) { bottom = true; yf = ytemp; }
		else if (sh[ytemp][x] == 1) Bcheck = 0;
	}

	if (Lcheck && Rcheck && Tcheck && Bcheck) //paskendus laiveli is visu pusiu pazymes kaip saudyta
	{
		for (int i = ys; i <= yf; i++)
			for (int j = xs; j <= xf; j++)
			{
				if (sh[i][j] == 0) { sh[i][j] = 2; sh1[i][j] = 2; }
			}
		return true;
	}
	return false;
}
// | 0 = . |   1 = D |   -1 = X |   2 = * |

int EnemyShotCheck(int x, int y, int sh[][10])
{
	if (sh[y][x] == 1 || sh[y][x] == -1) return true;
	else return false;
}