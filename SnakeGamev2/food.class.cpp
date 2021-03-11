/*
 * Food class
 *================================================================================================
 * Variables:
 *------------------------------------------------------------------------------------------------
 * Point location.............The current location of the food.
 *
 *================================================================================================
 * Functions:
 *------------------------------------------------------------------------------------------------
 * int getPosx()..............Returns the x coordinate
 * int getPosy()..............Returns the y coordinate
 * void setPos(int x, int y)..Assigns the location to a new point, given by the x and y arguments.
 *================================================================================================
 * Description:
 *       This is an object which holds a location, which is used to display the food in the game
 *    space. Only one item of food will appear on the screen at a time.
 *================================================================================================
 */


#ifndef FOOD_CLASS
#define FOOD_CLASS
#include "point.class.cpp"

using namespace std;

class Food{
    Point location;

public:
    Food(){
        location = Point();

    }
    Food(int x, int y){
        location = Point(x,y);
    }

    int getPosx(){
        return location.x();
    }

    int getPosy(){
        return location.y();
    }

    void setPos(int x, int y){
        location = Point(x, y);
    }
};

#endif