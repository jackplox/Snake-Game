/*
 * World Class
 *====================================================================================================================================================
 * Variables:
 *----------------------------------------------------------------------------------------------------------------------------------------------------
 * int score..........The current score the player has accumulated.
 * int targetScore....The score the player must acquire to increase the game speed.
 * bool eatenFood.....A boolean that determines wether or not food has been eaten by the player. Is true when the snake's head passes through food.
 * Snake s............The player. Refer to snake.class.cpp
 * Food f.............The food on the screen.
 * Point size.........This is the size of the 2D game space, enclosed by '#'s.
 *====================================================================================================================================================
 * Functions:
 *----------------------------------------------------------------------------------------------------------------------------------------------------
 * void Update();
 *      Checks if food has been eaten, if it has, then randomize the food location, call s.Grow() and assign eatenFood to false. Otherwise,
 *      call s.Step(). After, it assigns gameOver to the value returned by s.checkWin(), and finally draws the world by calling
 *      drawWorld().
 *
 * void clear_screen();
 *      Uses an ANSI escape code to clear the screen.
 *
 * void drawWorld();
 *      This function will print out the world in ASCII art to the terminal after clearing the screen with clear_screen().
 *      # = Wall
 *      Q = Snake's head / Player position
 *      o = Part of the snake's body
 *      6 = A fruit that appears on the screen and increases the snakes tail length.
 *====================================================================================================================================================
 * Description:
 *
 *      This is the world in which the game is being played. It contains the snake, the food and the boundaries of the game space. This class also
 *      keeps track of the state of the game; running, win or loss.
 *
 *====================================================================================================================================================
 *
 */

#ifndef WORLD_CLASS
#define WORLD_CLASS
#include <time.h>
#include <iostream>
#include "snake.class.cpp"
#include "food.class.cpp"


using namespace std;

class World{

public:
    int score = 0;
    int targetScore = 15;

    Snake s;
    Food f;
    Point size;

    // 1 = win, 0 = running, -1 = loss
    int gameOver;

    // Constructor
    World(){
        size = Point(15,15); // Set size to an x & y, which defines the size

        // Randomizing initial food position
        srand(time(NULL));
        int x = rand() % size.x();
        srand(time(NULL));
        int y = rand() % size.y();

        // Instantiating snake and food objects
        s = Snake();
        f = Food(x,y);

        gameOver = 0;

    }

    void Update(){

        if(s.getPosy() == f.getPosy() && s.getPosx() == f.getPosx()){ // if snake head is at food position, if yes, randomize x and y for food, increase the score and grow the snake.
            // Randomize food x and y values
            srand(time(NULL));
            int x = rand() % size.x();
            srand(time(NULL));
            int y = rand() % size.y();
            f.setPos(x,y);

            // Increment player score
            score += 5;
            // Grow the snake
            s.Grow();
        }
        else { // Otherwise, call s.Step()
            s.Step();
        }

        gameOver = s.checkWin(size); // Refer to snake.class.cpp for more information about s.checkWin()
        drawWorld();

    }

    void clearScreen() { // Escape code clear the screen
        char ESC = 27;
        cout << ESC << "[2J";
    }

    void drawWorld(){
        clearScreen();

        cout << "\t\tSnake Game\nBy Jack Johnson\n\nScore : " << score << endl;

        // Top-Left corner
        cout << "# ";

        // Draw roof
        for(int i = 0; i < size.x(); i++){
            cout << " # ";
        }
        // Top Right corner
        cout << " #\n";

        // Draw under the roof
        for(int i = 0; i < size.y(); i++){
            // For loop for Y (Going down)

            // Left wall
            cout << "# ";
            //

            for (int j = 0 ; j < size.x() ; j++){
                //For loop for X (Going across to the right)

                // Snake head is there
                if(s.getPosx() == j && s.getPosy() == i){
                    cout << " Q ";
                }

                // Food is there
                else if(f.getPosx() == j && f.getPosy() == i){
                    cout << " 6 ";
                }

                // Body part is there
                else if(s.drawBody(j, i)){
                    cout << " o ";
                }

                // nothing there
                else {
                    cout << "   ";
                }

            }

            // Right wall, newline to go down one
            cout << " #\n";
            //
        }

        cout << "# ";

        // Draw the floor

        for(int i = 0; i < size.x(); i++){
            cout << " # ";
        }

        cout << " #\n" << endl;

    }




};


#endif
