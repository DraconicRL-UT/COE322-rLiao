//Name: Robert Liao
//EID: RQL85


//Delcaring the relevant c++ libraries
#include <iostream>
#include <vector>

using namespace std;

//making the function to find the length of the Collatz conjecture
vector <int> maxSeq(int testN){
  // Initialzing the initial tracker variabels count (the length of current sequence) and next (the u_n+1) value, and the result vector which will output the two aforementioned variables (count and next)
  int count = 1;
  int next = testN;
  vector<int> result = { 1, 2} ;
  while (1==1){
    //making a temerination condition for when the current value in the sequence becomes = 1
    if (next == 1){
      break;
    }
    else {
      //if the value is even divide by two to find the next value
      if (next % 2 == 0){
	next = next/2;
      }
      else {
	//if the value is odd multiple by three then add one to find the next value
	next = 3*next + 1;
      }
      count++;
    }
  }
  //setting the outputs for the result vector
  result[0] = count; 
  result[1] = testN;
  return result;
}

//the main function which call the maxSeq function made above
int main(int maxCount, int guess){
//for loop to iterate through values of u1 from u1 = 1 up to u1 = 1000
  for (int i = 1; i <=1000; i++){
    vector<int> test = maxSeq(i);
    //if the length of the current sequence is longer than the current longest sequence make this the new longest sequence and output the u1 guess at which this occurs
    if (test.at(0) > maxCount){
      maxCount = test.at(0);
      guess = test.at(1);
    }
  }
  cout << "The longest sequence is " << maxCount<< "\n";
  cout << "This occured for initial guess of " << guess;
}
