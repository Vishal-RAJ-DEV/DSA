#include <iostream>

using namespace std;

int main() {
    // Fast I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    long long L, R, M;
    
    // Read L, R, and M
    cin >> L >> R >> M;
    
    long long product = 1;
    
    // Loop from L to R (inclusive)
    for (long long i = L; i <= R; ++i) {
        // Multiply and take modulo M at each step to prevent overflow
        product = (product * (i % M)) % M;
    }
    
    // Print the final product modulo M
    cout << product << "\n";
    
    return 0;
}