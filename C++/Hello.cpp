#include <iostream>
#include <conio.h>
using namespace std;

bool gameover;
const int width = 20;
const int height = 20;
int tailX[100], tailY[100];
int Ntail;
int x, y, fruitX, fruitY, score;
enum Edirect { STOP = 0, LEFT, RIGHT, UP, DOWN };
Edirect dir;

void Setup() 
{
    gameover = false;
    dir = STOP;
    x = width / 2 - 1;
    y = height / 2 - 1;
    fruitX = rand() % width;
    fruitY = rand() % height;
    score = 0;
}
void Draw()
{
    system("cls"); 
    for (int i = 0; i < width + 1; i++) {
        cout << "#";
    }
    

    cout << endl;

    for (int i = 0; i < height; i++) {
         for (int j = 0; j < width; j++) {
             if (j == 0 || j == width - 1 ){
                cout << "#";
             }
                cout << " ";
                if (i == y && j == x) {
                    cout << "0";
                }
                else if (i == fruitY && j == fruitX) {
                    cout << "F";
                }
                else {
                    bool print = false;
                    for (int k = 0; k < Ntail; k++) {
                        if (tailX[k] == j && tailY[k] == i) {
                            print = true;
                            cout << "o";
                        }
                    }
                    if (!print)
                    cout << " ";
                }
         }
            cout << endl;
    }

    for (int i = 0; i < width + 1; i++) {
         cout << "#";
    }
    cout << endl;
    cout << "Score: "<< score << endl;
}

void Input()
{
    if (_kbhit()) {
        switch (_getch()) {
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
            gameover = true;
            break;
        }
    }

}

void Logic()
{
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2x, prev2y;
    tailX[0] = x;
    tailY[0] = y;

    for (int i = 1; i < Ntail; i++)
    {
        prev2x = tailX[i];
        prev2y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2x;
        prevY = prev2y;
    }

    switch (dir) {
    case LEFT:
        x--;
        break;
    case RIGHT:
        x++;
        break;
    case UP:
        y--;
        break;
    case DOWN:
        y++;
        break;
    }

    if (x > width || x < 0 || y > height || y < 0) {
        gameover = true;
        for (int i = 0; i < Ntail; i++) {
            if (tailX[i] == x && tailY[i] == y) {
                gameover = true;
            }
        }       
    }
    if (x == fruitX && y == fruitY) {
        score = score + 10;
        fruitX = rand() % width;
        fruitY = rand() % height;
        Ntail++;
    }
}

int main()
{
    Setup();
    while (!gameover) {
        Draw();
        Input();
        Logic();
        
    }

   
    return 0;
}
