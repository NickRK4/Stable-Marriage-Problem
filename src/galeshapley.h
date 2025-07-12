#include <vector>
#include "person.h"

#ifndef GALE_SHAPLEY_H
#define GALE_SHAPLEY_H

// input: a vector of people
// loops through each  person and displays their preferences in order
void initialState(const std::vector<Person*> people);

// input: a vector of people
// loops through each person and displays their final partner
void printResults(const std::vector<Person*> people);

// input: two people
// output: the rejected person from the proposal
Person* propose(Person* A, Person* B);

void galeShapley(std::vector<std::vector<Person*>>);

#endif
