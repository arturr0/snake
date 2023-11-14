#include <iostream>
#include <cstdlib>
#include <time.h>
#include <stdio.h>
#include <windows.h>
#include <vector>
#include <algorithm>
#include <ctime>
#include <stdlib.h>
#include <random>
#include <conio.h>

using namespace std;
int i = 0, j = 0, b = 0, poz = 0, poz1 = 1, pion = 1, punkty = 0, x, y, buforx, bufory, los;
bool kolizja = false;

vector <int> lastx(3, 0);
vector <int> lasty(3, 0);


vector<vector <int>> pozycja{ {0,0},
{0,0} ,
{0,0} ,
{0,0}, };
int longer = 2;
int czas = 500;

std::vector < std::vector < int >> v1(100, std::vector < int >(2, 0));

vector <vector <int>> generuj()


{
    int l = 0, m = 10, n, o = 0, p = 0, g = 0, h = 10, t, u;

    for (size_t k = 0; k < 10; ++k)
    {
        if (k > 0)
        {
            l = l + 10;
            m = m + 10;
            o++;
        }
        for (n = l; n < m; ++n)
        {


            for (size_t j = 0; j < 2; j++)
            {

                v1[n][0] = o + 1;


            }

        }

    }

    for (size_t k = 0; k < 10; ++k)
    {

        if (k > 0)
        {
            g = g + 10;
            h = h + 10;

        }

        for (t = g; t < h; ++t)
        {
            if (t % 10 == 0) u = 0;
            u++;
            for (size_t j = 0; j < 2; j++)
            {

                v1[t][1] = u;


            }

        }

    }

    return v1;


}
int v3[2];
vector <vector<int>> wolne(vector <vector<int>>pozycja, vector <vector<int>>v4)

{


    for (int k = 0; k < pozycja.size(); ++k)
    {
        for (size_t i = 0; i < v4.size(); ++i)
        {
            for (size_t j = 0; j < v1[i].size(); )
            {
                if (v4[i] == pozycja[k])
                {
                    v4.erase(v4.begin() + i);
                    --i;
                    break;
                }
                else {
                    ++j;
                }
            }
        }
    }
    return v4;
}
std::vector < std::vector < int >> v(12, std::vector < int >(12));
std::vector < std::vector < int >> v2(12, std::vector < int >(12));
char plansza[12][12];

void ClearScreen()
{
    COORD cursorPosition;	cursorPosition.X = 0;	cursorPosition.Y = 0;	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursorPosition);
}
void draw(int switcher)
{

    for (int i = 0; i < 12; i++)
    {


        if (switcher == 1)
        {
            v[x][y] = 2;


            v[pozycja[longer][0]][pozycja[longer][1]] = 0;
            v[pion][poz] = 1;

        }

        for (int j = 0; j < 12; j++)
        {

            if (v[i][j] == 1) plansza[i][j] = ' ';
            else if (v[i][j] == 0) plansza[i][j] = (char)219;
            else if (v[i][j] == 2) {
                plansza[i][j] = '$';
            }

            plansza[0][0] = (char)201;
            plansza[0][11] = (char)187;
            plansza[11][0] = (char)200;
            plansza[11][11] = (char)188;
            for (int i = 1; i < 11; i++) { plansza[i][0] = (char)186; plansza[i][11] = (char)186; }
            for (int i = 1; i < 11; i++) { plansza[0][i] = (char)205; plansza[11][i] = (char)205; }
            if (plansza[i][j] == '$') {

                HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
                SetConsoleTextAttribute(h, FOREGROUND_GREEN | FOREGROUND_INTENSITY);

            }
            else if (plansza[i][j] == (char)219) {

                HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
                SetConsoleTextAttribute(h, FOREGROUND_BLUE | FOREGROUND_INTENSITY);

            }
            else if (plansza[i][j] == (char)201
                || plansza[i][j] == (char)200
                || plansza[i][j] == (char)187
                || plansza[i][j] == (char)188
                || plansza[i][j] == (char)186
                || plansza[i][j] == (char)205) {

                HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
                SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY);

            }

            else {
                HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
            }
            cout << plansza[i][j];
        }
        std::cout << endl;

    }
}

bool urobos()
{
    for (int i = 2; i < longer; i++)

    {
        if (pion == pozycja[i][0] && poz == pozycja[i][1]) kolizja = true;

    }
    return kolizja;
}

void bonus(vector < vector < int >> pozycjac, vector < vector < int >> v2, int size)
{
    srand(time(NULL));
    if (v[x][y] == 1)
    {


        punkty++;

        v1 = generuj();

        los = rand() % size;

        x = v2[los][0];
        y = v2[los][1];

        longer++;
    }

}
vector<vector <int>> pozycjac{ {0,0},
{0,0} ,
{0,0} ,
{0,0}, };

int main()
{
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_CURSOR_INFO     cursorInfo;

    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = 0; // set the cursor visibility
    SetConsoleCursorInfo(out, &cursorInfo);
    for (int i = 3; i >= 0; i--)
    {
        cout << i;
        Sleep(1000);
        system("cls");
    }

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);

    srand(time(NULL));
    v1 = generuj();
    v2 = wolne(pozycjac, v1);
    int los = rand() % v2.size();
    x = v2[los][0];
    y = v2[los][1];
    v[1][1] = 2;



    while (true)
    {


    prawo:
        for (poz = poz + 1; poz < 11; poz++)
        {

            pozycjac.insert(pozycjac.begin(), { pion,poz });




            draw(1);

            pozycjac.erase(pozycjac.begin() + (longer + 2), pozycjac.end());
            Sleep(czas);

            ClearScreen();

            urobos();
            v2 = wolne(pozycjac, v1);
            bonus(pozycjac, v2, v2.size());

            if (_kbhit()) {
                char c = _getch();
                if (c == 's')
                {
                    pozycja.insert(pozycja.begin(), { pion,poz });
                    v[pion][poz] = 1;

                    goto dol;
                }
                if (c == 'w')
                {
                    pozycja.insert(pozycja.begin(), { pion,poz });
                    v[pion][poz] = 1;


                    goto gora;
                }
            }
            pozycja.insert(pozycja.begin(), { pion,poz });
            pozycja.erase(pozycja.begin() + (longer + 1), pozycja.end());

            // Inserting the vector = {1, 2, 3} as the second vector

            if (kolizja == true) break;
        }
        std::system("cls");
        break;

    lewo:
        for (poz = poz - 1; poz >= 1; poz--)
        {
            pozycjac.insert(pozycjac.begin(), { pion,poz });




            draw(1);
            pozycjac.erase(pozycjac.begin() + (longer + 2), pozycjac.end());
            Sleep(czas);

            ClearScreen();

            urobos();

            pozycja.erase(pozycja.begin() + (longer + 1), pozycja.end());
            v2 = wolne(pozycjac, v1);
            bonus(pozycjac, v2, v2.size());

            if (_kbhit()) {
                char c = _getch();
                if (c == 's')
                {
                    pozycja.insert(pozycja.begin(), { pion,poz });
                    v[pion][poz] = 1;

                    goto dol;
                }
                if (c == 'w')
                {
                    pozycja.insert(pozycja.begin(), { pion,poz });
                    v[pion][poz] = 1;

                    goto gora;
                }
            }
            pozycja.insert(pozycja.begin(), { pion,poz });
            pozycja.erase(pozycja.begin() + (longer + 1), pozycja.end());



            // Inserting the vector = {1, 2, 3} as the second vector

            if (kolizja == true) break;
        }
        std::system("cls");
        break;

    dol:
        for (pion = pion + 1; pion < 11; pion++)
        {
            pozycjac.insert(pozycjac.begin(), { pion,poz });



            v[x][y] = 2;
            v[pozycja[longer][0]][pozycja[longer][1]] = 0;
            v[pion][poz] = 1;

            draw(0);

            pozycjac.erase(pozycjac.begin() + (longer + 2), pozycjac.end());
            Sleep(czas);

            ClearScreen();

            urobos();
            v2 = wolne(pozycjac, v1);
            bonus(pozycjac, v2, v2.size());

            if (_kbhit()) {
                char c = _getch();
                if (c == 'd')
                {
                    pozycja.insert(pozycja.begin(), { pion,poz });
                    v[pion][poz] = 1;

                    goto prawo;
                }
                else if (c == 'a')
                {
                    pozycja.insert(pozycja.begin(), { pion,poz });
                    v[pion][poz] = 1;

                    goto lewo;
                }
            }
            pozycja.insert(pozycja.begin(), { pion,poz });
            pozycja.erase(pozycja.begin() + (longer + 1), pozycja.end());



            if (kolizja == true) break;
        }
        std::system("cls");
        break;
    gora:
        for (pion = pion - 1; pion >= 1; pion--)
        {
            pozycjac.insert(pozycjac.begin(), { pion,poz });


            v[x][y] = 2;
            v[pozycja[longer][0]][pozycja[longer][1]] = 0;
            v[pion][poz] = 1;

            draw(0);

            pozycjac.erase(pozycjac.begin() + (longer + 2), pozycjac.end());
            Sleep(czas);

            ClearScreen();

            urobos();

            pozycja.erase(pozycja.begin() + (longer + 1), pozycja.end());
            v2 = wolne(pozycjac, v1);
            bonus(pozycjac, v2, v2.size());

            if (_kbhit()) {
                char c = _getch();
                if (c == 'd')
                {
                    pozycja.insert(pozycja.begin(), { pion,poz });
                    v[pion][poz] = 1;

                    goto prawo;
                }
                else if (c == 'a')
                {
                    pozycja.insert(pozycja.begin(), { pion,poz });
                    v[pion][poz] = 1;

                    goto lewo;
                }
            }
            pozycja.insert(pozycja.begin(), { pion,poz });
            pozycja.erase(pozycja.begin() + (longer + 1), pozycja.end());


            if (kolizja == true) break;
        }

        break;
    }
    cout << los;
}






