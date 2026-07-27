#include <iostream>

using namespace std;

int main() {
    // Fast I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    long long x1, y1, x2, y2;
    long long x3, y3, x4, y4;
    
    // Read the coordinates for both lines
    if (cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> x4 >> y4) {
        
        // Calculate differences
        long long dy1 = y2 - y1;
        long long dx1 = x2 - x1;
        long long dy2 = y4 - y3;
        long long dx2 = x4 - x3;
        
        // Cross multiply to compare slopes
        if (dy1 * dx2 == dy2 * dx1) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
    }
    
    return 0;
}