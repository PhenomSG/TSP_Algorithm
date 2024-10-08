#include <iostream>
#include <vector>
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



int visited[N];
int min_cost = INT_MAX;

void tsp(int curr_pos, int count, int cost, int start) {
    if (count == N && dist[curr_pos][start]) {
        min_cost = min(min_cost, cost + dist[curr_pos][start]);
        return;
    }
    
    for (int i = 0; i < N; i++) {
        if (!visited[i] && dist[curr_pos][i]) {
            visited[i] = 1;
            tsp(i, count + 1, cost + dist[curr_pos][i], start);
            visited[i] = 0;
        }
    }
}

int main() {
    for (int i = 0; i < N; i++) visited[i] = 0;
    visited[0] = 1;
    tsp(0, 1, 0, 0);
    cout << "Minimum cost: " << min_cost << endl;
    return 0;
}
