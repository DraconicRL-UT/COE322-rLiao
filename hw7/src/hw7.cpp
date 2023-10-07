#include <iostream>
//#include <iomanip>
//#include "cxxopts.hpp"
//#define FMT_HEADER_ONLY
#include "fmt/include/fmt/format.h"

using fmt::print;


int main(){
  //int n = 3;
  //print("{}", n);
  for (int i = 0; i < 16; i++){
    for (int j = 0; j < 16; j++){
      int h = 16*i+j;
      //      std::string h = format("{}", (16*i+j));
      print("{:0>2x}  ", h);
    }
    print("\n");
  }
}
