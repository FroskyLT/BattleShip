#pragma once
#include <iostream>
#include <string>
using namespace std;

void CoordInput(int& x, int& y)
{
    char x1ch(0);
    string a;
    cin >> a;
    if (isalpha(a[0])) {
        x1ch = a[0];
        a.erase(a.begin());
        y = stoi(a) - 1;
    }
    else if (isdigit(a[0])) {
        y = stoi(a) - 1;
        x1ch = a[a.length() - 1];
    }

    // convert char to int
    int ch = 0;
    x = 10;
    for (char i = 'a'; i < 'k'; i++)
    {
        if (x1ch == i) x = ch;
        ch++;
    }
}

bool CoordCheck(int x1, int y1, int x2, int y2, int c) //setposition
{
    if ((x1 == x2 && y2 - y1 != c - 1) || (y1 == y2 && x2 - x1 != c - 1) ||
        (y1 != y2 && x1 != x2) || x1 > 9 || x2 > 9 || y1 > 9 || y2 > 9)
    {
        cout << "incorrect coordinates entered\n";
        return false;
    }
    else return true;
}

bool ShotCheck(int x, int y) //shots
{
    if (x > 9 || y > 9)
    {
        cout << "incorrect coordinates entered\n";
        return false;
    }
    else return true;
}