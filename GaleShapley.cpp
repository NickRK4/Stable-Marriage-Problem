#include <iostream>
#include <list>
#include <string>
#include <vector>

struct Person {
  std::string name;
  std::vector<Person*> preferences; // e.g. Bob: [Alice, Jane]
  std::unordered_map<Person *, int> ranking; // e.g Alice: 1, Jane: 2
  int next; // index of next person, B, that A will propose to
  Person * currentPartner; // index of their current partner
};


std::vector<std::vector<Person*>> initializePeople() {
  std::vector<Person*> males;
  std::vector<Person*> females;

  // dynamically create new people
  Person* bob = new Person{"Bob", {}, {}, 0, NULL};
  Person* mark = new Person{"Mark", {}, {}, 0, NULL};
  Person* tom = new Person{"Tom", {}, {}, 0, NULL};
  Person* alice = new Person{"Alice", {}, {}, 0, NULL};
  Person* jane = new Person{"Jane", {}, {}, 0, NULL};
  Person* lola = new Person{"Lola", {}, {}, 0, NULL};

  // add to lists
  males.push_back(bob);
  males.push_back(mark);
  males.push_back(tom);
  females.push_back(alice);
  females.push_back(jane);
  females.push_back(lola);

  // set up preference rankings
  bob->ranking[alice] = 1;
  bob->ranking[jane] = 2;
  bob->ranking[lola] = 3;

  mark->ranking[jane] = 1;
  mark->ranking[alice] = 2;
  mark->ranking[lola] = 3;

  tom->ranking[alice] = 1;
  tom->ranking[lola] = 2;
  tom->ranking[jane] = 3;
  
  alice->ranking[bob] = 1;
  alice->ranking[mark] = 2;
  alice->ranking[tom] = 3;

  jane->ranking[bob] = 2;
  jane->ranking[mark] = 1;
  jane->ranking[tom] = 3;

  lola->ranking[mark] = 1;
  lola->ranking[tom] = 2;
  lola->ranking[bob] = 3;

  for (const auto& person : males){ // iterate through the each person
    for (const auto& rank : person->ranking){ // iterate through the hashmap
      person->preferences.resize(10);
      person->preferences[rank.second-1] = rank.first;
    }
  }

  for (const auto person : females){
    for (const auto& rank : person->ranking){
      person->preferences.resize(10);
      person->preferences[rank.second-1] = rank.first; // (ranking : person) tuple
    }
  }  

  // expected: (alice, bob) (jane, mark)
  std::vector<std::vector<Person*>> people = {males, females};  
  return people;
}


// loop through each  person and display their result vector
void initialState(std::vector<std::vector<Person*>> people){
  int n = 3;
  for (int i = 0 ; i < 2; i++){ // for each gender
    for (int j = 0; j < n; j++){ // for each person
      Person *temp = people[i][j];
      std::cout << temp->name << "'s ranking: ";
      for (const auto& pair : temp->ranking){
	std::cout << "("<< pair.second << "," << (pair.first)->name + ") ";
      }
      std::cout << std::endl;
    }
  }
}


void printResults(std::vector<std::vector<Person*>> people){
  int n = 3;
  for (int i = 0 ; i < n; i++){
    Person *temp = people[0][i];
    std::cout << "(" << temp->name << "," << temp->preferences[temp->next-1]->name << ")";
    std::cout << std::endl;
  }
}


// input: two people.
// process: calculates if the person B (female) prefers person A (male) over their current partner
// output: the rejected person from the proposal
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


void GaleShapley() {    
  // list of free people R
  std::queue<Person *> queue;
  std::vector<std::vector<Person *>> people = initializePeople();

  std::cout << "------------------------------------" << std::endl;
  std::cout << "Initial State" << std::endl;
  initialState(people);
  
  for (Person* person : people[0]){
    queue.emplace(person);
  } // each person from A proposes to their first option, WHOM they haven't propsed to yet.

  std::cout << "------------------------------------" << std::endl;
  std::cout << "Simulation:" << std::endl;
  
  while (!queue.empty()){
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
  std::cout << "------------------------------------" << std::endl;
  std::cout << "Results:" << std::endl;

  printResults(people);
  
  for (auto& group : people){
    for (Person *p : group){
      delete p; // dealloc from heap
    }
  }
}


int main () {

  GaleShapley();
  
  return 0;
}



