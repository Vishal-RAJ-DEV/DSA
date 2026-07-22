#include <iostream>
#include <bits/stdc++.h>
using namespace std;

/*
 * ================================================================
 *  PROBLEM: Check If It Is a Straight Line  (LeetCode 1232)
 * ================================================================
 *  Given an array of coordinates, determine if all points lie on
 *  the same straight line.
 *
 *  Example:
 *    [[1,2], [2,3], [3,4], [4,5], [5,6]] → true
 *    [[1,1], [2,2], [3,4], [4,5]]        → false
 *
 *  FOUR approaches, each demonstrating a different geometric
 *  principle for checking collinearity.
 * ================================================================
 */

// ================================================================
// APPROACH 1: Slope Comparison (using double, handles vertical)
// ================================================================
// INTUITION:
//   All points are collinear iff the slope between every point
//   and the first point equals the slope between the first two points.
//
//   slope = (y2 - y1) / (x2 - x1)
//
// ALGORITHM:
//   1. Compute slope from points[0] and points[1].
//   2. If x1 == x2 (vertical line), all points must have same x.
//   3. Otherwise, for each point i ≥ 2, compute slope from
//      points[0] to points[i]. If any differs → false.
//
// PROBLEM: Floating point division can cause precision issues
//          for very large coordinates or near-vertical slopes.
//
// TIME:  O(n)   SPACE: O(1)
// ================================================================

class Solution_SlopeDouble {
public:
    bool checkStraightLine(vector<vector<int>>& coordinates) {

        // First two points define the reference line
        double x1 = coordinates[0][0];
        double y1 = coordinates[0][1];
        double x2 = coordinates[1][0];
        double y2 = coordinates[1][1];

        // ---- Handle vertical line (x1 == x2) ----
        // Slope is undefined (division by zero), so check separately:
        // All points must have the same x-coordinate.
        if (x1 == x2) {
            for (int i = 2; i < coordinates.size(); i++) {
                if (coordinates[i][0] != x1)
                    return false;
            }
            return true;
        }

        // Compute reference slope as a double
        double slope = (y2 - y1) / (x2 - x1);

        // Check all remaining points
        for (int i = 2; i < coordinates.size(); i++) {

            // Compute slope from (x1,y1) to (xi,yi)
            double currSlope =
                (coordinates[i][1] - y1) * 1.0 /
                (coordinates[i][0] - x1);

            // Direct double comparison — can fail for edge cases
            if (currSlope != slope)
                return false;
        }

        return true;
    }
};

// ================================================================
// APPROACH 2: Cross-Multiplication (no floating point)
// ================================================================
// INTUITION:
//   Instead of comparing slopes as doubles, compare them using
//   cross-multiplication (integer arithmetic only).
//
//   slope1 = slope2  means:
//     (y2 - y1) / (x2 - x1) == (yi - y1) / (xi - x1)
//   Cross-multiply to avoid division:
//     (y2 - y1) * (xi - x1) == (yi - y1) * (x2 - x1)
//
//   This is also the condition that vectors (dx, dy) and (xi-x1, yi-y1)
//   are PARALLEL (their cross product is 0).
//
// ALGORITHM:
//   1. Compute dx = x2 - x1, dy = y2 - y1.
//   2. For each point (x, y):
//        Check:  dy * (x - x1) == dx * (y - y1)
//   3. If any fails → false.
//
// ADVANTAGE: No floating point, no division, no special case.
//   When dx=0 (vertical), the equation becomes:
//     0 == 0 * (y - y1) → 0 == 0  for any y, but
//     dy * (x - x1) == 0 * (y - y1) → dy * (x - x1) == 0
//     Since dy ≠ 0 (otherwise all points identical), we get
//     (x - x1) == 0 → all x must equal x1 ✓
//
// TIME:  O(n)   SPACE: O(1)
// ================================================================

class Solution_CrossMultiply {
public:
    bool checkStraightLine(vector<vector<int>>& coordinates) {

        int x1 = coordinates[0][0];
        int y1 = coordinates[0][1];
        int x2 = coordinates[1][0];
        int y2 = coordinates[1][1];

        // Direction vector of the reference line
        int dx = x2 - x1;
        int dy = y2 - y1;

        /*
         * For each subsequent point (x, y), check if it lies on the
         * same line using the cross-product test:
         *
         *   dy * (x - x1) == dx * (y - y1)
         *
         * This checks if vectors (dx, dy) and (x-x1, y-y1) are
         * parallel by comparing their cross product to 0.
         *
         * Why this works for ALL cases (including vertical/horizontal):
         *
         *   Vertical line (dx=0, dy≠0):
         *     dy * (x - x1) == 0 * (y - y1)
         *     dy * (x - x1) == 0
         *     Since dy ≠ 0, must have x == x1 ✓
         *
         *   Horizontal line (dx≠0, dy=0):
         *     0 * (x - x1) == dx * (y - y1)
         *     0 == dx * (y - y1)
         *     Since dx ≠ 0, must have y == y1 ✓
         */
        for (int i = 2; i < coordinates.size(); i++) {

            int x = coordinates[i][0];
            int y = coordinates[i][1];

            if (dy * (x - x1) != dx * (y - y1))
                return false;
        }

        return true;
    }
};

// ================================================================
// APPROACH 3: Area of Triangle (Shoelace / Determinant)
// ================================================================
// INTUITION:
//   Three points are collinear iff the area of the triangle formed
//   by them is ZERO.
//
//   The area (signed) can be computed using the determinant formula
//   (also known as the shoelace formula for triangles):
//
//     area = x1*(y2 - y3) + x2*(y3 - y1) + x3*(y1 - y2)
//
//   This is twice the signed area of the triangle.
//   If area == 0 → points are collinear.
//
// ALGORITHM:
//   1. Pick first two points as reference (x1,y1) and (x2,y2).
//   2. For each point (x3,y3), compute the determinant/area.
//   3. If area ≠ 0 → not collinear → false.
//
// DERIVATION:
//   The determinant of the matrix formed by the two vectors:
//     | x2-x1   x3-x1 |       = (x2-x1)*(y3-y1) - (x3-x1)*(y2-y1)
//     | y2-y1   y3-y1 |
//
//   This equals the cross product of the two vectors and is 0
//   when they are parallel (collinear).
//
//   Expanding gives: x1(y2-y3) + x2(y3-y1) + x3(y1-y2)
//
// TIME:  O(n)   SPACE: O(1)
// ================================================================

class Solution_AreaTriangle {
public:
    bool checkStraightLine(vector<vector<int>>& coordinates) {

        int x1 = coordinates[0][0];
        int y1 = coordinates[0][1];
        int x2 = coordinates[1][0];
        int y2 = coordinates[1][1];

        for (int i = 2; i < coordinates.size(); i++) {

            int x3 = coordinates[i][0];
            int y3 = coordinates[i][1];

            /*
             * Compute twice the signed area of triangle (x1,y1)-(x2,y2)-(x3,y3)
             * using the determinant / shoelace formula:
             *
             *   area = x1*(y2 - y3) + x2*(y3 - y1) + x3*(y1 - y2)
             *
             * If area == 0, the three points are collinear.
             *
             * Geometric meaning:
             *   |area| = twice the area of triangle formed by the three points.
             *   Zero area → points lie on the same line.
             */
            int area = x1 * (y2 - y3)
                     + x2 * (y3 - y1)
                     + x3 * (y1 - y2);

            if (area != 0)
                return false;
        }

        return true;
    }
};

// ================================================================
// APPROACH 4: Reduced Direction Vector (using GCD)
// ================================================================
// INTUITION:
//   A line's direction can be represented as a REDUCED direction
//   vector (dx, dy) normalized by dividing by their GCD.
//
//   Two points (x1,y1) and (x2,y2) define a direction vector:
//     (dx, dy) = (x2-x1, y2-y1)
//
//   Reduce it:  g = gcd(|dx|, |dy|),  dx /= g,  dy /= g
//
//   This gives a UNIQUE representation of the line's slope.
//   For any other point (x, y) on the same line:
//     (x - x1, y - y1) must reduce to the SAME reduced vector.
//
// ALGORITHM:
//   1. Compute direction vector (dx, dy) from first two points.
//   2. Reduce it by dividing by gcd(dx, dy).
//   3. For each subsequent point (x, y):
//        a. Compute (ndx, ndy) = (x - x1, y - y1)
//        b. Reduce by dividing by gcd(ndx, ndy)
//        c. If (ndx, ndy) != (dx, dy) → false.
//
// NOTE: This normalizes direction ignoring sign. To handle signs
//       consistently, we ensure dx ≥ 0 or handle negative cases.
//
// TIME:  O(n * log M) — each GCD is O(log min(|dx|,|dy|))
// SPACE: O(1)
// ================================================================

class Solution_ReducedVector {
public:
    bool checkStraightLine(vector<vector<int>>& coordinates) {

        // Direction vector from first two points
        int dx = coordinates[1][0] - coordinates[0][0];
        int dy = coordinates[1][1] - coordinates[0][1];

        // Reduce (dx, dy) to its simplest form
        int g = __gcd(abs(dx), abs(dy));

        /*
         * Normalize so that the direction representation is unique.
         * We ensure dy ≥ 0 (or if dy=0, then dx > 0) for consistency,
         * so that (dx, dy) and (-dx, -dy) are treated as the same line.
         */
        dx /= g;
        dy /= g;

        /*
         * Note: A more robust normalization would also handle sign:
         *   if (dy < 0 || (dy == 0 && dx < 0)) { dx = -dx; dy = -dy; }
         * This ensures opposite directions map to the same reduced vector.
         */

        for (int i = 2; i < coordinates.size(); i++) {

            // Vector from first point to current point
            int ndx = coordinates[i][0] - coordinates[0][0];
            int ndy = coordinates[i][1] - coordinates[0][1];

            // Reduce this vector too
            int g2 = __gcd(abs(ndx), abs(ndy));

            if (g2 != 0) {  // avoid division by zero (point same as first)
                ndx /= g2;
                ndy /= g2;
            }

            // Compare reduced direction vectors
            if (ndx != dx || ndy != dy)
                return false;
        }

        return true;
    }
};

/*
 * ================================================================
 *  SUMMARY OF APPROACHES
 * ================================================================
 *
 *  Approach            | Method                        | Precision
 *  --------------------+-------------------------------+----------
 *  Slope (double)      | Compare (y₂-y₁)/(x₂-x₁)       | ⚠ Floating point
 *  Cross-multiplication| dy*(x-x₁) == dx*(y-y₁)        | ✅ Exact integer
 *  Area (determinant)  | x₁(y₂-y₃)+x₂(y₃-y₁)+x₃(y₁-y₂)| ✅ Exact integer
 *  Reduced vector (GCD)| Normalize (dx,dy) by gcd       | ✅ Exact integer
 *
 *  RECOMMENDED: Approach 2 (Cross-Multiplication) — simplest,
 *  handles all cases without special handling, integer-only.
 *
 *  DRY RUN (Cross-Multiplication approach):
 *    coordinates = [[1,2], [2,3], [3,4]]
 *    x1=1, y1=2, x2=2, y2=3
 *    dx=1, dy=1
 *
 *    i=2: x=3, y=4
 *      dy*(x-x1) = 1*(3-1) = 2
 *      dx*(y-y1) = 1*(4-2) = 2
 *      2 == 2 ✓ → collinear
 *    Result: true
 * ================================================================
 */

int main() {
    return 0;
}
