#include <string>
#include <vector>
#include <map>
#include "person.h"

#ifndef GALE_SHAPLEY_H
#define GALE_SHAPLEY_H

std::vector<std::vector<Person*>> initalizePeople();

void initialState(std::vector<Person*> people);

void printResults(std::vector<Person*> people);

Person* propose(Person* A, Person* B);

void GaleShapley(std::vector<std::vector<Person*>>);

#endif
