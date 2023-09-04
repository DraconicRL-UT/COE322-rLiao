#include <iostream>
#include <vector>

using namespace std;

//making a vector function that passes an input vector by reference to output two vectors (one for even numbers of input and one for odds).
vector<int> sepOddsEvens (vector<int> &inputVect){ 
  //initializing empty vectors to sort the odd and even numbers into, as well as a "result" vector which will be outputed from this function
  vector<int> odds; vector<int> evens; vector<int> result;
  //Using a for loop to iterate through all elements of the input vector
  for (int i = 0; i< inputVect.size(); i++){
    //checking if the element at index i of the input vector is an even or odd number then adding it to the end of the respective vector
    if (inputVect.at(i) % 2 == 0){
      evens.push_back(inputVect.at(i));
    }
    else{
      odds.push_back(inputVect.at(i));
    }
  }
  //making the result vector to output, where the first element is the total count of odd numbers in the input vector; then the next elements are all the odd elements; followed by all the even elements in the input vector
  result.push_back(odds.size());
  //the length of the results vector is the total number of odds and evens, which is the size of the two vectors plus one, but since starting from index i =0, we iterate until i < sum of the size of the odd and even vector
  for (int i = 0; i< odds.size() + evens.size(); i++){
    //checking if i is less than the total number of odd numbers, if so then add the corresponding odd element into the result vector, otherwise add the even elements to the results vector 
    if (i < odds.size()){
      result.push_back(odds.at(i));
    }
    else{
      //i-odds.size() to adjust the current index pointer to match with the indices of the evens vector
      result.push_back(evens.at(i-odds.size()));
    }
  }
  return result;
}

//declaring the int main function to call the sepOddsEvens function with 
int main (){
  //initializing empty variables to be used later
  vector <int> inputVect; int input;
  //taking in an input of test vector to be sorted into odd and even elements
  cout<< "Please input a test vector to be sorted: " << endl;
  //while the user is putting in inputs, keep adding the integers into the end of the vector inputVect (note: to finalize the vector input "esc + enter" keys)
  while (cin >> input){ 
    inputVect.push_back(input);
  }
  //outputting the input vector for reference
  for (int i = 0; i <inputVect.size(); i++){
    if (i==0){
      cout << "The input is: \n" << inputVect.at(0);
    }
    else{
      cout << "," << inputVect.at(i);
    }
  }
  //calling the sepOddsEvens Function to get the results vector and then declaring the two vectors of interest (oddVect and evenVect respectively)
  vector <int> resultsVect = sepOddsEvens(inputVect); 
  vector<int> oddVect; vector<int> evenVect;
  //saving the first element of the results vector output as the total count of odd numbers from the input (this will be used to correct the index pointers to align with the indices for the elements of interest)
  int oddCount = resultsVect.at(0); 
  for (int i=1; i<resultsVect.size(); i++){
    if (i < oddCount+1){ 
      oddVect.push_back(resultsVect.at(i));
    }
    else{
      evenVect.push_back(resultsVect.at(i));
    }
  }
  //neatly outputting the elements in the odd vector
  for (int i = 0; i < oddVect.size(); i++){
    if (i == 0){
      cout << "\nThe odds are: \n" << oddVect.at(0);
    }
    else {
      cout << "," << oddVect.at(i);
    }
  }
  //neatly outputing the elements in the even vector
  for (int i = 0; i < evenVect.size(); i++){
    if (i ==0){
      cout << "\nThe evens are: \n" << evenVect.at(0);
    }
    else{
      cout << "," << evenVect.at(i);
    }
  }
  cout << "\n";
}
