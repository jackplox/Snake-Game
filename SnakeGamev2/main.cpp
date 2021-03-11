
/*
 * Snake Game  -  Written by Jack Johnson
 *
 * Main
 * ===============================================================================================================
 *  Variables:         |                                                                                         |
 * --------------------------------------------------------------------------------------------------------------|
 * World w........................World, This is the world in which everything occurs. Refer to world.class.cpp  |
 * float waitTime.................This is the amount of seconds to wait before updating the world.               |
 * float sec......................This is the current amount of seconds since w.Update was last called           |
 * auto start, stop, duration.....These are variables to get sec from the chrono namespace.                      |
 * ===============================================================================================================
 *
 * Description:
 *
 *      This function is essentially a while loop that keeps running until w.s.checkWin() returns either 1 or -1,
 *  for win and loss respectively. The function uses the chrono namespace to keep track of the time elapsed
 *  since the Update method was last called, and is reduced each time the player receives 3 fruit.
 *
 *      You win by having your snake fill up the entire board, and lose by either hitting your tail, or running
 *  into the walls.
 *
 * ==============================================================================================================
 *
 *      Controls:
 *
 *  Use the arrow keys to move the snake.
 *
 *          ^ ----- UP
 *       <  v  > -- RIGHT
 *       |  L______ DOWN
 *       L_________ LEFT
 *
 * ==============================================================================================================
 */

#include <iostream>
#include <Windows.h>
#include "food.class.cpp"
#include "world.class.cpp"
#include <chrono>


using namespace std;

int main(){
    World w;

    // Initializing waitTime and sec
    float waitTime = 0.75f;
    float sec = 0.0f;

    // Start the timer before the loop, so it doesnt get reset each iteration
    auto start = chrono::high_resolution_clock::now();

    // Draw the world before Update, so the user can see around them before moving.
    w.drawWorld();

    // Game while Loop, gameOver is the value returned by w.s.chekWin()
    while(w.gameOver == 0){

        if (w.score >= w.targetScore){
            w.targetScore += 15;         // Add to the targetScore, which is the amount of points necessary to decrease the wait time by 25%
            waitTime = waitTime * 0.75f; // Decrease the refresh rate by 25%
        }

        if(sec >= waitTime){ // Check if the amount of seconds elapsed is greater or equal to the wait time
            w.Update(); // Updates the world
            start = chrono::high_resolution_clock::now(); // Reset timer
        }


        // Check key presses

        if(GetAsyncKeyState(VK_UP)){
            w.s.setDir(0,-1);   // Refer to snake.class.cpp for w.s.setDir()
        }
        if(GetAsyncKeyState(VK_DOWN)){
            w.s.setDir(0,1);
        }
        if(GetAsyncKeyState(VK_LEFT)){
            w.s.setDir(-1,0);
        }
        if(GetAsyncKeyState(VK_RIGHT)){
            w.s.setDir(1,0);
        }

        //End timer and assign the result divided by 1000 to sec.
        auto stop = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::milliseconds>(stop - start); // Receive duration in milliseconds
        sec = duration.count() / 1000.0f; // Dividing milliseconds by 1000 to receive more accurate measurement

    }

    // check gameover state. If its anything other than 1 or -1, something went wrong
    switch(w.gameOver){
        default:
            cout << "Error, Something has gone wrong... gameOver = " << w.gameOver << endl;
            return -1;
        case 1:
            cout << "\n\n\t\tCONGRATULATIONS!\n\tYouv'e won the game! Your total score was: " << w.score << "\n\nTry again with a new field size!\n\n" << endl;
            return 0;
        case -1:
            cout << "\n\n\t\tGAME OVER.\n\tYour total score was : "<< w.score << endl;
            return 0;
    }

}