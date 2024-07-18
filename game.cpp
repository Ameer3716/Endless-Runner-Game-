#include <iostream>
#include <thread>       
#include <chrono>
#include <fstream>
#include<stdlib.h>
#include<time.h>
#include <conio.h>
#include <windows.h>

using namespace std;
// Function declarations
void function();
void instruction();
void Menu();
void printBoard(int row, int col, int obs_row, int obs_col, int coin_row, int coin_col, int comp_row, int comp_col);
void movePlayer(char move, int& row, int& col, int& jump_height, int& slide_distance, int& live);
void handleJumping(int& row, int& jump_height);
void handleSliding(int& col, int& slide_distance);
void moveObstacle(int& obs_row, int& row, int& obs_col, int& col, int& live, int& comp_row, int& comp_col, int& distance,int&total_distance);
void moveCoin(int& coin_row, int& row, int& coin_col, int& col, int& score);
void speed(int& distance);
void saveHighScore(int score, string name);

int main()
{
    system("Color C");
    Menu();
    return 0;
}
void Menu()
{

    do {
        system("cls");
        cout << "\n\n\n\n\n\n\n\n\n\n";
        cout << "\t\t\t\t\t " << " =============================== " << endl;
        cout << "\t\t\t\t\t " << " |     Endless Runner Game     | " << endl;
        cout << "\t\t\t\t\t " << " =============================== " << endl;
        cout << "\t\t\t\t\t " << " 1. Start Game " << endl;
        cout << "\t\t\t\t\t " << " 2. Instructions " << endl;
        cout << "\t\t\t\t\t " << " 3. Quit " << endl;
        cout << "\t\t\t\t\t " << " \nSelect Options: " << endl;
        char op = _getch();
        if (op == '1') function();
        else if (op == '2') instruction();
        else if (op == '3') exit(0);
    } while (1);
}
void instruction()
{
    system("cls");
    char option1;
    cout << "\n\n\n\n\n\n\n";
    cout << "\t\t" << "Instructions : " << endl;
    cout << "\t\t" << " (1) : If you use enter ( w ) the runner will move Up. " << endl;
    cout << "\t\t" << " (2) : If you use enter ( s ) the runner will move Down. " << endl;
    cout << "\t\t" << " (3) : If you use enter ( a ) the runner will move Left. " << endl;
    cout << "\t\t" << " (4) : If you use enter ( d ) the runner will move Right. " << endl;
    cout << "\t\t" << " (5) : If you use enter ( space or z ) the runner will jump and slide in upward direction. " << endl;
    cout << "\t\t" << " (6) : The score will be counted continuously as long as the game is not over. " << endl;
    cout << "\t\t" << " (7) : If you use collide with ( @@ ) the coins will be count. " << endl;
    cout << "\t\t" << " (8) : If you use collide with ( ## ) the lives will be reduce. " << endl;
    cout << "\n\t\t" << " (9) : Once the lives reduce to zero (0) the game will be over. \n\t\t Your name, score and coin you collected will be shown. " << endl;
    cout << "\n Enter q or Q to return to mainMenu : ";
    cin >> option1;
    if (option1 == 'q' || option1 == 'Q') {
        Menu();
    }
    else {
        cout << " Invalid Input !!! " << endl;
        _getch();
        exit(0);
    }
   
}
void function()
{
    srand(time(0));
    int upper = 20, lower = 10;
    int row = 18, clm = 4;
    char move = 'a'; // Initialize move variable

    int jump_height = 0;
    int slide_distance = 0;
    int obs_row = 0;
    int obs_col = rand() % 9 + 1;
    int coin_row = 0;
    int coin_col = rand() % 9 + 1;
    int score = 0;
    int live = 3;
    int distance = 0;
    int total_distance = 0;
    int milestone = 200;
    int comp_row = rand() % 19 + 1;
    int comp_col = rand() % 9 + 1;

    cout << "Enter your name: ";
    string name;
    cin >> name;

    while (move != 'q' && live > 0)
    {
        printBoard(row, clm, obs_row, obs_col, coin_row, coin_col, comp_row, comp_col);
        // Increase game speed at distance milestones
        if (_kbhit())
        {

            movePlayer(move, row, clm, jump_height, slide_distance, live);
        }
        handleJumping(row, jump_height);
        handleSliding(clm, slide_distance);
        moveObstacle(obs_row, row, obs_col, clm, live, comp_row, comp_col, distance,total_distance);
        moveCoin(coin_row, row, coin_col, clm, score);
        speed(distance);
            distance++;
        cout << "Distance=" << distance << endl;
    }
    total_distance = total_distance + distance;
   

    cout << "Final Score: " << score;
    saveHighScore(score, name);
}

void movePlayer(char move, int& row, int& col, int& jump_height, int& slide_distance, int& live)
{

    move = _getch();
    switch (move)
    {
    case 'w':
        if (row > 0)
        {
            row--;
        }
        break;
    case 'a':
        if (col > 0)
        {
            col--;
        }
        break;
    case 's':
        if (row < 19)
        {
            row++;
        }
        break;
    case 'd':
        if (col < 9)
        {
            col++;
        }
        break;
    case ' ':
        jump_height = 3;
        break;
    case 'j':
        slide_distance = 2;
        break;
    default:
        break;
    }

    if (row == 0 || row == 19 || col == 0 || col == 9)
    {
        live--;
        row = 18;
        col = 4;
    }
}

void handleJumping(int& row, int& jump_height)
{
    if (jump_height > 0)
    {
        row -= jump_height;
        jump_height--;
    }
    if (row < 0)
    {
        row = 0;
        jump_height = 0;
    }
}

void handleSliding(int& col, int& slide_distance)
{
    if (slide_distance > 0)
    {
        col += slide_distance;
        slide_distance--;
    }
    if (col > 9)
    {
        col = 9;
        slide_distance = 0;
    }
}

void moveObstacle(int& obs_row, int& row, int& obs_col, int& col, int& live, int& comp_row, int& comp_col, int& distance,int&total_distance)
{
    if (obs_row < 19)
    {
        obs_row++;
    }
    else
    {
        obs_row = 0;
        obs_col = rand() % 9 + 1;
    }
    if (obs_row == row && obs_col == col)
    {
        live--;
    }
    if (distance > 2000)//computer player distance 2000+ hone kay baad chalay ga if you want to run it before distance 2000 se kam kardo
    {
        
        comp_row = rand() % 19 + 1;
        comp_col = rand() % 9 + 1;
        if (comp_row < row)
        {
            comp_row++;
        }
        else if (comp_row > row)
        {
            comp_row--;
        }

        if (comp_col < col)
        {
            comp_col++;
        }
        else if (comp_col > col)
        {
            comp_col--;
        }

        if (row == comp_row && col == comp_col)


        {
            live--;
        }
    }
    cout << "live=" << live << endl;
    if (live == 0)
    {
        system("cls");
        cout << "\n\n\n\n\n\n\n\n\n\n";
        cout << "\t\t\t\t\t\t" << " Game Over !" << endl;
        cout << "\t\t\t\t\t\t" << "Total Distance " << total_distance << endl;

        char option1;
        cout << "Enter Q or q to return to Main Menu : ";
        cin >> option1;
        if (option1 == 'q' || option1 == 'Q')
        {
            Menu();
        }
        else
        {
            cout << " Invalid Input !!! " << endl;
            exit(0);
        }
        system("cls");
    }
}
void moveCoin(int& coin_row, int& row, int& coin_col, int& col, int& score)
{
    if (coin_row < 19)
    {
        coin_row++;
    }
    else
    {
        coin_row = 0;
        coin_col = rand() % 9 + 1;
    }
    if (coin_row == row && coin_col == col)
    {
        score = score + 10;
    }
    cout << "Score=" << score << endl;
}
void speed(int& distance)
{
    if (distance > 2000)
    {
        this_thread::sleep_for(chrono::milliseconds(30));
    }
    else if (distance > 200)
    {
        this_thread::sleep_for(chrono::milliseconds(90));
    }
    else
    {
        this_thread::sleep_for(chrono::milliseconds(150));
    }
}

void printBoard(int row, int col, int obs_row, int obs_col, int coin_row, int coin_col, int comp_row, int comp_col)
{
    system("cls");
    cout << "\t\t\t\t    " << " =============================== " << endl;
    cout << "\t\t\t\t    " << " |     Endless Runner Game     | " << endl;
    cout << "\t\t\t\t    " << " =============================== " << endl;
    cout << "\t\t\t\t\t ";
    cout << "<><><><><><><><><><><><>" << endl;
    for (int i = 0; i < 20; i++)
    {
        cout << "\t\t\t\t\t ";
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, 4);
        cout << "||";
        SetConsoleTextAttribute(hConsole, 4);
        for (int j = 0; j < 10; j++)
        {
            if (i == row && j == col)
            {
                HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                SetConsoleTextAttribute(hConsole, 2);

                cout << "^^";
                SetConsoleTextAttribute(hConsole, 7);
            }
            else if (i == comp_row && j == comp_col)
            {
                HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                SetConsoleTextAttribute(hConsole, 5);
                cout << "&&";
                SetConsoleTextAttribute(hConsole, 5);
            }
            else if (i == obs_row && j == obs_col)
            {
                HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                SetConsoleTextAttribute(hConsole, 9);
                cout << "##";
                SetConsoleTextAttribute(hConsole, 9);
            }
            else if (i == coin_row && j == coin_col)
            {
                HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                SetConsoleTextAttribute(hConsole, 6);
                cout << "$$";
                SetConsoleTextAttribute(hConsole, 6);
            }
            else
            {
                cout << "  ";
            }
        }
        cout << "||";
        cout << endl;
    }
    cout << "\t\t\t\t\t ";
    cout << "<><><><><><><><><><><><>" << endl;
}

void saveHighScore(int score, string name)
{
    ifstream input_file("high_score.txt");
    int highScore;
    input_file >> highScore;
    input_file.close();

    ofstream output_file("high_score.txt", ios::app);
    if (score > highScore)
    {
        output_file << "Player Name" << " " << name << " " << score << endl;
    }
    else
    {
        output_file << highScore << endl;
    }
    output_file.close();
}