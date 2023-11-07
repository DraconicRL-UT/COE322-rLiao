/****************************************************************
 ****
 **** This file belongs with the course
 **** Introduction to Scientific Programming in C++/Fortran2003
 **** copyright 2017-2023 Victor Eijkhout eijkhout@tacc.utexas.edu
 ****
 **** findzeroclass.cxx : root finding library based on OOP
 ****
 ****************************************************************/

//Group with: Mahi Juthani, tacc user: mdj2367

#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

class polynomial {
private:
  std::vector<double> coefficients;
public:
  polynomial( std::vector<double> c ){
    coefficients = c;
    //check if the coefficients vector is non-zero and if the 0th term is also non-zero, if either is false then throw an exception
    if (coefficients.size() == 0 || coefficients.at(0) == 0.0){
      throw invalid_argument("The 0th coefficient needs to be non-zero");
    }
  };
  bool is_odd() const{
    //check if the there are an odd number of coefficients
    return (coefficients.size() % 2 == 1);
  };
  double evaluate_at(double x) const{
    //makes tracker variable to store the f(x) value
    double result = 0.0;
    for (int i = 0; i<coefficients.size();i++){
      // iterates through the powers of x, then computes each term (coefficient times x to the respective power) and sums it up
      result += (coefficients.at(i))*pow(x, (1.0*i));
    }
    //return tracker variable, should be ~= f(x)
    return result;
  };
  //overloading the evlauate_at() variable
  double operator()(double x) const { return evaluate_at(x); };
};

void find_initial_bounds
( const polynomial &poly,double &left,double &right){
  //check if the polynomial is odd, otherwise throw eorr (invalid arguemtn)
  if(not poly.is_odd()){
    throw invalid_argument("Needs to be odd degree polynomial");
  }
  //check if left point is less than right and not reverse, otherwise throw error
  else if(not (left < right)){
    throw invalid_argument("Left point must be less than right point");
  }
  else{
    // calculate a midpoint value between the left and right points
    double midpt = (left+right)/2.0;
    //check if the current midpoint value is the solution, if it is, then do nothing to the input bounds (in other words, the input values will be the iinitial bounds)
    if (poly.evaluate_at(midpt)==Catch::Approx(0.0)){
      return;
    }   
    //if the solution is in the left half of the current interval (left, right), then make intial bounds the left input and set the midpoint to be the new right bound 
    else if (poly.evaluate_at(left)*poly.evaluate_at(midpt)<=Catch::Approx(0.0)){
      right = midpt;
    }
    //if the solution is in the right half of the interval, make the initial bounds the midpoint and the right input bound
    else {
      left = midpt;
    }
  }
};

void move_bounds_closer
( const polynomial& poly,double& left,double& right,bool trace=false ){
  //check if input polynomial value is odd, otherwise throw error
  if(not poly.is_odd()){
    throw invalid_argument("Needs to be odd degree polynomial");
  }
  //check that left and right points are not reverse or equal
  else if(not (left < right)){
    throw invalid_argument("Left point must be less than right point");
  }
  else{
    double midpt = (left+right)/2.0;
    //while the left bound<right bound and f(left)*f(right)<=0 keep moving the bounds closer
    while(poly.evaluate_at(left)*poly.evaluate_at(right)<=Catch::Approx(0.0) && left<right){
      //check if left bound is equal to right bound if so, there is a computation/implementation bug, which will cause a runtime error, so throw a runtme error message
      if ( left == Catch:Approx(right)){
	throw runtime_error("Failed to find convergence upon a solution.");
      }
      //if the midpoint is the soultion, bring left and right bounds marginally closer, then exit loop
      else if (poly.evaluate_at(midpt)==Catch::Approx(0.0)){
	left+=.1;
	right-= .1;
	break;
      }   
      //if the solution is in the left half of the current interval, make the new right bound the midpoint (thereby cutting the interval in half)
      else if (poly.evaluate_at(left)*poly.evaluate_at(midpt)<=Catch::Approx(0.0)){
	right = midpt;
      }
      //else if the solution is in the right half of the current interval, make the new left point the midpoint
      else {
	left = midpt;
      }
    }
  }
};

double find_zero( const polynomial& poly,double prec,bool=false ){
  //verify that the polynomial is odd, otherwise throw an error
  if(not poly.is_odd()){
    throw invalid_argument("Needs to be odd degree polynomial");
  }
  //initialize a guess variable for left and right values, then calculate the midpoint (xSol) value, which corresponds to the inital guess solution
  double guessLeft = - 10.0, guessRight = 10.0; 
  double xSol = (guessLeft + guessRight)/2.0;
  //find the inital bounds that contains the solution
  find_initial_bounds(poly, guessLeft, guessRight);
  //until the solution is precise enough, keep moving the bounds closer towards the solution
  while(not (abs(poly.evalaute_at(xSol))<prec)){
    //call the move_bounds_closer function to iteratively bring bounds closer to solution until a certain precision
    move_bounds_closer(poly, guessLeft, guessRight);
    xSol = (guessLeft + guessRight)/2.0; 
  }
  //output the calculated solution/zero x value
  return xSol;
};

double f(int n){
  //make sure that f outputs a positive double value of n
  return std::abs(1.0*n);
}
