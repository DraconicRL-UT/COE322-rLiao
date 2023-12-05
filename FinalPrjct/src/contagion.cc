//include the header file
#include "contagion.h"

using namespace std;

// method for neighbor only infection contagion model
void Population::infectNeigh(){
  bool touched = false; // bool to track if anybody was infected in the current day or not
  for(int i = 0; i < people.size(); i++){   
    if (touched){ // check if someone has already been infect, if so, then wait till next day before infecting others
      break;
    }
    //for first element/person, check if both are sick and if they have the same varinat, if so, do nothing and continue onto next person
    if (i == 0) {
      if(people[i+1].isSick() && people[i].isSick() && (people[i].whatVariant() == people[i+1].whatVariant())){
	continue;
      }
      //if the 0th and 1st people werent both sick with same vairant,  lets the two people interact/touch and check if they are now both sick, if so increase the tranmission count and set the bool touched to true so that next iterantion knows someone has been infected already and should wait till next day before proceeding to infect others
      people[i+1].touch(people[i], cVariant);
      if (people[i+1].isSick() && people[i].isSick()){
	cTransmit++;
	touched = true;
      }
    }
    //checks the last and second last person
    else if (i == people.size()- 1){
      if(people[i-1].isSick() && people[i].isSick() && (people[i].whatVariant() == people[i-1].whatVariant())){
	continue;
      }
      people[i-1].touch(people[i], cVariant);
      if (people[i-1].isSick() && people[i].isSick()){
	cTransmit++;
	touched = true;
      }
    }
    //check the person before and after current and touch/interact if the same previously mentioned conditions are true
    else if(people[i-1].isSick() && people[i].isSick() && (people[i].whatVariant() == people[i-1].whatVariant())){
      if(people[i+1].isSick() && people[i].isSick() && (people[i].whatVariant() == people[i+1].whatVariant())){
	  continue;
      }
      people[i+1].touch(people[i], cVariant);
      if (people[i+1].isSick() && people[i].isSick()){
	cTransmit++;
	touched = true;
      }
      continue;
    }
    else{
      people[i-1].touch(people[i], cVariant);
      if (people[i-1].isSick() && people[i].isSick()){
	cTransmit++;
	touched = true;
      }
      if(people[i+1].isSick() && people[i].isSick() && (people[i].whatVariant() == people[i+1].whatVariant())){
	  continue;
      }
      people[i+1].touch(people[i], cVariant);
      if (people[i+1].isSick() && people[i].isSick()){
	cTransmit++;
	touched = true;
      }
    }
    //after all interactions, check if the current tranmsision count has exceeded the mutation threshold/rate, if so, then increase the variation count and reste the tranmission count
    if (cTransmit >= mutateThresh){
	cVariant++;
	cTransmit = cTransmit - mutateThresh;
    }
  } 
};
// the SIR contragion model for infection
void Population::infectSIR(){
  int maxContacts = 6; // setting max contacts to 6 per person 
  bool touched = false; // same function as before
  for(int i = 0; i < people.size(); i++){
    if (touched){
      break;
    }
    //for each sick person or person in incubation period, let them interact with 6 random people besides themselves
    if(people[i].isSick()  || people[i].isIncub() ){
      for(int j = 0; j < maxContacts; j++){
	int randPerson = round(rand() % people.size());
	//while loop to make sure the random element used to simulate a person isnt the current element/ person instance
	while(randPerson == i){ // note that this likely only runs at most 1 time per ith iteration in the upper for loop
	  randPerson = round(rand() % people.size());
	}
	//check if the random person status and touch if need
	if ((people[randPerson].isSick()  || people[randPerson].isIncub() ) != (people[i].isSick()  || people[i].isIncub() )){
	  people[randPerson].touch(people[i], cVariant);
	  if ((people[randPerson].isSick()  || people[randPerson].isIncub()  ) && (people[i].isSick() || people[i].isIncub() )){
	    cTransmit++;
	    touched = true;
	  } 
	}
      }
    }
    /*    else if(people[i].isSDist()){
      if ((i-3 < 0) || (i+3 > people.size() -1)){ 
	if (i - 3 < 0){
	  if (i - 2 < 0){
	    if (i - 1 >= 0){
	      people[i-1].touch(people[i], cVariant);
	    }
	  }
	  people[i-2].touch(people[i], cVariant);
	  people[i-1].touch(people[i], cVariant);
	}
	if (i + 3 > people.size() - 1){
	  if (i + 2 < people.size() - 1){
	    if (i + 1 <= people.size() - 1){
	      people[i+1].touch(people[i], cVariant);
	    }
	  }
	  people[i+2].touch(people[i], cVariant);
	  people[i+1].touch(people[i], cVariant);
	}
	} 
      else {
	people[i-3].touch(people[i], cVariant);
	people[i-2].touch(people[i], cVariant);
	people[i-1].touch(people[i], cVariant);
	people[i+3].touch(people[i], cVariant);
	people[i+2].touch(people[i], cVariant);
	people[i+1].touch(people[i], cVariant);
      }
      } */ 
    //update the variant counter and rest tranmission count as need same as before
    if (cTransmit >= mutateThresh){
      cVariant++;
      cTransmit = cTransmit - mutateThresh;
    }
  }
};
//function to randomly vacciante people based on the vaccination percentage of the population
void Population::rand_nVac(){
  int nVacc_d = round(perVac*people.size()); 
  for( int i = 0; i < nVacc_d ; i++){
    int randPerson = round(rand() % people.size());
    while(!people[randPerson].isVul()) {
      randPerson = round(rand() % people.size());
    }
    people[randPerson].vaccinate();
  }
};
// function to randomyl infect (init_infect) an amount of people wiht a disease_name
void Population::randInfect(Disease disease_name, int init_infect){ 
  if(init_infect > this->cVul()){
    init_infect = this->cVul();
  }
  for(int i = 0; i < init_infect; i++){
    int randPerson = round(rand() % people.size()); 
    while(!people[randPerson].isVul()){
      randPerson = round(rand() % people.size());
    }
    people[randPerson].infect(disease_name);
    if (people[randPerson].isSick()){
      cTransmit++;
    }
  }
};

