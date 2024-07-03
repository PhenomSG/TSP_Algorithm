#include <iostream>
#include <vector>
#include <climits>

using namespace std;

const int INF = INT_MAX;
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



int dp[1 << N][N];

int tsp(int mask, int pos) {
    if (mask == ((1 << N) - 1)) {
        return dist[pos][0];
    }
    if (dp[mask][pos] != -1) {
        return dp[mask][pos];
    }

    int ans = INF;
    for (int city = 0; city < N; city++) {
        if ((mask & (1 << city)) == 0) {
            int newAns = dist[pos][city] + tsp(mask | (1 << city), city);
            ans = min(ans, newAns);
        }
    }
    return dp[mask][pos] = ans;
}

int main() {
    for (int i = 0; i < (1 << N); i++) {
        for (int j = 0; j < N; j++) {
            dp[i][j] = -1;
        }
    }
    cout << "Minimum cost: " << tsp(1, 0) << endl;
    return 0;
}
