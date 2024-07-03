#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>

using namespace std;

const int N = 7; // Number of cities
int dist[N][N] = {
    {0, 10, 15, 20, 25, 30, 35},
    {10, 0, 35, 25, 30, 15, 20},
    {15, 35, 0, 30, 20, 25, 10},
    {20, 25, 30, 0, 10, 5, 15},
    {25, 30, 20, 10, 0, 15, 25},
    {30, 15, 25, 5, 15, 0, 20},
    {35, 20, 10, 15, 25, 20, 0}
};




int reduceMatrix(int costMatrix[N][N], int rowReduction[N], int colReduction[N]) {
    int cost = 0;

    for (int i = 0; i < N; i++) {
        rowReduction[i] = *min_element(costMatrix[i], costMatrix[i] + N);
        cost += rowReduction[i];
        for (int j = 0; j < N; j++) {
            if (costMatrix[i][j] != INT_MAX && rowReduction[i] != INT_MAX) {
                costMatrix[i][j] -= rowReduction[i];
            }
        }
    }

    for (int j = 0; j < N; j++) {
        int colMin = INT_MAX;
        for (int i = 0; i < N; i++) {
            if (costMatrix[i][j] < colMin) {
                colMin = costMatrix[i][j];
            }
        }
        colReduction[j] = colMin;
        cost += colReduction[j];
        for (int i = 0; i < N; i++) {
            if (costMatrix[i][j] != INT_MAX && colReduction[j] != INT_MAX) {
                costMatrix[i][j] -= colReduction[j];
            }
        }
    }

    return cost;
}

int branchAndBoundTSP(int costMatrix[N][N], int currBound, int currWeight, int level, vector<int>& currPath, vector<int>& bestPath, int& minCost) {
    if (level == N) {
        if (dist[currPath[level - 1]][currPath[0]] != 0) {
            int currResult = currWeight + dist[currPath[level - 1]][currPath[0]];
            if (currResult < minCost) {
                minCost = currResult;
                bestPath = currPath;
                bestPath.push_back(currPath[0]);
            }
        }
        return minCost;
    }

    for (int i = 0; i < N; i++) {
        if (find(currPath.begin(), currPath.end(), i) == currPath.end() && dist[currPath[level - 1]][i] != 0) {
            int temp = currBound;
            currWeight += dist[currPath[level - 1]][i];

            int rowReduction[N], colReduction[N];
            int reducedCostMatrix[N][N];
            copy(&costMatrix[0][0], &costMatrix[0][0] + N * N, &reducedCostMatrix[0][0]);

            int cost = reduceMatrix(reducedCostMatrix, rowReduction, colReduction);
            currBound = temp + cost;
            
            if (currBound + currWeight < minCost) {
                currPath[level] = i;
                minCost = branchAndBoundTSP(reducedCostMatrix, currBound, currWeight, level + 1, currPath, bestPath, minCost);
            }

            currWeight -= dist[currPath[level - 1]][i];
            currBound = temp;
        }
    }
    return minCost;
}

int solveTSP(int costMatrix[N][N]) {
    vector<int> currPath(N + 1, -1);
    vector<int> bestPath(N + 1, -1);
    int currBound = 0;
    int rowReduction[N], colReduction[N];
    currBound = reduceMatrix(costMatrix, rowReduction, colReduction);
    currPath[0] = 0;

    int minCost = INT_MAX;
    return branchAndBoundTSP(costMatrix, currBound, 0, 1, currPath, bestPath, minCost);
}

int main() {
    int costMatrix[N][N] = {
        {0, 10, 15, 20},
        {10, 0, 35, 25},
        {15, 35, 0, 30},
        {20, 25, 30, 0}
    };
    cout << "Minimum cost: " << solveTSP(costMatrix) << endl;
    return 0;
}
