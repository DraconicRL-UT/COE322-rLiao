/****************************************************************
 ****
 **** This file belongs with the course
 **** Introduction to Scientific Programming in C++/Fortran2003
 **** copyright 2016-8 Victor Eijkhout eijkhout@tacc.utexas.edu
 ****
 **** dynrectangle.cxx : make a rectangle from pointers
 ****
 ****************************************************************/

//Importing the relevant libraries and functions using the include command
#include <iostream>
using std::cin;
using std::cout;

#include <cmath>
using std::sqrt;

#include <memory>
using std::make_shared,std::shared_ptr;

//Making the point class
class Point {
protected:
  float x,y;
public:
  Point(float ux,float uy) { x = ux; y = uy; };
  // Point class methods:
  //method to find horizontal ("x") distance between current point and another point
  float dx( Point other ) {
    return other.x-x; };
  //method to find vertical ("y") distance between current point and another
  float dy( Point other ) {
    return other.y-y; };
  //method find the diagonal distance between current point and another (pythagorean theorem)
  float distance(Point other) {
    float wd = dx(other), ht = dy(other);
    return sqrt( wd*wd + ht*ht );
  };
  //method for scaling the "radius" of a point in polar coordinates, in other words shifting the point diagonally by scaling it's old coordinates by a factor
  void scale(float factor){
    x = factor*x;
    y = factor*y;
  };
};

//making the rectangle class, which is rectangle object constructed of point objects
class Rectangle {
private:
  Point bottom_left,top_right;
public:
  Rectangle( Point bl,Point tr )
    : bottom_left(bl),top_right(tr) {};
  //method for calculating the area of the created rectangle by finding it's width and length by using point class methods of dy and dx respectively to calculate area using A = w*l
  float area() {
    float
      xsize = bottom_left.dx(top_right),
      ysize = bottom_left.dy(top_right);
    return xsize*ysize;
  };
};

//making the dynrectanlge class, which is rectangle object that relies on smart/shared pointers that point to point objects
class DynRectangle {
private:
  shared_ptr<Point> bl, tr;
public:
  DynRectangle( shared_ptr<Point> bottom_left, shared_ptr<Point> top_right ) : bl(bottom_left), tr(top_right) {};
  //method to calculate the area of the rectangle made; note that this is similar to the method for the rectangle class but it utilizes smart pointers to reference the point class methods
  float area(){
    float 
      xsize = bl->dx(*tr),
      ysize = bl->dy(*tr);
    return xsize*ysize;
  };
};

//main class for implementation of and usage of other classes
int main() {
  //initializing shared_pointer objects implicitly using "auto"
    auto
      origin  = make_shared<Point>(0,0),
      fivetwo = make_shared<Point>(5,2),
      tenfour = make_shared<Point>(10,4);
    //initializing the two dynrectangle objects of interest
    DynRectangle 
      lielow( origin,fivetwo ),
      //the bl point of the second rectangle is the same point as the tr point of the first rectangle
      flyhigh( fivetwo, tenfour);

    // record the initail (unscaled) areas:
    cout << "First Rectangle Area: " <<  lielow.area() << " & Second Rectangle Area: " << flyhigh.area() << '\n';

    // scale the `fivetwo' point by three (if scaled by 2, then the area of the second rectangle would be 0 as the tr point of the second rectangle in this instance is twice the bl point (so scaling bl by 2 would make the rectanlge a point instead of an rectangle hence yielding an area of zero)
    fivetwo->scale(3);

    // now the area should be adjusted accordingly
    cout << "Scaled Rectangle Area's: " <<  lielow.area() << " & " << flyhigh.area() <<'\n';

  return 0;
}
