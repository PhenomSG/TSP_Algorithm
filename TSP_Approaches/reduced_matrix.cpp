#include <iostream>
#include <vector>
#include <climits>

using namespace std;

const int N = 4;

int dist[N][N] = {
    {0, 10, 15, 20},
    {10, 0, 35, 25},
    {15, 35, 0, 30},
    {20, 25, 30, 0}
};

int reduceMatrix(int costMatrix[N][N]) {
    int cost = 0;

    for (int i = 0; i < N; i++) {
        int rowMin = INT_MAX;
        for (int j = 0; j < N; j++) {
            if (costMatrix[i][j] < rowMin) {
                rowMin = costMatrix[i][j];
            }
        }
        if (rowMin != INT_MAX) {
            cost += rowMin;
            for (int j = 0; j < N; j++) {
                if (costMatrix[i][j] != INT_MAX) {
                    costMatrix[i][j] -= rowMin;
                }
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
        if (colMin != INT_MAX) {
            cost += colMin;
            for (int i = 0; i < N; i++) {
                if (costMatrix[i][j] != INT_MAX) {
                    costMatrix[i][j] -= colMin;
                }
            }
        }
    }

    return cost;
}

int solveTSP(int costMatrix[N][N]) {
    int minCost = INT_MAX;

    vector<int> path;
    path.push_back(0);

    vector<vector<int>> reducedMatrix(N, vector<int>(N));

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            reducedMatrix[i][j] = costMatrix[i][j];
        }
    }

    minCost = reduceMatrix(reducedMatrix);

    for (int i = 1; i < N; i++) {
        if (find(path.begin(), path.end(), i) == path.end()) {
            path.push_back(i);
            int currentCost = costMatrix[path.back()][i] + solveTSP(costMatrix);
            minCost = min(minCost, currentCost);
            path.pop_back();
        }
    }

    return minCost;
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
