# Gale-Shapley Algorithm Implementation

I implemented the Gale-Shapley algorithm in C++ to practice basic C++ syntax and data structures. The algorithm finds a stable matching between two equally-sized sets of people. I hard coded the people to size 10, but I'm interested how this performs with larger inputs.

## Algorithm Overview

Given n men and n women, where each person has ranked all members of the opposite gender with a unique number between 1 and n in order of preference, the algorithm finds a stable matching of men and women such that there are no two people of opposite gender who would both rather be matched with each other than their current partners. [Gale-Shapley Algorithm](https://en.wikipedia.org/wiki/Gale%E2%80%93Shapley_algorithm)

## Project Structure

```
├── src/
│   ├── galeshapley.cpp  - Implementation of the core algorithm
│   ├── galeshapley.h    - Header declarations for the algorithm
│   ├── person.h         - Person structure definition
│   ├── test.cpp         - Test implementation and main function
│   └── test.h           - Test function declarations
└── README.md            - This file
```

## How to Compile and Run

```bash
# Navigate to the project directory
cd GaleShapley

# Compile the project
make

# Run the executable
./gale_shapley
```

## Example Output

Program will show:
1. Initial state with all people's randomized preferences
2. Step-by-step simulation of the algorithm
3. Final pairs

## Algorithm Complexity

- Time Complexity: O(n²) where n is the number of people in each group
- Space Complexity: O(n²)

## References

- Gale, D., & Shapley, L. S. (1962). College Admissions and the Stability of Marriage. The American Mathematical Monthly, 69(1), 9-15.
