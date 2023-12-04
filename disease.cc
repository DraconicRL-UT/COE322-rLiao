#include "disease.h"

//using namespace std;


void Population::infect_neigh(){
  for(int i=0;i< people.size();i++){
    if(people[i].is_sick()){
      if(i==0){
	if(people[i+1].is_sus){
	  people[i+1].touch(people[i]);}
      }
      else if(i==(people.size()-1)){
	if(people[i-1].is_sus){
	  people[i-1].touch(people[i]);}
      }

      else {
	if(people[i+1].is_sus){
	  people[i+1].touch(people[i]);}
      
	if(people[i-1].is_sus){
          people[i-1].touch(people[i]);}
      }}}};


void Population::infect_sir(){
  int ppl=6;
  for(int i=0;i< people.size();i++){
    if(people[i].is_sick()){
      for(int j=0;j<ppl;j++){
	int num = round(rand() % people.size());
	while(num==i){ 
	  num= round(rand() % people.size());}
	if(people[num].is_sus()){ 
	  people[num].touch(people[i]);}}}}};


void Population::random_vacc(){
  //if(prob==1){ return;}
   int pop_size=people.size(); //can you get pop_size from same place we getting amount_vacc
   int vacc= round(vaccinated*pop_size);
   for( int i=0; i<vacc;i++){
     int random = round(rand() % pop_size);
     while(!people[random].is_sus()) {
       random = round(rand() % pop_size);
     }
     people[random].vaccinate();
   }};

void Population::random_infect(Disease disease_name, int init_infect){ //need input of amount of initially infected?
  int pop_size = people.size();
  if(init_infect> this->count_sus()){
    init_infect = this->count_sus();}
  for( int i=0; i<init_infect;i++){
     int random = round(rand() % pop_size); //rand is for random person selection
     while(!people[random].is_sus()){
       random = round(rand() % pop_size);}
     if(people[random].is_sus()) {
       people[random].infect(disease_name);
          
//break;
     }}};

