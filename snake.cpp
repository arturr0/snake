#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <conio.h>
#include <windows.h>
#include <algorithm>

using namespace std;

const int WIDTH = 12;
const int HEIGHT = 12;
int pion = 1, poz = 1, punkty = 0, longer = 2, czas = 500;
bool kolizja = false;
int x, y, los;

vector<vector<int>> pozycja = {{0, 0}, {0, 0}, {0, 0}, {0, 0}};
vector<vector<int>> pozycjac = {{0, 0}, {0, 0}, {0, 0}, {0, 0}};
vector<vector<int>> v1(100, vector<int>(2, 0));
vector<vector<int>> v(WIDTH, vector<int>(HEIGHT, 0));
char plansza[WIDTH][HEIGHT];

void ClearScreen()
{
    COORD cursorPosition = {0, 0};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursorPosition);
}

vector<vector<int>> generuj()
{
    int idx = 0;
    for (int i = 0; i < 10; ++i)
        for (int j = 0; j < 10; ++j, ++idx)
        {
            v1[idx][0] = i + 1;
            v1[idx][1] = j + 1;
        }
    return v1;
}

vector<vector<int>> wolne(const vector<vector<int>> &snake, vector<vector<int>> all)
{
    for (const auto &segment : snake)
    {
        all.erase(remove(all.begin(), all.end(), segment), all.end());
    }
    return all;
}

void draw()
{
    v[x][y] = 2;
    v[pozycja[longer][0]][pozycja[longer][1]] = 0;
    v[pion][poz] = 1;

    for (int i = 0; i < HEIGHT; ++i)
    {
        for (int j = 0; j < WIDTH; ++j)
        {
            if (v[i][j] == 1)
                plansza[i][j] = ' ';
            else if (v[i][j] == 0)
                plansza[i][j] = (char)219; // Block character
            else if (v[i][j] == 2)
                plansza[i][j] = '$'; // Food character

            HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
            if (plansza[i][j] == '$')
                SetConsoleTextAttribute(h, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
            else if (plansza[i][j] == (char)219)
                SetConsoleTextAttribute(h, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
            else
                SetConsoleTextAttribute(h, 7);

            // Print two characters horizontally for each tile to make it appear square
            cout << plansza[i][j] << plansza[i][j];
        }
        cout << endl;
    }
}

bool urobos()
{
    for (int i = 2; i < longer; i++)
    {
        if (pion == pozycja[i][0] && poz == pozycja[i][1])
            return true;
    }
    return false;
}

void bonus(vector<vector<int>> &freeTiles)
{
    if (v[x][y] == 1)
    {
        punkty++;
        v1 = generuj();
        freeTiles = wolne(pozycjac, v1);
        los = rand() % freeTiles.size();
        x = freeTiles[los][0];
        y = freeTiles[los][1];
        longer++;
    }
}

enum Direction
{
    UP,
    DOWN,
    LEFT,
    RIGHT
};

void moveSnake(Direction dir)
{
    switch (dir)
    {
    case UP:
        pion--;
        break;
    case DOWN:
        pion++;
        break;
    case LEFT:
        poz--;
        break;
    case RIGHT:
        poz++;
        break;
    }

    pozycjac.insert(pozycjac.begin(), {pion, poz});
    pozycjac.resize(longer + 2);

    draw();
    Sleep(czas);
    ClearScreen();

    kolizja = urobos();
    auto freeTiles = wolne(pozycjac, v1);
    bonus(freeTiles);

    pozycja.insert(pozycja.begin(), {pion, poz});
    pozycja.resize(longer + 1);
}

int main()
{
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = false;
    SetConsoleCursorInfo(out, &cursorInfo);

    // system("mode con: cols=24 lines=12"); // Set console window size to match the game board, adjust cols for 2x tiles
    cout << "\x1b[?25l";

    for (int i = 3; i >= 0; --i)
    {
        cout << i;
        Sleep(1000);
        system("cls");
    }

    srand(time(NULL));
    v1 = generuj();
    auto freeTiles = wolne(pozycjac, v1);
    los = rand() % freeTiles.size();
    x = freeTiles[los][0];
    y = freeTiles[los][1];
    v[1][1] = 2;

    Direction currentDirection = RIGHT;
    while (!kolizja && poz > 0 && poz < WIDTH - 1 && pion > 0 && pion < HEIGHT - 1)
    {
        if (_kbhit())
        {
            char c = _getch();
            if (c == 'w' && currentDirection != DOWN)
                currentDirection = UP;
            else if (c == 's' && currentDirection != UP)
                currentDirection = DOWN;
            else if (c == 'a' && currentDirection != RIGHT)
                currentDirection = LEFT;
            else if (c == 'd' && currentDirection != LEFT)
                currentDirection = RIGHT;
        }
        moveSnake(currentDirection);
    }

    cout << "Game Over. Score: " << punkty << endl;
    return 0;
}
