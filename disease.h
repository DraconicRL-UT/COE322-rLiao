#include <iostream>
#include <math.h>
#include <string>
#include <vector>
#include <cstdlib>

using namespace std;

enum HealthEnum {sick, sus, recover, vacc};


class Disease { //touch method, takes into acc probability and if they get inf\ected.


  private:

    double prob;
    int infecDays;

  public:

   Disease(int days, double transmitProb){
    this->infecDays=days;
    this->prob=transmitProb;
   };

   Disease(){ // for bonus
    this->infecDays=0.0;
    this->prob=0.0;
    };

   double transfer_probability(){
    return prob;
   };
   
   int duration(){
    return infecDays;
   };

 };


class Person {

 private:

  int days = 1;
  int personNum;
  HealthEnum status; //= sus; //enum
  int sickDays;
  Disease disease;

 public:

  Person(int number){
    personNum=number;
    status = sus;}

  string status_string(){
     switch(status)
       {
       case sick : std::cout << "sick, "<< std::to_string(sickDays) <<" days to go\n";   break;
       case sus: std::cout << "suseptible\n"; break;
       case recover: std::cout << "recovered\n";  break;
       case vacc: std::cout << "vaccinated\n";  break;
       }
   }; //could make void if no need to return

  void one_more_day(){
    //days++;
     if(sickDays==0){return;}
     if(status == sick){ 
       //cout << "Sick days: " << sickDays << "\n";
       sickDays--; 
       if(sickDays<=0) {status=recover;}}
   };

  void touch(Person &person){
    this->infect(person.get_disease());
  };
   

  void infect(Disease disease_name){  
     //sickDays=infec.infecDays;
    disease = disease_name; 
    sickDays=disease_name.duration();
     if(status==sus){
       //double chance=(rand()/RAND_MAX);
       double chance = (rand() % 100 + 1)/(double)100;
       if(chance<=disease_name.transfer_probability()){
	 status=sick;}
     }};

// need a void touch(){}; ??
  
  bool is_sick(){return (status==sick);};
  bool is_sus(){return (status == sus);};
  bool is_vacc(){return (status==vacc);};
  bool is_recover(){return(status== recover);};
  void vaccinate(){ status = vacc; };
  int get_sickDays(){return sickDays;};

  Disease get_disease(){return disease;};

 };

class Population {
 private:
  vector<Person> people;
  double prob;
  double vaccinated;
  //int count_infected;

 public:
 
  Population(int n){ 
    //Disease d(5,prob);
    for(int i=0;i<n;i++){
      Person newPerson(i);
      //newPerson.get_disease() =d;
      //newPerson.get_sickDays()=d.duration();
      people.push_back(newPerson);
    }} 

  void set_prob(double p){ prob=p;}
  void set_vacc(double vac){vaccinated = vac;}
  void random_infect(Disease disease_name, int init_infect);
  void random_vacc();
  void infect_neigh();
  void infect_sir();

  int count_infected(){
     int count = 0;
     for(int i=0;i< people.size();i++){
       if(people[i].is_sick())
	 count++;
     } return count;
  }

  int count_vaccinated(){
     int count =0;
     for(int i=0;i< people.size();i++){
       if(people[i].is_vacc())
	 count++;
     } return count;}

  int count_recovered(){
    int count =0;
  for(int i=0;i< people.size();i++){
    if(people[i].is_recover())
      count++;
  } return count;}

  int count_sus(){
   int count =0;
   for(int i=0;i< people.size();i++){
     if(people[i].is_sus())
       count++;
   } return count;}

  void one_more_day(){
     for(int i=0;i< people.size();i++){
       people[i].one_more_day();}}

 };
