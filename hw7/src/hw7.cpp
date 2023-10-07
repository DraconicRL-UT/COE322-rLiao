//Importing the relevant libraries
#include <iostream>
#include "fmt/include/fmt/format.h"

using fmt::print;


int main(){
  //setting up an iterator to generate hex numbers
  for (int i = 0; i < 16; i++){
    for (int j = 0; j < 16; j++){
      int h = 16*i+j;
      //formating the output to be hex base and with 2 digits aligned to the right, so that "single" digits will have a "0" in front/left of the digit itself so that all values will be evenly spaced. Also note that the formated hex number is followed with two spaces to allow for even spacing string output
      print("{:0>2x}  ", h);
    }
    //after iterating through one set of hexes (one row of 16 hex numbers), start a new line
    print("\n");
  }
}
