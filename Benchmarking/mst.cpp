#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

const int N = 8; // Number of cities
int dist[N][N] = {
    {0, 10, 15, 20, 25, 30, 35, 40},
    {10, 0, 35, 25, 30, 15, 20, 25},
    {15, 35, 0, 30, 20, 25, 10, 5},
    {20, 25, 30, 0, 10, 5, 15, 20},
    {25, 30, 20, 10, 0, 15, 25, 30},
    {30, 15, 25, 5, 15, 0, 20, 25},
    {35, 20, 10, 15, 25, 20, 0, 10},
    {40, 25, 5, 20, 30, 25, 10, 0}
};


int primMST() {
    vector<int> key(N, INT_MAX);
    vector<bool> mstSet(N, false);
    key[0] = 0;

    for (int count = 0; count < N - 1; count++) {
        int u = -1;
        for (int i = 0; i < N; i++) {
            if (!mstSet[i] && (u == -1 || key[i] < key[u])) {
                u = i;
            }
        }

        mstSet[u] = true;

        for (int v = 0; v < N; v++) {
            if (dist[u][v] && !mstSet[v] && dist[u][v] < key[v]) {
                key[v] = dist[u][v];
            }
        }
    }

    int mstWeight = 0;
    for (int i = 1; i < N; i++) {
        mstWeight += key[i];
    }
    return mstWeight;
}

int main() {
    cout << "Minimum cost: " << 2 * primMST() << endl;
    return 0;
}
