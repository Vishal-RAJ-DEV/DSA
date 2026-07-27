#include <iostream>
#include <algorithm>

using namespace std;

void solve(int case_num) {
    int n;
    cin >> n;
    
    // Initialize boundaries to extreme values
    long long max_x1 = -100000, max_y1 = -100000;
    long long min_x2 = 100000, min_y2 = 100000;
    
    for (int i = 0; i < n; ++i) {
        long long x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        
        // Update the tightest boundaries
        max_x1 = max(max_x1, x1);
        max_y1 = max(max_y1, y1);
        min_x2 = min(min_x2, x2);
        min_y2 = min(min_y2, y2);
    }
    
    long long area = 0;
    // Calculate area if it's a valid intersection
    if (max_x1 < min_x2 && max_y1 < min_y2) {
        area = (min_x2 - max_x1) * (min_y2 - max_y1);
    }
    
    cout << "Case #" << case_num << ": " << area << "\n";
}

int main() {
    // Fast I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    if (cin >> t) {
        for (int i = 1; i <= t; ++i) {
            solve(i);
        }
    }
    return 0;
}