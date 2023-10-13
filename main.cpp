#include <iostream>
#include <raylib.h>
#include <cmath>
#include <cstring>
#include <fstream>
#include <iomanip>
using namespace std;

Color Platinum = Color{229, 228, 226, 255};
// Template class---------------------------------------------------------------------------------------
template <class t>
class set
{
public:
    t arr[100];
    int i;
    t highest()
    {
        t high = 0;
        for (int j = 0; j <= i; j++)
        {
            if (arr[j] > high)
            {
                high = arr[j];
            }
        }
        return high;
    }
};
set<int> Myset;
// function for getting highest value----------------------------------------------------------------
void get_file()
{
    ifstream inputFile("Number.txt");
    if (!inputFile)
    {
        cerr << "Failed to open the file for reading!";
    }
    else
    {
        int number;
        while (inputFile >> number)
        {
            Myset.arr[Myset.i] = number;
            //cout << "is : " << Myset.arr[Myset.i] << endl;
            Myset.i++;
        }
        inputFile.close();
    }
}

// abstract class---------------------------------------------------------------------------------
class shape
{
public:
    virtual void give(float, float, float, float, float) = 0; // pure virtual function-------------
    virtual void draw() = 0;                                  // pure virtual function-------------
    virtual void update() = 0;                                // pure virtual function-------------
};
// derived class 1---------------------------------------------------------------------------------
class Triangle;
class Ball : virtual public shape
{
public:
    float x, y, radious, speed_x, speed_y;
    void give(float x, float y, float radious, float speed_x, float speed_y)
    {
        this->x = x;
        this->y = y;
        this->radious = radious;
        this->speed_x = speed_x;
        this->speed_y = speed_y;
    }

    void draw()
    {
        DrawCircle(x, y, radious, Platinum);
    }

    void update()
    {
        x += speed_x;
        y += speed_y;
        if (y >= GetScreenHeight() - radious)
        {
            speed_y /= -1;
        }
        if (x >= GetScreenWidth() - radious || x <= radious)
        {
            speed_x *= -1;
        }
        if (y <= radious)
        {
            speed_y *= -1;
        }
    }
    friend bool operator+(Ball &ball, Triangle &t);
};
// derived class 2-----------------------------------------------------------------------------------
class Triangle : virtual public shape
{
public:
    float x1 = 600, x2 = 580, x3 = 620, y1 = 700, y2 = 800, y3 = 800;
    void give(float, float, float, float, float) {}
    void draw()
    {
        DrawTriangle({x1, y1}, {x2, y2}, {x3, y3}, RED);
    }
    void update()
    {
        if (IsKeyDown(KEY_LEFT) && x2 >= 0)
        {
            x1 -= 9;
            x2 -= 9;
            x3 -= 9;
        }
        if (IsKeyDown(KEY_RIGHT) && x3 <= GetScreenWidth())
        {
            x1 += 9;
            x2 += 9;
            x3 += 9;
        }
    }

    // operator overloading using friend function--------------------------------------------------
    friend bool operator+(Ball &ball, Triangle &t)
    {
        bool truth = 0;
        float dis_y = ball.y - t.y1;
        float dis_x = ball.x - t.x1;
        float dis = dis_y * dis_y + dis_x * dis_x;
        dis = sqrt(dis);
        if (dis <= ball.radious)
        {
            DrawText("BALL GET DAMAGED!!!", 200, 400, 100, RED);
            truth = 1;
        }
        return truth;
    }
};

// File Management-----------------------------------------------------------------------------------
class input_file
{
public:
    char inputText[256] = {0};
    int textLength = 0;
    void in(char intext[], int score)
    {
        ofstream outf("Record.txt", ios::app);

        outf << setw(15) << intext;

        outf << "\t" << setw(20) << score << endl;
        outf.close();
        ofstream out("Number.txt", ios::app);
        out << score << " ";
        out.close();
    }
};

Ball ball_1, ball_2, ball_3, ball_4, ball_5, ball_6;
Triangle triangle;
input_file file;

int main()
{

    const int screen_width = 1200;
    const int screen_height = 800;
    int score = 0;
    int j = 0;
    get_file();
    int high = Myset.highest();

    // initializing value-----------------------------------------------------------------------------

    ball_1.give(150, 200, 50, 3, -15);
    ball_2.give(450, 250, 45, 7, -9);
    ball_3.give(750, 310, 52, -5, -12);
    ball_4.give(1050, 400, 52, 5, -8);
    ball_5.give(250, 250, 60, 7, -18);
    ball_6.give(875, 175, 78, 5, -11);
    InitWindow(screen_width, screen_height, "2107052_Project_Game");

    SetTargetFPS(40);

    while (!IsKeyPressed(KEY_ENTER))
    {
        BeginDrawing();
        ClearBackground(WHITE);
        DrawText("Press ENTER to go", 2 * screen_width / 8, screen_height / 2, 50, BLACK);
        EndDrawing();
    }

    for (int i = 0; i < 130; i++)
    {
        ClearBackground(GRAY);
        BeginDrawing();
        triangle.draw();
        ball_1.draw();
        ball_2.draw();
        ball_3.draw();
        ball_4.draw();
        ball_5.draw();
        ball_6.draw();
        // for giving time to start game-------------------------------------------------------------
        DrawText(TextFormat("SCORE : %d", score), 500, 50, 50, WHITE);
        if (i > 40 && i < 60)
            DrawText("GET!!!!!!!!!!", 3 * screen_width / 8, screen_height / 2, 100, BLACK);
        if (i > 64 && i < 80)
            DrawText("SET!!!!!!!!!", 3 * screen_width / 8, screen_height / 2, 100, GREEN);
        if (i > 90)
            DrawText("GO!!!", 3 * screen_width / 8, screen_height / 2, 150, RED);
        EndDrawing();
    }
    system("cls");

    while (WindowShouldClose() == false)
    {
        j++;

        if (j % 160 != 0)
        {
            score++;
            DrawText(TextFormat("SCORE : %d", score), 500, 50, 50, WHITE);
        }
        ClearBackground(GRAY);
        BeginDrawing();

        // drawing---------------------------------------------------------------------------------
        triangle.draw();
        triangle.update();

        ball_1.draw();
        ball_2.draw();
        ball_3.draw();
        ball_4.draw();
        ball_5.draw();
        ball_6.draw();

        // updating position------------------------------------------------------------------------
        ball_1.update();
        ball_6.update();
        if (j > 100)
        {
            ball_2.update();
        }
        if (j > 270)
        {
            ball_3.update();
        }
        if (j > 350)
        {
            ball_4.update();
        }
        if (j > 550)
        {
            ball_5.update();
        }

        // collision checking--------------------------------------------------------------------

        if (
            ball_1 + triangle ||
            ball_2 + triangle ||
            ball_3 + triangle ||
            ball_4 + triangle ||
            ball_5 + triangle ||
            ball_6 + triangle)
        {
            break;
        }
        EndDrawing();
    }

    while (!IsKeyPressed(KEY_SPACE))
    {
        BeginDrawing();
        ClearBackground(GRAY);
        DrawText(TextFormat("SCORE IS : \n     %d", score), 400, 200, 50, YELLOW);
        DrawText(TextFormat("HIGHEST WAS : %d", high), 400, 400, 40, RED);
        DrawText("press SPACE to store record...", 400, 750, 30, WHITE);
        EndDrawing();
    }

    while (!WindowShouldClose())
    {
        int key = GetKeyPressed();

        if (key > 0 && file.textLength < sizeof(file.inputText) - 1)
        {
            file.inputText[file.textLength] = (char)key;
            file.textLength++;
        }

        if (IsKeyPressed(KEY_BACKSPACE) && file.textLength > 0)
        {
            file.textLength--;
            file.inputText[file.textLength] = '\0';
        }

        if (IsKeyPressed(KEY_ENTER))
        {
            printf("Entered Name : %s\n", file.inputText);
            file.in(file.inputText, score); // calling function to store data in file--------------------
            memset(file.inputText, 0, sizeof(file.inputText));
            file.textLength = 0;

            break;
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Draw the input text----------------------------------------------------------------------------
        DrawText("Enter Player name : ", 10, 10, 50, RED);
        DrawText(file.inputText, 200, 300, 50, DARKGRAY);
        EndDrawing();
    }

    CloseWindow();
    

    return 0;
}
