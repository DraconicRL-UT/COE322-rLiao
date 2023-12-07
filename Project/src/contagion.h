//include relevant libaries
#include <iostream>
#include <math.h>
#include <string>
#include <vector>
#include <cstdlib>

using namespace std;

//making a disease class to track the disease parameters
class Disease{
private:
  double transProb; // the tranmission probability of the disease
  int expSickDays; // number of days a person will be sick for, aka the recovery period or how long until a person recovers form illness
  int incubDays; // for bonus, stores how long the incubation period is why
public:
  //constructor for disease class, assumes incubation period if about half the normal recovery period
  Disease(int days, double transmitProb){
    expSickDays = days;
    incubDays = round(.5*days);
    transProb = transmitProb;
  };
  //a default null constructor 
  Disease(){ // for bonus
    transProb = 0.0;
    expSickDays = 0;
    incubDays = 0;
  };
  //utilizes a getSet method to allow the null contructor case to work - for extra credit/bonus
  double& transfer_probability(){
    return transProb;
  };
  //same reasoning as before for getSet method
  int& duration(){
    return expSickDays;
  }; 
  //same reasoning as before for getSet method
  int& incubationPeriod(){
    return incubDays; // for extra credit
    }; 
};

//making a enumerated list for the statuses of a person object
enum patientStatus {vul, ill, rec, vac , inc };

//person class to track the relevant vairables
class Person {
private:
  int day; // current day of simulation
  int patientNum; // identitfication number
  patientStatus status; 
  int nDays2Rec; // days till recovery
  int nDays2Sym; // days in incubation until symptoms show
  Disease disease; // what disease if any
  int currVariant; // what variant if any
  bool newInfect; // if person was infected on the current day or not (if so, then they must wait till next day to infect someone)
public:
  //default construcotr
  Person(int number){
    patientNum = number;
    status = vul;
    day = 1;
    nDays2Rec = 0;
    nDays2Sym = 0;
    newInfect = true;
    currVariant = 0;
  };
  //string method that turnns enum list into string to funcation as a getStatus method of sorts
  string status_string(){
    switch(status)
      {
      case ill: cout << "sick, "<< to_string(nDays2Rec) <<" days to go\n";   break;
      case vul: cout << "suseptible\n"; break;
      case rec: cout << "recovered\n";  break;
      case vac: cout << "vaccinated\n";  break;
      case inc: cout << "incubating\n";  break;
      }
  }; 
  //a temporal advancement method to update the recovery or incubation status of a person object
  void one_more_day(){
    day++;
    if(status == ill){ 
      nDays2Rec--; 
      if(nDays2Rec <= 0) {
	status = rec;
      }
    } 
    else if (status == inc){
      nDays2Sym--;
      if(nDays2Sym <= 0) {
	status = ill;
      }
    }  
  };
  // a touch method that accounts for all interactions between two person objects
  void touch(Person &person, int &variant){
    //check if both are sick/incubating
    if ((this->isSick() || this->isIncub() ) && (person.isSick() || person.isIncub()  )){
      //check if one has a new variant, if so, then infect the one with an older variant with the new variant and update the variant varibale associated with the person object
      if (this->whatVariant() > person.whatVariant()){
	person.infect(this->whatDisease());
	person.newVariant(this->whatVariant());
      }
      else{
	this->infect(person.whatDisease());
	this->newVariant(person.whatVariant());
      }
    }
    // if this person is sick and the person person if vuleranble or recovery from an older variant, infect them
    else if (this->isSick() || this->isIncub() /* || this->isSDist()*/ ){
      if (person.isVul() || (person.isRec() && person.whatVariant() != this->whatVariant())){
	person.infect(this->whatDisease());
	person.newVariant(this->whatVariant());
      }
    }
    //if person person is sick and this person is vulernable or recoverying from an older variant, infect them
    else if (person.isSick()   || person.isIncub() /*|| person.isSDist()*/){
      if(this->isVul() || (this->isRec() && this->whatVariant() != person.whatVariant())){
	this->infect(person.whatDisease());
	this->newVariant(person.whatVariant());
      }
    }
  };
  //infect method that generates a random number to simulate the relative immunity of an individual compared to the population, and if it is less than or equal to the tranmissibility of the disease, get infected, otherwise "fight off disease" with naturual immunity
  void infect(Disease disease_name){  
    //randomly generate an immunity chance bteween zero and 100
    double relImmune = (rand() % 100 + 1)/100.0; 
    if(relImmune <= disease_name.transfer_probability()){
      //upadate the relvant info and stauts of the newly infected person
      status = ill;
      disease = disease_name; 
      nDays2Rec = disease_name.duration();
      nDays2Sym = disease_name.incubationPeriod();
      this->isNew() = true; 
    }
  };
  //getter method that checks if the current person object is ill/sick, vulnerable/suscpetible, vaccincated, recovering, is newly infected, or if the person is in icubation
  bool isSick(){
    return (status == ill);
  };
  bool isVul(){
    return (status == vul);
  };
  bool isVac(){
    return (status == vac);
  };
  bool isRec(){
    return(status == rec);
  }; 
  bool& isNew(){
    return newInfect;
  };
  bool isIncub(){
    return (status == inc);
  };/* 
  bool isSDist(){
    return (status == sDist);
    }; */
  
  //vaccinates a person
  void vaccinate(){
    status = vac;
  };
  //checks how many days till recovery
  int getDaysTillRec(){
    return nDays2Rec;
  };
  //checks what disease
  Disease whatDisease(){
    return disease;
  };
  //checsk what variant
  int whatVariant(){
    return currVariant;
  };
  //updates the variant of a person
  void newVariant(int newVar){
    currVariant = newVar;
  };
};

//population class for simulating the whole population
class Population {
private:
  vector<Person> people; // vector of person objects
  double transProb; // the transmission probility of the diesase
  double perVac; // the percentage of the populatuon that has been vacinated
  int cVariant; // the number of vaccinated ppl in pop
  int cTransmit; // count of number of transmissions of the current varaint
  int mutateThresh; // the mutatution rate 
public: 
  //default constructor
  Population(int n){ 
    transProb = 0.0;
    perVac = 0.0;
    cVariant = 0;
    cTransmit = 0;
    //mutation rate, set as a variable amount proportional to the total population size for more realisitic amount
    mutateThresh = 100;
    if (n >= 1000){
      mutateThresh = round(.01*n);
    }
    if (mutateThresh >= 1000){
      mutateThresh = 1000;
    }
    for(int i=0;i<n;i++){
      Person newPerson(i);
      people.push_back(newPerson);
    }
  }; 
  //a setter method for the tranmission probability
  void setProb(double p){ 
    transProb = p;
  };
  //a setter method for the percentage of the population that is vaccinated
  void set_nVac(double vac){
    perVac = vac;
  };
  //a function that randmomly infects an initial amount of ppl with a disease of interest
  void randInfect(Disease disease_name, int init_infect);
  //a functuion that randomly vaccinates the predetermined amount of vaccinations based on the vaccination percentage
  void rand_nVac();
  //the function to model the neighbor infection only contagion model
  void infectNeigh();
  //the function to model the SIR contagion model
  void infectSIR();
  //a countter method for total number of infectees
  int cInfect(){
    int count = 0;
    for(int i = 0; i < people.size(); i++){
      if(people[i].isSick() || people[i].isIncub()){
	count++;
      }    
    } 
    return count;
  };
  //a counter method for total number of vaccinated ppl
  int cVac(){
    int count = 0;
    for(int i = 0; i < people.size(); i++){
      if(people[i].isVac()){
	count++;
      }
    } 
    return count;
  };
  //count method for recovered ppl
  int cRec(){
    int count = 0;
    for(int i = 0; i < people.size(); i++){
      if(people[i].isRec()){
	count++;
      }
    } 
    return count;
  };
  //counts how many vulernable/susceptible ppl there are
  int cVul(){
    int count = 0;
    for(int i = 0; i < people.size(); i++){
      if(people[i].isVul()){
	count++;
      }
    } 
    return count;
  };
  //returns how many variants there are
  int howManyVar(){
    return cVariant;
  };
  //counts the total transmissions of all variants combined
  int howManyTotalTransmit(){
    return cVariant*mutateThresh + cTransmit;
  };
  //counts the current transmiussion of the current vairnat
  int howManyCurrTransmit(){
    return cTransmit;
  };
  //returns the mutation rate used in the simualtuon
  int mutateRate(){
    return mutateThresh;
  };
  //the population class version of the temporal advnacement method, one_more_day also seen in the person class - updates the day for each person
  void one_more_day(){
    for(int i = 0; i < people.size(); i++){
      people[i].one_more_day();
    }
  };
};
