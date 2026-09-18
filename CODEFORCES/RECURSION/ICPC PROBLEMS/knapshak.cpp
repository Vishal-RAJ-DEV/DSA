#include <iostream>
using namespace std;

int knapsack(int i, int W, int weight[], int value[], int N) {
    // Base case: no items left
    if (i == N) {
        return 0;
    }

    // Don't take the current item
    int notTake = knapsack(i + 1, W, weight, value, N);

    // Take the current item if it fits
    int take = 0;

    if (weight[i] <= W) {
        take = value[i] +
               knapsack(i + 1, W - weight[i], weight, value, N);
    }

    // Choose the better option
    return max(take, notTake);
}

int main() {
    int N, W;
    cin >> N >> W;

    int weight[N], value[N];

    for (int i = 0; i < N; i++) {
        cin >> weight[i] >> value[i];
    }

    cout << knapsack(0, W, weight, value, N) << endl;

    return 0;
}