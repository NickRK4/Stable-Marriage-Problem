#include <iostream>
#include <vector>
#include <queue>
#include "galeshapley.h"


void initialState(const std::vector<Person*> group){
  int n = group.size();
  for (int i = 0; i < n; i++){ // for each person in group
    Person *temp = group[i];
    std::cout << temp->name << "'s ranking: ";

    for (int k = 0; k < n; k++){
      std::cout << k+1 << ": " << temp->preferences[k]->name << ", ";
    }

    std::cout << std::endl;
  }
}

void printResults(const std::vector<Person*> group){
  int n = group.size();
  for (int i = 0 ; i < n; i++){
    Person *temp = group[i];
    std::cout << "(" << temp->name << "," << temp->preferences[temp->next-1]->name << ")";
    std::cout << std::endl;
  }
}

Person* propose(Person* A, Person* B){
  std::cout << A->name << " proposes to " << B->name;
  // if B is unmatched, it's an automatic yes, also if B prefers the person A
  if (B->currentPartner == NULL){ // always accept if not engaged
    std::cout << " and " << B->name << " accepts!" << std::endl;	
    B->currentPartner = A;
    A->currentPartner = B;
    return NULL; // no one was rejected
  } else if (B->ranking[A] < B->ranking[B->currentPartner]){ // B prefers A to current partner
    std::cout << " and " << B->name << " accepts, replacing " << B->currentPartner->name << "!" << std::endl;
    Person *replacedPartner = B->currentPartner;
    replacedPartner->currentPartner = NULL; // replaced person has no current partner
    B->currentPartner = A;
    A->currentPartner = B;
    return replacedPartner; // old partner was rejected
  } else{ // B prefers the current partner
    std::cout << " and " << B->name << " rejects! :("<< std::endl;
    return A; // A was rejected
  }
}

void galeShapley(std::vector<std::vector<Person*>> people) {      
  std::queue<Person *> queue; // list of free people
  for (Person* person : people[0]){
    queue.emplace(person);
  } // each person from A proposes to their first option, WHOM they haven't propsed to yet.

  int i = 1;  
  while (!queue.empty()){
    std::cout << i++ << ": ";
      
    Person *proposer = queue.front(); // take the first person from the queue
    queue.pop();

    if (proposer->next >= proposer->preferences.size()){
      continue; // max next value is pref size - 1
    }
    
    Person *rejected = propose(proposer, proposer->preferences[proposer->next]); // returns the replaced
    proposer->next++; // next moves to their next preference
    
    if (rejected != NULL){ // someone was rejected
      queue.emplace(rejected); // add them back to the queue
    } 
  }
}