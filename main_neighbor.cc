#include <iostream>
#include <vector>
#include <math.h>
#include <string>
#include <cstdlib>
#include "disease.h"

using namespace std;

int main(){

  srand(time(NULL));
  int pop_size;
  double amount_vacc;
  double prob;
  int sick_days=5;

  cout <<"What is the size of the population?\n";
  cin>> pop_size;

  cout << "What percentage of the population is vaccinated? (enter as a decimal)\n";
  cin>> amount_vacc;

  cout << "what is the probablity of transmission? (enter as a decimal)\n";
  cin >> prob;

  Population p(pop_size);
  Disease d(sick_days, prob);
  p.set_vacc(amount_vacc);
  p.set_prob(prob);
  p.random_vacc();
  int initperc= round(pop_size*0.02);
  int init=round(rand()%initperc); 
  p.random_infect(d,init);
  
  int runtime=0;
  while(p.count_infected()>0){
    p.one_more_day();
    cout << "one more day: " << runtime << "\n";    
    p.infect_neigh();
    runtime++;
    }


  cout << "It took " << runtime << " days for the disease to run through a population of " << pop_size << " \n";
  cout << p.count_recovered() << " people are recovered \n";
  cout << p.count_sus()<<" people are still susceptible \n";
  cout << p.count_infected() << " count infected \n";
  cout << p.count_vaccinated() << " count vaccinated \n";

  return 0;
}
