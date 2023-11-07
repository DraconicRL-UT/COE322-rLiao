#include <iostream>
#include <cmath>
#include <vector>
#define CATCH_CONFIG_MAIN
#include "../Catch2/src/catch2/catch_all.hpp"

using namespace std;

double f(int n){
  if (n<=0){
    n = -n;
  }
  return 1.0*n;
}


TEST_CASE ("needs to be postive 6"){
  REQUIRE( f(5) == 5.0 );
  REQUIRE( f(-5) == 5.0);
}
TEST_CASE ("needs to be postive 3"){
  REQUIRE( f(3) == 3.0 );
  REQUIRE( f(-3) == 3.0);
}

polynomial third{3,2,0,1};
if(not third.is_odd()){
  cout << "This program only works for odd-degree polynomials\n";
  exit(1);
}

auto zero = find_zero(coefficients, 1.e-8);
cout << "Found root " << zero << " with value " << coefficients.evaluate_at(zero) << '\n'; 

/*
int main(){

}*/
