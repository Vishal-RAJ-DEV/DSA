// ============================================================
// PROBLEM: For each query point, determine if it lies inside
//          (or on) a given circle.
//
// LOGIC — Distance-squared Comparison:
//
//   A point (x,y) lies inside a circle with center (X,Y) and
//   radius R if its distance from the center ≤ R.
//
//   Euclidean distance formula:
//       distance = sqrt((x - X)^2 + (y - Y)^2)
//
//   To avoid expensive floating-point sqrt, we compare
//   SQUARED distances instead:
//
//       (x - X)^2 + (y - Y)^2  ≤  R^2
//
//   Since both sides are non-negative, squaring preserves the
//   inequality (squaring is monotonic for non-negative numbers).
//
//   Precomputing R_squared = R * R avoids recomputing it for
//   every query point.
//
// WHY AVOID sqrt():
//   sqrt() is a slow floating-point operation. Comparing squared
//   distances uses only integer arithmetic (long long), which is
//   faster and exact. No precision loss.
//
// COMPLEXITY: O(N) time for N queries, O(1) space per query
// ============================================================

#include <iostream>

using namespace std;

int main() {
    // Fast I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    long long X, Y, R;
    int N;
    
    // Read center coordinates, radius, and number of points
    if (cin >> X >> Y >> R >> N) {
        // Precompute R² to avoid recomputing for every query
        long long R_squared = R * R;
        
        for (int i = 0; i < N; ++i) {
            long long x, y;
            cin >> x >> y;
            
            // Compute squared Euclidean distance from (x,y) to center (X,Y)
            long long dx = x - X;
            long long dy = y - Y;
            long long distance_squared = (dx * dx) + (dy * dy);
            
            // If distance² ≤ R², the point lies inside or on the circle
            if (distance_squared <= R_squared) {
                cout << "YES\n";
            } else {
                cout << "NO\n";
            }
        }
    }
    
    return 0;
}
