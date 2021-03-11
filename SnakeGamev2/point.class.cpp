#ifndef POINT_CLASS
#define POINT_CLASS
/*
 * Point Class
 *========================================================================================
 * Variables
 *----------------------------------------------------------------------------------------
 *
 * int xcoord, ycoord............x and y coordinates that are points in 2D space. Private.
 *
 *========================================================================================
 * Functions
 *----------------------------------------------------------------------------------------
 *
 * int x();......................Getter for the x value.
 * int y();......................Getter for the y value.
 *
 *=======================================================================================
 * Description:
 *
 *      Self explanatory. This is a x,y coordinate system for a point on the map.
 *
 * --------------------------------------------------------------------------------------
 */


class Point{
private:
    int xcoord;
    int ycoord;

public:
    Point(){ // If no parameters given, initialize as zeroes
        xcoord = 0;
        ycoord = 0;
    }
    Point(int x, int y){ // Otherwise use the x and y given
        xcoord = x;
        ycoord = y;
    }

    // Getters
    int x(){
        return xcoord;
    }
    int y(){
        return ycoord;
    }

};




#endif