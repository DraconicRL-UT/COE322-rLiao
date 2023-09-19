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

class goldbachConj{

private:
  int e, p, q; vector<int> primes;
public:
  //default constructor for smallest goldbach conjecture
  goldbachConj() {e = 4; primes = {};};
  goldbachConj(int evenNum) {e = evenNum; primes = {};};
  //function to find prime numbers according to the goldbach conjecture
  void goldbach_findPrimes(){
    //initializing a primeGen object, seq, to generate the prime numbers up to the input evenNum
    primeGen seq; 
    //initializing a number, testPrime, to test if it can act as "p" in the conjecture, and adding it to a vector of primes that tracks alls the prime numbers
    int testPrime = seq.nextprime();
    primes.push_back(testPrime);
    //for each even number from 4 up to the bounded value input, e, do find the goldbach conjecture
    for (int i = 4; i <=e; i +=2){

      /* //This solution method finds iterates through the prime numbers until the largest prime number less than i is found, then computes its compliment q using q = e- p (appears to be a faster implementation?)
      //see if testPrime number is less than i, since we computed it beforehand so it could be larger than i; if it is less than i then set p as testPrime and iterate to the next prime number
      if (testPrime < i){
       	p = testPrime;
	testPrime = seq.nextprime();
	primes.push_back(testPrime);
      }
      else {
	//if the current prime number is larger than i, use the previous prime number as p
	p = primes.at(primes.size()-2);
      }
      //calculate q using q=e-p, then output the conjecture
      q = i - p;
      cout << "The number " << i << " is " << p << " + " << q << "\n"; 
    }
      */

      //this is the implementation method recommended in class for the goldbach conjecture and appears slower than the above method according to my tests - thoguht it was interesting to point out

      //for every prime number (starting from lowest) find q = e - p, and test if q is a prime number, if so output the conjecture
      for (int n = 0; n < seq.number_of_primes_found(); n++){
	p = primes.at(n);
	q = i -p;
	if (isprime(q)){
	  //if q is a valid prime number, then output the conjecture and break out this loop to continue onwards towards the next even number
	  cout << "The number " << i << " is " << p << " + " << q << "\n";
	  break;
	} 
      }
      //find the next prime number and test if it can be a valid p
      testPrime = seq.nextprime();
      primes.push_back(testPrime);
    }     

  };
  //finds the p,q,r triplets for every prime R up until a total of count of primeCount prime values have been found
  void find_rpq(int primeCount){
    //initializing a primeGen object, seq, to generate the prime numbers up to the input evenNum; also initialize a primeGen object rSeq to generate all the values of "r" to test against
    primeGen seq, rSeq; 
    //initializing a number, testPrime, to test if it can act as "p" in the conjecture, and adding it to a vector of primes that tracks alls the prime numbers
    int testPrime = seq.nextprime();
    primes.push_back(testPrime);
    // initializing the first r value as 5 (the smallest prime that is equidistant to two other primes
    rSeq.nextprime(); rSeq.nextprime();
    int testR = rSeq.nextprime();
    //initializing a counter for how many triplets have been found, since using the prime counters for the two sequences above would be inaccurate
    int tripletsFound = 0;
    while(tripletsFound < primeCount){
      //make the testPrime number  = p, then calculate q, and check if q is prime, not equal to r (otherwise p = q = r would be equidistant of 0 from r), and if r is the midpoint between p and q
      p = testPrime; q = testR*2 - p;
      if (q!=testR && isprime(q) && (abs(q - testR) == abs(testR - p))){
	//if the current p,q,r triplet is valid print the triplet
       	if (q<p){
	cout << "The prime number " << testR << " is (" << q << " + " << p << ")/2 \n";
	}
	else{
	  cout << "The prime number " << testR << " is (" << p << " + " << q << ")/2 \n";
	}
	//advance the triplet counter and proceed onto the next r value to find the corresponding p,q,r triplet for
	tripletsFound ++;
	testR = rSeq.nextprime();
      }
      //advance the testiPrime sequence
      testPrime = seq.nextprime(); 
      primes.push_back(testPrime);
    }
  };
};


//main function for calling and testing class objects
int main(){
  //intitializing and inputing a count for how many prime numbers, r, to find p,q,r triplets for using the goldbach conjecture
  int nPCount;
  cout<<"How many prime numbers, r, would you like to test?\n";
  cin >> nPCount;
  //calling the default constructor for the goldbachConj class
  goldbachConj gbc;
  //using the find_rpq function to generate and output the rpq triplets
  gbc.find_rpq(nPCount);
}
