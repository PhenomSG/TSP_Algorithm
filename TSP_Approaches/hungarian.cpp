#include <iostream>
#include <vector>
#include <climits>

using namespace std;

const int N = 4;
const int INF = INT_MAX;

int dist[N][N] = {
    {0, 10, 15, 20},
    {10, 0, 35, 25},
    {15, 35, 0, 30},
    {20, 25, 30, 0}
};

int hungarian() {
    vector<int> u(N, 0), v(N, INF), p(N), way(N);

    for (int i = 1; i < N; ++i) {
        p[0] = i;
        int j0 = 0;
        vector<int> minv(N, INF);
        vector<bool> used(N, false);

        do {
            used[j0] = true;
            int i0 = p[j0], delta = INF, j1;

            for (int j = 1; j < N; ++j) {
                if (!used[j]) {
                    int cur = dist[i0][j] - u[i0] - v[j];
                    if (cur < minv[j]) {
                        minv[j] = cur;
                        way[j] = j0;
                    }
                    if (minv[j] < delta) {
                        delta = minv[j];
                        j1 = j;
                    }
                }
            }

            for (int j = 0; j < N; ++j) {
                if (used[j]) {
                    u[p[j]] += delta;
                    v[j] -= delta;
                } else {
                    minv[j] -= delta;
                }
            }
            j0 = j1;
        } while (p[j0] != 0);

        do {
            int j1 = way[j0];
            p[j0] = p[j1];
            j0 = j1;
        } while (j0);
    }

    return -v[0]; // Return the minimum cost found
}

int main() {
    cout << "Minimum cost: " << hungarian() << endl;
    return 0;
}
