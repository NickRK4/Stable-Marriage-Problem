#include <string>
#include <vector>
#include <unordered_map>

#ifndef PERSON_H
#define PERSON_H

// defines the Person structure
// each person has a name, array of preferences, ordered by ranking, a hashmap for O(1) people comparisons.
// next defines the next proposee that the proposer will propose to
// currentPartner simplifies the comparisons, but isn't necessary
struct Person {
  std::string name;
  std::vector<Person*> preferences;
  std::unordered_map<Person *, int> ranking;
  int next;
  Person* currentPartner;
};

#endif
