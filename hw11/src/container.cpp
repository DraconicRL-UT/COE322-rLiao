//Name: Mahi Juthani; EID: MDJ2367
//Name: Robert Liao; EID: RQL85


//importing the relvant libraries and using "using::std_" for convenience
#include <iostream>
using std::cout;
using std::cin;

#include <vector>
using std::vector;
#include <string>
using std::string;

//makeing a template class, namedvector that takes in a string name and int size then makes a namedvector object of the same type as the template T
template <typename T>
class namedvector
  : public vector<T> {
private:
  string _name;
public:
  //the constructor
  namedvector ( string n,int s ) : _name(n) ,vector<T>(s) {};
  //having an auto name method that returns the name of the namedvector object 
  auto name() {
    return _name;
  };
  //note that no other vector methods were implemented as the templating of the vector class will inherit the methods from the vector class
}; 

//make a namespace "geo" that has a vector class that will be constructed to be the same as the namedvector class object made previously
namespace geo {
  template <typename T>
  class vector : public namedvector<T> {
  public:
    vector (string n,int s ): namedvector<T>(n, s) {};
  }; 
}

//implementing a main class that will call and test the namedvector class and the namespace geo::vector
int main() { 

  namedvector<float> fivetemp("five",5);
  cout << fivetemp.name()
       << ": "
       << fivetemp.size() << '\n';
  cout << "at zero: "
       << fivetemp.at(0) << '\n';  

  using namespace geo;
  geo::vector<float> float4("four",4);
  cout << float4.name() << '\n';
  float4[1] = 3.14;
  cout << float4.at(1) << '\n';
  geo::vector<string> string3("three",3);
  string3.at(2) = "abc";
  cout << string3[2] << '\n';
  
  return 0;
}
