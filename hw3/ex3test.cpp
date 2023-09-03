#include <iostream>
#include <vector>

using namespace std;

vector <int> maxSeq(int testN){
  //cout << "Enter guess \n";
  //cin >> testN;
  int count = 1;
  int next = testN;
  vector<int> result = { 1, 2} ;
  while (1==1){
    if (next == 1){
      break;
    }
    else {
      if (next % 2 == 0){
	next = next/2;
	//cout << "the next guess is " << next << "\n";
	//cout << "the count is " << count << "\n";
      }
      else {
	next = 3*next + 1;
	//cout << "the next guess is " << next << "\n";
	//cout << "the count is " << count << "\n";
      }
      count++;
    }
  }
  result[0] = count; 
  result[1] = testN;
  //cout << count << "\n";
  //cout << next;
  next = 1;
  count = 1;
  return result;
  //cout << "The length of the sequence was " << count;
}

int main(int maxCount, int guess){
  for (int i = 1; i <=10; i++){
    vector<int> test = maxSeq(i);
    if (test.at(0) > maxCount){
      maxCount = test.at(0);
      guess = test.at(1);
    }
  }
  cout << "The longest sequence is " << maxCount<< "\n";
  cout << "This occured for initial guess of " << guess;
}
