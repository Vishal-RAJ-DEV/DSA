// ============================================================
// PROBLEM: Check if three points are collinear (lie on one straight line)
//
// LOGIC — Slope Comparison (without floating-point division):
//
//   Three points A(x1,y1), B(x2,y2), C(x3,y3) are collinear
//   if the slope between A-B equals the slope between B-C.
//
//   Slope of AB = (y2 - y1) / (x2 - x1)
//   Slope of BC = (y3 - y2) / (x3 - x2)
//
//   Since division introduces floating-point errors and is slower,
//   we CROSS-MULTIPLY to compare slopes with integers only:
//
//       (y2 - y1)   (y3 - y2)
//       --------- = ---------    ⇔    (y2 - y1)*(x3 - x2) = (y3 - y2)*(x2 - x1)
//       (x2 - x1)   (x3 - x2)
//
//   Cross-multiplication avoids division entirely. Both sides are
//   integer products, so we just compare them with ==.
//
// WHY THIS WORKS:
//   The equation (y2 - y1)*(x3 - x2) == (y3 - y2)*(x2 - x1) is
//   algebraically equivalent to the determinant being zero:
//
//     | x1 y1 1 |
//     | x2 y2 1 |  =  0  ⇔  area of triangle ABC = 0
//     | x3 y3 1 |
//
//   When the area of the triangle formed by the three points is
//   zero, the points are collinear.
//
// EDGE CASE — Vertical Lines:
//   If x2 - x1 = 0 (vertical), the slope formula would divide by
//   zero. But cross-multiplication handles this naturally because
//   we never divide — the equation still holds correctly.
//
// COMPLEXITY: O(1) time, O(1) space
// ============================================================

#include <iostream>

using namespace std;

int main() {
    // Fast I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    long long x1, y1, x2, y2, x3, y3;
    
    // Read the three points
    if (cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3) {
        
        // left_side  = (y2 - y1) * (x3 - x2)   → slope AB × Δx of BC
        // right_side = (y3 - y2) * (x2 - x1)   → slope BC × Δx of AB
        // If slopes are equal, the cross products are equal
        long long left_side = (y2 - y1) * (x3 - x2);
        long long right_side = (y3 - y2) * (x2 - x1);
        
        // If they are equal, the points are collinear
        if (left_side == right_side) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
    }
    
    return 0;
}
