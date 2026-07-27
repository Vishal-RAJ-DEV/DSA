// ============================================================
// PROBLEM: W. Circles (Codeforces) — Determine if two circles
//          intersect (or touch).
//
// GIVEN: Two diameters (each defined by two endpoints):
//   Circle 1 diameter endpoints: (x1,y1) and (x2,y2)
//   Circle 2 diameter endpoints: (x3,y3) and (x4,y4)
//
// STEP 1 — Find the Center of Each Circle:
//   The center of a circle is the MIDPOINT of any diameter.
//   Midpoint formula:
//       Cx = (x1 + x2) / 2
//       Cy = (y1 + y2) / 2
//
// STEP 2 — Find the Radius of Each Circle:
//   The radius is half the distance between the diameter endpoints.
//   Distance between (x1,y1) and (x2,y2):
//       d = sqrt((x2 - x1)^2 + (y2 - y1)^2)
//   Radius:
//       r = d / 2
//
// STEP 3 — Check Intersection Condition:
//   Two circles intersect (or touch) if the distance between their
//   centers is ≤ the sum of their radii:
//       dist(C1, C2) ≤ r1 + r2
//
//   Distance between centers:
//       dist = sqrt((Cx1 - Cx2)^2 + (Cy1 - Cy2)^2)
//
// WHY THIS CONDITION:
//   Imagine two circles:
//     - If they are far apart (dist > r1 + r2), there is a gap → NO
//     - If they just touch (dist = r1 + r2), externally tangent → YES
//     - If one is inside the other (dist < r1 + r2, could even be 0
//       if concentric), they intersect → YES
//   The condition dist ≤ r1 + r2 covers all cases where the circles
//   share at least one point.
//
// Why sqrt / floating point?
//   Unlike Circle_Task.cpp, we CAN'T avoid sqrt here because we
//   need to compare sqrt(a) ≤ sqrt(b) + sqrt(c). Squaring both
//   sides would still leave cross-terms (2*sqrt(b*c)). So we use
//   double with sqrt(). The precision is sufficient for this check.
//
// COMPLEXITY: O(1) time, O(1) space
// ============================================================

#include <iostream>
#include <cmath>

using namespace std;

int main() {
    // Fast I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    double x1, y1, x2, y2, x3, y3, x4, y4;
    
    // Read the coordinates for both diameters
    if (cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> x4 >> y4) {
        
        // ── STEP 1: Compute centers (midpoints of diameters) ──
        double cx1 = (x1 + x2) / 2.0;          // Center of circle 1, x-coordinate
        double cy1 = (y1 + y2) / 2.0;          // Center of circle 1, y-coordinate
        double cx2 = (x3 + x4) / 2.0;          // Center of circle 2, x-coordinate
        double cy2 = (y3 + y4) / 2.0;          // Center of circle 2, y-coordinate
        
        // ── STEP 2: Compute radii (half the diameter length) ──
        double r1 = sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2)) / 2.0;   // Radius of circle 1
        double r2 = sqrt(pow(x3 - x4, 2) + pow(y3 - y4, 2)) / 2.0;   // Radius of circle 2
        
        // ── Compute distance between the two centers ──
        double dist_centers = sqrt(pow(cx1 - cx2, 2) + pow(cy1 - cy2, 2));
        
        // ── STEP 3: Check if dist(centers) ≤ r1 + r2 ──
        // Circles intersect (or touch) if this holds
        if (dist_centers <= r1 + r2) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
    }
    
    return 0;
}
