#include "test.h"
#include "galeshapley.h"
#include "person.h"
#include <string>
#include <iostream>
#include <unordered_set>
#include <cstdlib>
#include <ctime>

// takes two arrays, p and q
// for each person in p, it will assign n random rankings of people in q
void assignRanking(std::vector<Person*> p, std::vector<Person*> q){
  // For each person in p, choose a random person in q
  int n = p.size();
  
  for (Person* person : p){
    std::unordered_set<int> chosen;
    // choose a random person, then rank them in 1, 2, 3, etc
    for (int i = 1; i <= n; i++){
      int choice = rand() % n; // choice is between 0 and 7
      while (chosen.find(choice) != chosen.end()){ // if you've already ranked, then find a new person
	choice = rand() % n;
      }
      person->ranking[q[choice]] = i; // males[person *] = 1,2,..,8
      chosen.insert(choice);
    }
  }
}


// takes no input
// dynamically creates a people structs, then puts them into an array
// and returns a 2D array where arr[0] = proposers and arr[1] = proposees
// returns the 2D array
std::vector<std::vector<Person*>> initializePeople() {
  std::vector<Person*> males;
  std::vector<Person*> females;

  // dynamically create new people
  Person* bob = new Person{"Bob", {}, {}, 0, NULL};
  Person* mark = new Person{"Mark", {}, {}, 0, NULL};
  Person* tom = new Person{"Tom", {}, {}, 0, NULL};
  Person* james = new Person{"James", {}, {}, 0, NULL};
  Person* william = new Person{"William", {}, {}, 0, NULL};
  Person* nigel = new Person{"Nigel", {}, {}, 0, NULL};
  Person* gregory = new Person{"Gregory", {}, {}, 0, NULL};
  Person* clive = new Person{"Clive", {}, {}, 0, NULL};
  Person* louis = new Person{"Louis", {}, {}, 0, NULL};
  Person* john = new Person{"John", {}, {}, 0, NULL};
  
  Person* alice = new Person{"Alice", {}, {}, 0, NULL};
  Person* jane = new Person{"Jane", {}, {}, 0, NULL};
  Person* lola = new Person{"Lola", {}, {}, 0, NULL};
  Person* cathy = new Person{"Cathy", {}, {}, 0, NULL};
  Person* kayla = new Person{"Kayla", {}, {}, 0, NULL};
  Person* emma  = new Person{"Emma", {}, {}, 0, NULL};
  Person* eevie = new Person{"Eevie", {}, {}, 0, NULL};
  Person* jeanne = new Person{"Jeanne", {}, {}, 0, NULL};
  Person* megan = new Person{"Megan", {}, {}, 0, NULL};
  Person* mia = new Person{"Mia", {}, {}, 0, NULL};
  
  // add to lists
  males.push_back(bob);
  males.push_back(mark);
  males.push_back(tom);
  males.push_back(james);
  males.push_back(william);
  males.push_back(nigel);
  males.push_back(gregory);
  males.push_back(clive);
  males.push_back(louis);
  males.push_back(john);
  
  females.push_back(alice);
  females.push_back(jane);
  females.push_back(lola);
  females.push_back(cathy);
  females.push_back(kayla);
  females.push_back(emma);
  females.push_back(eevie);
  females.push_back(jeanne);
  females.push_back(megan);
  females.push_back(mia);

  // set up preference rankings randomly
  assignRanking(males, females);
  assignRanking(females, males);
    
  for (const auto& person : males){ // iterate through the each person
    for (const auto& rank : person->ranking){ // iterate through the hashmap
      person->preferences.resize(10);
      person->preferences[rank.second-1] = rank.first; // arr[ranking] = person
    }
  }

  for (const auto person : females){
    for (const auto& rank : person->ranking){
      person->preferences.resize(10);
      person->preferences[rank.second-1] = rank.first; // (ranking : person) tuple
    }
  }  

  // expected: (alice, bob, ...) (jane, mark, ...)
  std::vector<std::vector<Person*>> people = {males, females};  
  return people;
}


int main(void){

  srand(time(0));
  std::vector<std::vector<Person*>> people = initializePeople();

  GaleShapley(people);

  return 0;
}
