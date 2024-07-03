#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <algorithm>

using namespace std;

const int N = 4;
int dist[N][N] = {
    {0, 10, 15, 20},
    {10, 0, 35, 25},
    {15, 35, 0, 30},
    {20, 25, 30, 0}
};

struct Node {
    vector<int> path;
    int reducedMatrix[N][N];
    int cost;
    int vertex;
    int level;
};

int calculateCost(int reducedMatrix[N][N]) {
    int cost = 0;
    for (int i = 0; i < N; i++) {
        int rowMin = INT_MAX;
        for (int j = 0; j < N; j++) {
            if (reducedMatrix[i][j] < rowMin) {
                rowMin = reducedMatrix[i][j];
            }
        }
        if (rowMin != INT_MAX) {
            cost += rowMin;
            for (int j = 0; j < N; j++) {
                if (reducedMatrix[i][j] != INT_MAX) {
                    reducedMatrix[i][j] -= rowMin;
                }
            }
        }
    }

    for (int j = 0; j < N; j++) {
        int colMin = INT_MAX;
        for (int i = 0; i < N; i++) {
            if (reducedMatrix[i][j] < colMin) {
                colMin = reducedMatrix[i][j];
            }
        }
        if (colMin != INT_MAX) {
            cost += colMin;
            for (int i = 0; i < N; i++) {
                if (reducedMatrix[i][j] != INT_MAX) {
                    reducedMatrix[i][j] -= colMin;
                }
            }
        }
    }

    return cost;
}

void copyMatrix(int src[N][N], int dest[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            dest[i][j] = src[i][j];
        }
    }
}

struct compare {
    bool operator()(const Node* lhs, const Node* rhs) const {
        return lhs->cost > rhs->cost;
    }
};

int tsp() {
    priority_queue<Node*, vector<Node*>, compare> pq;

    vector<int> path;
    path.push_back(0);

    Node* root = new Node;
    root->path = path;
    root->vertex = 0;
    root->level = 0;
    copyMatrix(dist, root->reducedMatrix);

    root->cost = calculateCost(root->reducedMatrix);
    pq.push(root);

    while (!pq.empty()) {
        Node* min = pq.top();
        pq.pop();

        if (min->level == N - 1) {
            min->path.push_back(0);
            return min->cost;
        }

        for (int i = 0; i < N; i++) {
            if (find(min->path.begin(), min->path.end(), i) == min->path.end()) {
                Node* child = new Node;
                child->path = min->path;
                child->path.push_back(i);
                child->level = min->level + 1;
                child->vertex = i;

                copyMatrix(min->reducedMatrix, child->reducedMatrix);
                for (int j = 0; j < N; j++) {
                    child->reducedMatrix[min->vertex][j] = INT_MAX;
                    child->reducedMatrix[j][i] = INT_MAX;
                }
                child->reducedMatrix[i][0] = INT_MAX;

                child->cost = min->cost + dist[min->vertex][i] + calculateCost(child->reducedMatrix);
                pq.push(child);
            }
        }
    }
    return INT_MAX;
}

int main() {
    cout << "Minimum cost: " << tsp() << endl;
    return 0;
}
