//initalizing standard relevant c++ libaries 
#include <iostream>
#include <vector>

using namespace std;

bool isprime(int num){
  //loop for all numbers starting from 2 (so as to not divide by one) up to the input number, num
  for (int i = 2; i<= num; i++){ 
    //checking if the number is divisible by a number other than itself and 1, if so then the input number, num, is not a prime number so return false
    if (num!= i && num%i == 0){
      return false;
    }
  }
  //if the number was not divisible by any of the numbers from 2 up to num-1, then the input number was only divisible by itself and 1 and therefore a prime number, so return true
  return true;
}

class primeGen{

private:
  int pC, cP;
public:
  //default constructor where there are no prime numbers yet and the current number is 1
  primeGen() {pC = 0; cP = 1;};
  primeGen(int primeCount, int currentPrime) { pC = primeCount; cP = currentPrime;};
  //return the total number of primes found thus far
  int number_of_primes_found(){
    return pC;
  };
  //find next prime number by iterating from current number incrementally until next prime number is found
  int nextprime(){
    //want to start with number of 2 as it is first prime number
    int currentN = cP +1;
    while (1 == 1){
      //checking if the current number is a prime number using the isprime function, if it is prime set the current prime (cP) equal to the current number and increase the prime counter (pC) by 1 then return cP 
      if (isprime(currentN)){
	cP = currentN;
	pC++;
	return cP;	
      }
      //otherwise if current number is not a prime number, increase the current number by one before iterating again
      currentN++;
    }
  };
};

//main function for calling and testing class objects
int main(){
  //take in a number nprimes and calculate that many prime numbers
  int nprimes;
  cin >> nprimes;
  //calling the default constructor for the primeGen class
  primeGen sequence;
  //while the total number of primes found is less than the desired amount, continue finding the next number and output its value
  while (sequence.number_of_primes_found()<nprimes){
    int number  = sequence.nextprime();
    cout << "Number "<<number << " is prime " << '\n';
  }
}
