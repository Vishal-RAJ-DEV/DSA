#include <iostream>
#include <algorithm>

using namespace std;

int main() {
    // Fast I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int x1, y1, x2, y2, x3, y3, x4, y4;
    
    // Read the four points of the rectangle
    if (cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> x4 >> y4) {
        
        // Find the boundary limits of the rectangle
        int x_min = min({x1, x2, x3, x4});
        int x_max = max({x1, x2, x3, x4});
        int y_min = min({y1, y2, y3, y4});
        int y_max = max({y1, y2, y3, y4});
        
        int n;
        cin >> n;
        
        // Check each point
        for (int i = 0; i < n; ++i) {
            int px, py;
            cin >> px >> py;
            
            if (px >= x_min && px <= x_max && py >= y_min && py <= y_max) {
                cout << "YES\n";
            } else {
                cout << "NO\n";
            }
        }
    }
    
    return 0;
}