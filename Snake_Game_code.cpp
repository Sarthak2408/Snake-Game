#include <iostream>
#include <conio.h>
#include <windows.h>
using namespace std;
bool gameOver;
const int widthofwall = 80;
const int heightofwall = 20;
int snakeX, snakeY, fruitX, fruitY, points;
int tailX[100], tailY[100];
int nTail;
enum eDirecton { STOP = 0, LEFT, RIGHT, UP, DOWN}; 
eDirecton dir;
void Settings()
{
    gameOver = false;
    dir = STOP;
    snakeX = widthofwall / 2;
    snakeY = heightofwall / 2;
    fruitX = rand() % widthofwall;
    fruitY = rand() % heightofwall;
    points = 0;
}
void arena()
{
    system("cls");
    for (int i = 0; i < widthofwall+2; i++)
        cout << "-";
    cout << endl;
 
    for (int i = 0; i < heightofwall; i++)
    {
        for (int j = 0; j < widthofwall; j++)
        {
            if (j == 0)
                cout << "|";
            if (i == snakeY && j == snakeX)
                cout << "O";
            else if (i == fruitY && j == fruitX)
                cout << "@";
            else
            {
                bool print = false;
                for (int k = 0; k < nTail; k++)
                {
                    if (tailX[k] == j && tailY[k] == i)
                    {
                        cout << "o";
                        print = true;
                    }
                }
                if (!print)
                    cout << " ";
            }
                 
 
            if (j == widthofwall - 1)
                cout << "|";
        }
        cout << endl;
    }
 
    for (int i = 0; i < widthofwall+2; i++)
        cout << "-";
    cout << endl;
    cout << "points:" << points << endl;
}
void keys()
{
    if (_kbhit())
    {
        switch (_getch())
        {
        case 'a':
            dir = LEFT;
            break;
        case 'd':
            dir = RIGHT;
            break;
        case 'w':
            dir = UP;
            break;
        case 's':
            dir = DOWN;
            break;
        case 'x':
            gameOver = true;
            break;
        }
    }
}
void movement()
{
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = snakeX;
    tailY[0] = snakeY;
    for (int i = 1; i < nTail; i++)
    {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }
    switch (dir)
    {
    case LEFT:
        snakeX--;
        break;
    case RIGHT:
        snakeX++;
        break;
    case UP:
        snakeY--;
        break;
    case DOWN:
        snakeY++;
        break;
    default:
        break;
    }
    
    if (snakeX >= widthofwall) snakeX = 0; else if (snakeX < 0) snakeX = widthofwall - 1;
    if (snakeY >= heightofwall) snakeY = 0; else if (snakeY < 0) snakeY = heightofwall - 1;
 
    for (int i = 0; i < nTail; i++)
        if (tailX[i] == snakeX && tailY[i] == snakeY)
            gameOver = true;
 
    if (snakeX == fruitX && snakeY == fruitY)
    {
        points += 10;
        fruitX = rand() % widthofwall;
        fruitY = rand() % heightofwall;
        nTail++;
    }
}
int main()
{
    Settings();
    while (!gameOver)
    {
        arena();
        keys();
        movement();
        Sleep(10); 
    }
    return 0;
}
