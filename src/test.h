#include "person.h"

#ifndef TEST_H
#define TEST_H

// input: none
// process: dynamically creates a people structs, then puts them into an array
// and returns a 2D array where arr[0] = proposers and arr[1] = proposees
// output: a 2D array where arr[0] = proposers and arr[1] = proposees
std::vector<std::vector<Person*>> initalizePeople();

// input: two arrays, p and q
// process: for each person in p, it will assign n random rankings of people in q
// output: none
void assignRanking(std::vector<Person*> males, std::vector<Person*> females);

#endif
