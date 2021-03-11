/*
 * Snake Class
 *==========================================================================================================================================================================
 * Variables :
 *--------------------------------------------------------------------------------------------------------------------------------------------------------------------------
 * queue<Point> body.......The snake's body represented as a queue of points.
 * queue<Point> tempBody...The snake's body, inserted into a temporary queue for iteration. (I did not use an iterator, as it seemed easier just to store it in a temp var.)
 * int startingLen.........The starting length of the snakes body, which the snake will initially grow into.
 * Point location..........A set of coordinates denoting the snake's current position in the world.
 * Point direction.........A set of x and y values that represent the snakes direction. (0,1) for down, (0,-1) for up, (1,0) for right and (-1,0) for left.
 *==========================================================================================================================================================================
 * Functions
 *--------------------------------------------------------------------------------------------------------------------------------------------------------------------------
 * void setDir(int x, int y)......Assigns the pair of x and y values given to the Point direction variable.
 * int getPosx()..................Returns the value of the x position of the snake's point
 * int getPosy()..................Returns the value of the y position of the snake's point
 * bool drawBody(int x, int y)....Returns true if a body part is at the given x and y coordinate, otherwise, false. Used in w.DrawWorld() method in world.class.cpp.
 * int checkWin().................Returns 1, -1, or 0 to determine the game's state. 1 is win, -1 is a loss and 0 continues running. This also handles collision detection.
 * void Grow()....................This function pushes the snakes head location onto the queue and then moves the head in the direction of Point direction.
 * void Step()....................This function pops the tail, pushes the snakes head location onto the queue and then moves the head in the direction of Point direction.
 *==========================================================================================================================================================================
 * Description:
 *      The Snake class is a representation of the player. It contains the body in a queue structure, as it makes moving and growing the snake much easier, by just calling
 *   either push, or pop then push. The body has a starting length which is used during initialization. The body is initialized as a series of points with the values x = -1
 *   and y = -1 to get the body out of the way in the beginning, so as to not fail the player immediately by either being on top of the player, or in an unexpected position.
 *   The snake is initialized at position x = 1 and y = 1, the top left corner, and direction is initialized as right, so as to not allow the player to run straight into a
 *   wall (however, I've noticed that when you press arrow key up to go to your most recent command in the terminal, the program will initialize the direction as up).
 *
 *=========================================================================================================================================================================
 */


#ifndef SNAKE_CLASS
#define SNAKE_CLASS

#include <iostream>
#include <iterator>
#include <queue>
#include "point.class.cpp"

using namespace std;

class Snake{
private:

    queue<Point> body;

    int startingLen = 5;

    Point location;
    Point direction;

public:
    Snake(){ // Constructor
        location = Point(1,1);
        direction = Point(1,0);

        // Initialize body points as -1,-1
        for(int i = 0; i < startingLen; i++){
            body.push(Point(-1, -1));
        }

    }

    void setDir(int x, int y){  // Direction setter
        direction = Point(x, y);
    }

    // Getters
    int getPosx(){
        return location.x();
    }

    int getPosy(){
        return location.y();
    }

    bool drawBody(int x, int y){ // Returns true if a body point is seen at the given parameter's x & y pair, else, false.
        queue<Point> tempBody = body; // Temporary body, so we do not pop the actual snake's body

        for(int i = 0; i < body.size(); i++) { // For loop to iterate over the body
            if(tempBody.front().x() == x && tempBody.front().y() == y){ // If the point in the body is equal to the given point
                return true;
            }
            else if(!tempBody.empty()){ // Otherwise, if the tempBody queue isn't empty,
                tempBody.pop(); // Pop to get next front()
            }
        }

        return false;
    }

    void Grow(){
        body.push(location);   // Push the next body part to where the head is
        location = Point(location.x() + direction.x(), location.y() + direction.y()); // Move the head
    }

    int checkWin(Point size){

        if(body.size() >= (size.y() * size.x()) - 1){ // If the body size is greater or equal to the area of the game space minus one, then you win, return 1
            return 1;
        }

        else if(location.x() >= size.x() || location.y() >= size.y() || location.x() < 0 || location.y() < 0){ // Otherwise, if the snake collides with the walls return -1
            return -1;
        }
        else{ // Otherwise, check if the head makes contact with the body
            queue<Point> tempBody = body; // Temporary body, so we do not pop the actual snake's body

            for(int i = 0; i < body.size(); i++){ // For loop to iterate over the body

                if(location.x() == tempBody.front().x() && location.y() == tempBody.front().y()){  // If the point in the body is equal to the head's location, you lose, return -1

                    return -1;
                }
                else{
                    tempBody.pop(); // Get next Point in queue

                }
            }
        }

        return 0;
    }

    void Step(){ // Called each update, unless eating food
        body.pop(); // Pop front (last body part)
        body.push(location); // Push a new point to the head location
        location = Point(location.x() + direction.x(), location.y() + direction.y()); // Move the snake in direction of Point direction
    }
};

#endif