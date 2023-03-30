#include <iostream>
#include <windows.h>
using namespace std;

void printMaze();
void gotoxy(int x, int y);
void erase(int x, int y);
void printPacman(int x, int y);
void printGhost(int x, int y);
void printChar(int x, int y, char character);
void printScore(int score);
void updateScore(int &score);
char getCharAtxy(short int x, short int y);

void handleGhost1(int &x, int &y, bool &direction, char &previousChar);
void handleGhost2(int &x, int &y, bool &direction, char &previousChar);

void handlePacman(int &x, int &y, int &score);
bool pacmanUp(int &x, int &y);
bool pacmanDown(int &x, int &y);
bool pacmanLeft(int &x, int &y);
bool pacmanRight(int &x, int &y);

void consoleCursor(bool visibility);

int main()
{
    consoleCursor(false);
    int score = 0;
    int gx1 = 5;
    int gy1 = 15;
    int gx2 = 28;
    int gy2 = 10;
    int pacmanX = 30, pacmanY = 16;
    bool direction1 = true;
    char previousChar1 = ' ';
    bool direction2 = true;
    char previousChar2 = ' ';
    system("cls");
    printMaze();
    printGhost(gx1, gy1);
    printGhost(gx2, gy2);
    printScore(score);
    while (true)
    {
        Sleep(100);
        handlePacman(pacmanX, pacmanY, score);
        handleGhost1(gx1, gy1, direction1, previousChar1);
        handleGhost2(gx2, gy2, direction2, previousChar2);
    }
}
bool isPill(char character)
{
    if (character == '.')
    {
        return true;
    }
    else
    {
        return false;
    }
}
void handleGhost1(int &x, int &y, bool &direction, char &previousChar)
{
    if (direction)
    {
        char nextLocation = getCharAtxy(x + 1, y);
        if (nextLocation != '.' && nextLocation != ' ')
        {
            direction = false;
        }
        else if (nextLocation == ' ' || nextLocation == '.')
        {
            erase(x, y);
            printChar(x, y, previousChar);
            previousChar = nextLocation;
            x = x + 1;
            printGhost(x, y);
        }
    }
    if (!direction)
    {
        char nextLocation = getCharAtxy(x - 1, y);
        if (nextLocation != '.' & nextLocation != ' ')
        {
            direction = true;
        }
        else if (nextLocation == ' ' || nextLocation == '.')
        {
            erase(x, y);
            printChar(x, y, previousChar);
            previousChar = nextLocation;
            x = x - 1;
            printGhost(x, y);
        }
    }
}
void handleGhost2(int &x, int &y, bool &direction, char &previousChar)
{
    if (direction)
    {
        char nextLocation = getCharAtxy(x, y + 1);
        if (nextLocation != '.' && nextLocation != ' ')
        {
            direction = false;
        }
        else if (nextLocation == ' ' || nextLocation == '.')
        {
            erase(x, y);
            printChar(x, y, previousChar);
            previousChar = nextLocation;
            y = y + 1;
            printGhost(x, y);
        }
    }
    if (!direction)
    {
        char nextLocation = getCharAtxy(x, y - 1);
        if (nextLocation != '.' & nextLocation != ' ')
        {
            direction = true;
        }
        else if (nextLocation == ' ' || nextLocation == '.')
        {
            erase(x, y);
            printChar(x, y, previousChar);
            previousChar = nextLocation;
            y = y - 1;
            printGhost(x, y);
        }
    }
}
void handlePacman(int &x, int &y, int &score)
{
    if (GetAsyncKeyState(VK_LEFT))
    {
        if (pacmanLeft(x, y))
        {
            updateScore(score);
        }
    }
    if (GetAsyncKeyState(VK_RIGHT))
    {
        if (pacmanRight(x, y))
        {
            updateScore(score);
        }
    }
    if (GetAsyncKeyState(VK_UP))
    {
        if (pacmanUp(x, y))
        {
            updateScore(score);
        }
    }
    if (GetAsyncKeyState(VK_DOWN))
    {
        if (pacmanDown(x, y))
        {
            updateScore(score);
        }
    }
}
bool pacmanUp(int &x, int &y)
{
    char nextPosition = getCharAtxy(x, y - 1);
    if (nextPosition == ' ' || nextPosition == '.')
    {
        erase(x, y);
        y--;
        printPacman(x, y);
    }
    return isPill(nextPosition);
}
bool pacmanDown(int &x, int &y)
{
    char nextPosition = getCharAtxy(x, y + 1);
    if (nextPosition == ' ' || nextPosition == '.')
    {
        erase(x, y);
        y++;
        printPacman(x, y);
    }
    return isPill(nextPosition);
}
bool pacmanLeft(int &x, int &y)
{
    char nextPosition = getCharAtxy(x - 1, y);
    if (nextPosition == ' ' || nextPosition == '.')
    {
        erase(x, y);
        x--;
        printPacman(x, y);
    }
    return isPill(nextPosition);
}
bool pacmanRight(int &x, int &y)
{
    char nextPosition = getCharAtxy(x + 1, y);
    if (nextPosition == ' ' || nextPosition == '.')
    {
        erase(x, y);
        x++;
        printPacman(x, y);
    }
    return isPill(nextPosition);
}
void gotoxy(int x, int y)
{
    COORD coordinates;
    coordinates.X = x;
    coordinates.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordinates);
}
char getCharAtxy(short int x, short int y)
{
    CHAR_INFO ci;
    COORD xy = {0, 0};
    SMALL_RECT rect = {x, y, x, y};
    COORD coordBufSize;
    coordBufSize.X = 1;
    coordBufSize.Y = 1;
    return ReadConsoleOutput(GetStdHandle(STD_OUTPUT_HANDLE), &ci, coordBufSize, xy, &rect) ? ci.Char.AsciiChar : ' ';
}
void erase(int x, int y)
{
    gotoxy(x, y);
    cout << " ";
}
void printPacman(int x, int y)
{
    gotoxy(x, y);
    cout << "P";
}
void printGhost(int x, int y)
{
    gotoxy(x, y);
    cout << "G";
}
void printChar(int x, int y, char character)
{
    gotoxy(x, y);
    cout << character;
}
void printMaze()
{
    cout << "#####################################################################" << endl;
    cout << "||........................................................  .......||" << endl;
    cout << "||.. %%%%%%%%%%%%%%%%       ...     %%%%%%%%%%%%%%%  |%|..   %%%%  ||" << endl;
    cout << "||..       |%|    |%|    |%|...     |%|         |%|  |%|..    |%|  ||" << endl;
    cout << "||..       |%|    |%|    |%|...     |%|         |%|  |%|..    |%|  ||" << endl;
    cout << "||..       %%%%%%%%  . . |%|...     %%%%%%%%%%%%%%%          %%%%. ||" << endl;
    cout << "||..       |%|       . . |%|...    ...............  |%| ..       . ||" << endl;
    cout << "||..       %%%%%%%%%%. . |%|...    %%%%%%%%%%%%     |%| ..   %%%%. ||" << endl;
    cout << "||..              |%|.             |%|......        |%| ..    |%|. ||" << endl;
    cout << "||..     ........ |%|.             |%|......|%|         ..    |%|. ||" << endl;
    cout << "||..|%|  |%|%%|%|.|%|. |%|            ......|%|         ..|%| |%|. ||" << endl;
    cout << "||..|%|  |%|  |%|..    %%%%%%%%%%%%   ......|%|          .|%|.     ||" << endl;
    cout << "||..|%|  |%|  |%|..          ...|%|      %%%%%%         . |%|.     ||" << endl;
    cout << "||..|%|           .          ...|%|                 |%| ..|%|.     ||" << endl;
    cout << "||..|%|  %%%%%%%%%%%%        ...|%|%%%%%%%%%%%      |%| ..|%|%%%%  ||" << endl;
    cout << "||..............................................    |%| .........  ||" << endl;
    cout << "||   ...........................................          .......  ||" << endl;
    cout << "||..|%|  |%|  |%|..   %%%%%%%%%%%%%  ......|%|      |%| ..|%|.     ||" << endl;
    cout << "||..|%|  |%|  |%|..          ...|%|    %%%%%%%      |%| ..|%|.     ||" << endl;
    cout << "||..|%|           .          ...|%|                 |%| ..|%|.     ||" << endl;
    cout << "||..|%|  %%%%%%%%%%%%        ...|%|%%%%%%%%%        |%| ..|%|%%%%  ||" << endl;
    cout << "||............................................      |%| .........  ||" << endl;
    cout << "||  ..........................................            .......  ||" << endl;
    cout << "#####################################################################" << endl;
}
void updateScore(int &score)
{
    score += 10;
    printScore(score);
}
void printScore(int score)
{
    gotoxy(80, 15);
    cout <<"Score:"<< score;
}
void consoleCursor(bool visibility)
{
    CONSOLE_CURSOR_INFO ci;
    HANDLE stdHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleCursorInfo(stdHandle, &ci);
    ci.bVisible = visibility;
    SetConsoleCursorInfo(stdHandle, &ci);
}