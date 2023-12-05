//include relevant libaries
#include <iostream>
#include <vector>
#include <math.h>
#include <string>
#include <cstdlib>
#include "contagion.h"

using namespace std;

int main(){

  srand(time(NULL)); // initialze so that futuure instances of "rand()" will generate unique random numbers rather than the same intial random everything
  int popSize; // population size
  double perVacc; // percent vaccination 
  double exTransProb; // trnamission prob of the disease
  int exExpSickDays = 5; // expected nubmer of sick days

  //user input the simualtion pop size and vaccination percentage, and the transmission probability
  cout << "Population size?\n";
  cin >> popSize;
  cout << "Percentage of population that is vaccinated?\n";
  cin >> perVacc;
  cout << "Probablity of transmission?\n";
  cin >> exTransProb;

  // make an instance sample population and flu disease
  Population sample(popSize);
  Disease flu(exExpSickDays, exTransProb);
  /* 
     // extra credit, can uncomment and work
  Disease flu;
  flu.duration() = exExpSickDays;
  flu.transfer_probability() = exTransProb;
  */
  //set the inital parameters accordingly
  sample.set_nVac(perVacc);
  sample.setProb(exTransProb);
  sample.rand_nVac();
  //determine an appropriate max intial infection ammount
  int maxInfectI = round(.05*popSize);
  int infectI = round(rand()%popSize);
  if (popSize <= 100){
    maxInfectI = round(.15*popSize); 
  }
  if (maxInfectI >= 50){
    maxInfectI = 50;
  }
  if (infectI > maxInfectI){
    infectI = round(rand()%maxInfectI);
  }
  // output the intial attemped infections (may be less due to natural immunity of individuals and if the diesase has a low tranmission probality)
  cout << "There were "<< infectI << " initial attempted infections\n";
  sample.randInfect(flu,infectI);

  //set the intial day to zero, then iterate day by day till there are no more infectees
  int contagionDuration = 0;
  while(sample.cInfect()>0){
    sample.one_more_day();
    sample.infectNeigh();
    contagionDuration++;
  }

  //output easily readable data
  cout << "It took " << contagionDuration << " days for the disease to run it's course through a population of " << popSize << " \n";
  cout << sample.cRec() << " people have recovered \n";
  cout << sample.cVul()<<" people are still susceptible \n";
  cout << sample.cInfect() << " people are currently infected \n";
  cout << sample.cVac() << " people were vaccinated \n";
  cout << sample.howManyVar() << " variant (s) occured\n";
  if (sample.howManyVar() > 0){
    cout << "With a mutuation rate of " << sample.mutateRate() << " people before each mutation\n"; 
  }
  cout << sample.howManyTotalTransmit() << " total tranmissions of all variants occured, with " << sample.howManyCurrTransmit() << " tranmissions of the current variant\n";

  return 0;
}
