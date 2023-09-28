#include <iostream>
#include <vector>
#include <cmath>
#include <functional>
#include "cxxopts.hpp"
using namespace std;

double newton_root( function< double(double) > f, function< double(double) > fprime ) {
  double x{1.};
  while ( true ) {
    auto fx = f(x);
    //cout << "f( " << x << " ) = " << fx << '\n';
    if (abs(fx)<1.e-10 ){
      break;
    }
    x = x - fx/fprime(x);
  }
  return x;
};

double newton_root (function < double(double)> f){
  double x{1.}; double h{1.e-6}; 
  while ( true ) {
    auto fx = f(x);
    auto fprimex = (f(x+h) - f(x))/h;
    //cout << "f( " << x << " ) = " << fx << '\n';
    if (abs(fx)<1.e-10 ){
      break;
    }
    x = x - fx/fprimex;
  }
  return x;
};

int main(int argc, char **argv){

  cxxopts::Options options("cxxopts", "Commandline options demo");
  options.add_options() ("h, help", "usage information"); 
  options.add_options() ("v, value", "newton root value", cxxopts::value<double>()->default_value("3.14"));
  auto result = options.parse(argc, argv);
  if (result.count("help")>0){
    cout << options.help() << '\n';
    return 0;
  }

  double n = result["value"].as<double>();  
  auto f = [n] (double x ) -> double { return x*x-n; }; 
  cout << "The root of this number is "<< newton_root( f ) <<'\n';

}
