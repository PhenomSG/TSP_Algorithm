# Travelling Salesman Problem (TSP)

## Problem Statement
The Travelling Salesman Problem (TSP) is a classic optimization problem in which a salesman is required to visit a set of cities exactly once, returning to the starting city, while minimizing the total travel distance or cost. The objective is to find the shortest possible route that visits each city once and returns to the origin city.

## Challenges Faced
1. **Computational Complexity:** TSP is an NP-hard problem, meaning that the time required to solve it increases exponentially with the number of cities.
2. **Optimality vs. Efficiency:** Finding the absolute optimal solution can be computationally infeasible for large datasets. There is often a trade-off between finding an exact solution and an approximate one in a reasonable amount of time.
3. **Dynamic Constraints:** Real-world applications of TSP may include dynamic constraints such as traffic conditions, time windows, or varying travel costs.
4. **Scalability:** The solution methods need to scale effectively as the number of cities increases.
5. **Memory Usage:** Some algorithms require significant memory, which can be a limiting factor for large instances.

## Solution Approaches
We explore several methods to solve the TSP, each with its own advantages and trade-offs:

### 1. Dynamic Programming
Dynamic Programming (DP) breaks the problem into smaller subproblems and stores the results of these subproblems to avoid redundant computations. One well-known DP approach is the Held-Karp algorithm, which has a time complexity of O(n^2 * 2^n).

### 2. Minimum Spanning Tree (MST)
Using MST, we can approximate the TSP by finding a minimum spanning tree of the graph and performing a depth-first traversal to generate a Hamiltonian cycle. This approach provides a 2-approximation solution but is not guaranteed to be optimal.

### 3. Backtracking
Backtracking systematically explores all possible permutations of cities to find the optimal tour. While straightforward, this method has a factorial time complexity (O(n!)) and is impractical for large numbers of cities.

### 4. Hungarian Method
The Hungarian Method solves the assignment problem and can be adapted for TSP by converting it into an assignment problem. This method works well for smaller instances but is not directly applicable to TSP without modifications.

### 5. Reduced Matrix Method
This method involves reducing the cost matrix and iteratively refining it to find the optimal tour. It is an exact method but can be computationally intensive for larger instances.

### 6. Bitmasking and Dynamic Programming
Combining bitmasking with DP allows us to represent the state of visited cities efficiently. This method is particularly effective for small to medium-sized instances, with a time complexity of O(n^2 * 2^n).

### 7. Branch and Bound
Branch and Bound systematically explores branches of the search space, using bounds to prune branches that cannot yield better solutions than the current best. It can find exact solutions more efficiently than simple backtracking but still suffers from exponential time complexity in the worst case.

## Benchmarking
We benchmark the performance of each approach using various datasets to evaluate their efficiency and accuracy. The criteria include:
- **Execution Time:** The time taken to find a solution.
- **Memory Usage:** The amount of memory consumed during computation.
- **Solution Quality:** The optimality of the solution found (distance or cost).

### Results
After extensive benchmarking, the best-performing methods in terms of execution time and solution quality are:

1. **Bitmasking and Dynamic Programming:** Provides an optimal solution for small to medium-sized instances efficiently.
2. **Branch and Bound:** Offers an exact solution with reasonable efficiency for medium-sized instances.
3. **Minimum Spanning Tree (MST):** Delivers a good approximation quickly for large instances where exact solutions are impractical.

## Conclusion
The choice of method depends on the specific requirements of the problem instance, including the size of the city set and the acceptable trade-off between optimality and computational resources. For exact solutions, Bitmasking and Dynamic Programming and Branch and Bound are recommended for smaller instances, while MST offers a practical approximation for larger instances.

## Usage
To run the algorithms, follow these steps:
1. Clone the repository: `git clone https://github.com/yourusername/tsp-solutions.git`
2. Navigate to the project directory: `cd tsp-solutions`
3. Follow the instructions in the `setup.md` file to set up the environment.
4. Run the desired algorithm using the provided scripts in the `scripts` directory.

## License
This project is licensed under the MIT License - see the [LICENSE](LICENSE.md) file for details.
