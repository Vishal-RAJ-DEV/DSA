#include <iostream>
using namespace std;

int ways_using_loop(int current, int E) {
    if (current == E)
        return 1;

    if (current > E)
        return 0;

    int ans = 0;

    for (int step = 1; step <= 3; step++) {
        ans += ways_using_loop(current + step, E);
    }

    return ans;
}

int ways(int current, int E) {
    // Reached the destination
    if (current == E)
        return 1;

    // Crossed the destination
    if (current > E)
        return 0;

    return ways(current + 1, E)
         + ways(current + 2, E)
         + ways(current + 3, E);
}

int main() {
    int S, E;
    cin >> S >> E;

    cout << ways(S, E) << endl;

    return 0;
}