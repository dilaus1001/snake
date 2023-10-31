#include <iostream>
#include <math.h>
#include <ncurses.h>

using namespace std;

bool gameOver;
const int width = 20;
const int height = 20;
int x, y, fruitX, fruitY, score;
int tailX[100], tailY[100];
int nTail;
enum eDirection{STOP = 0, LEFT, RIGHT, UP, DOWN};
eDirection dir;
int ch = ERR;

void Setup() 
{
    gameOver = false;
    dir = STOP;
    x = width / 2;
    y = height / 2;
    fruitX = rand() % width;
    fruitY = rand() % height;
    score = 0;


}

void Draw() 
{
    system("clear"); //we are going to use the system screen so this would clear the terminal, on linux it will be system("clear");
    for (int i = 0; i < width+1; i++)
        cout << "#";
    cout << endl;

      for (int i = 0; i < height; i++)
      {
            for (int j = 0; j < width; j++)
                {
                    if (j == 0)
                        cout << "#";
                    if(i == y && j == x)
                        cout << "0";
                    else if(i == fruitY && j == fruitX)
                        cout << "F";
                    else    
                        {
                            bool print = false;
                            for(int k = 0; k < nTail; k++)
                            {
                                if(tailX[k] == j && tailY[k] == i)
                                {
                                    cout << "o";
                                    print = true;
                                }
                            }
                             if(!print)
                                cout << " ";  
                        }
                      
                         //cout << " ";
                    if (j == width-1)
                        cout << "#";
                }
                cout << endl;
      }
        

      for (int i = 0; i < width+1; i++)
        cout << "#";
    cout << endl;
    cout << "Score: " << score << endl;
}

void Input()
{
    initscr();  // Initialize ncurses
    nodelay(stdscr, FALSE);  // Set the window to non-blocking mode
    noecho();  // Disable automatic echoing of typed characters
    cbreak();  // Disable line buffering

    ch = wgetch(stdscr);  // Get a character from the user
    if (ch != ERR)  // If a character was pressed
    {
        switch(ch)
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
        ch = ERR;
    }
    endwin();  // Restore the terminal to its original state
}

void Logic()
{
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;
    for(int i = 1; i < nTail; i++)
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
    default:
        break;
    }
    

    if(x > width || x < 0 || y > height || y < 0)
        gameOver = true;
    if(x == fruitX && y == fruitY)
    {
        score +=10;
        fruitX = rand() % width;
        fruitY = rand() % height;
        nTail++;
    }
}
    int main() 
    {
        Setup();
        while (!gameOver)
        {
            Input();
            while(ch == ERR)
                Draw();
                Logic();
            //Sleep(10); sleep(10);
        }

        
        return 0;
    } 