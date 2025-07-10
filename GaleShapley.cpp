#include <iostream>
#include <list>
#include <string>
#include <vector>
#include <deque>

struct Person {
  std::string name;
  std::vector<Person*> ranking; // e.g. Bob: [Alice, Jane]
  int currPartner; // index of their current partner
  bool proposed;
};

// lastProposal. If i > currPartner , then their last proposal is higher ranked than the current partner
std::vector<std::vector<Person*>> initializePeople() {
  std::vector<Person*> males;
  std::vector<Person*> females;

  // dynamically create new people
  Person* bob = new Person{"Bob", {}, 1, NULL, false};
  Person* mark = new Person{"Mark", {}, 1, NULL, false};
  Person* alice = new Person{"Alice", {}, 1, NULL, false};
  Person* jane = new Person{"Jane", {}, 1, NULL, false};

  // add to lists
  males.push_back(bob);
  males.push_back(mark);
  females.push_back(alice);
  females.push_back(jane);

  // set up preference rankings
  bob->ranking[alice] = 1;
  bob->ranking[jane] = 2;
  mark->ranking[jane] = 1;
  mark->ranking[alice] = 2;

  alice->ranking[bob] = 1;
  alice->ranking[mark] = 2;
  jane->ranking[mark] = 1;
  jane->ranking[bob] = 2;

  // expected: (alice, bob) (jane, mark)

  std::vector<std::vector<Person*>> people = {males, females};  
  return people;
}



// loop through each  person and display their result vector
void printResult(std::vector<std::vector<Person*>> people){
  int n = 2;

  for (int i = 0 ; i < 2; i++){ // for each gender
    for (int j = 0; j < 2; j++){ // for each person
      Person *temp = people[i][j];
      std::cout << temp->name << "'s ranking: ";
      for (const auto& pair : temp->ranking){
	std::cout << "("<< pair.second << "," << (pair.first)->name + ") ";
      }
      std::cout << std::endl;
    }
  }

  
}

// input: two people.
// process: calculates if the person B (female) prefers person A (male) over their current partner
// output: the rejected person from the proposal
Person* propose(Person* A, Person* B){

  std::cout << A->name << " proposes to " << B->name;
  // if B is unmatched, it's an automatic yes, also if B prefers the person A
  if (B->proposed == false){ // always propose to free person
    std::cout << " and " << B->name << " accepts!" << std::endl;	
    B->proposed = true;
    A->proposed = true;
    A->currPartner = B;
    B->currPartner = A;
    return NULL; // no one was rejected
  } else if (B->ranking[A] < B->ranking[B->currPartner]){ // B prefers A to current partner
    std::cout << " and " << B->name << " accepts, replacing " << B->currPartner->name << "!" << std::endl;
    B->currPartner->proposed = false; // points to a member of A
    Person *replacedPartner = B->currPartner;
    A->proposed = true;
    B->currPartner = A;
    A->currPartner = B;
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
  printResult(people);
  
  for (Person* person : people[0]){
    queue.emplace(person);
  } // each person from A proposes to their first option, WHO they haven't propsed to it.

  while (!queue.empty()){
    Person *proposer = queue.front();
    Person *rejected = propose(proposer, proposer->ranking[proposer->lastProposal]); // returns the replaced
    proposer->lastProposal++;
    
    
  }
}



int main () {

  
  
  return 0;
}



