// ============================================================
// PROBLEM: Given a circle (radius R) and a square (side S),
//          determine which shape can fully contain the other,
//          or if neither can (complex intersection).
//
// GEOMETRIC CONDITIONS:
//
// CASE 1 — Circle inside Square ("Square"):
//   The circle fits inside the square if its DIAMETER ≤ the
//   square's SIDE:
//       2R ≤ S
//   The entire circle lies within the square when the square's
//   side is at least as wide as the circle's diameter.
//
// CASE 2 — Square inside Circle ("Circle"):
//   The square fits inside the circle if its DIAGONAL ≤ the
//   circle's DIAMETER:
//       S√2 ≤ 2R
//   Square both sides (both are positive, squaring preserves order):
//       2S² ≤ 4R²   →   S² ≤ 2R²
//   Why? The furthest points of a square from its center are its
//   corners, at distance = half the diagonal = S√2 / 2.
//   This must be ≤ R (the circle's radius), giving S√2 / 2 ≤ R,
//   which simplifies to the same condition: S² ≤ 2R².
//
// CASE 3 — Neither fits fully ("Complex"):
//   If 2R > S (circle too wide for square) AND S² > 2R² (square
//   too wide for circle), then the shapes partially intersect —
//   neither can completely contain the other.
//
// ORDER OF CHECKS MATTERS:
//   We check Circle-in-Square FIRST (2R ≤ S).
//   Then Square-in-Circle (S² ≤ 2R²).
//   If neither holds → Complex.
//   This order is arbitrary but must be consistent.
//
// WHY long long?
//   R and S can be up to 10^6.
//   S² and R² can be up to 10^12, which exceeds 32-bit int
//   (max ~2.1×10^9). So we use 64-bit long long.
//
// COMPLEXITY: O(1) time, O(1) space
// ============================================================

#include <iostream>

using namespace std;

int main() {
    // Fast I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    long long R, S;                     // 64-bit to handle squares up to 10^12
    
    // Read radius and side length
    if (cin >> R >> S) {
        
        // CASE 1: Can the circle fit INSIDE the square?
        // Condition: diameter of circle ≤ side of square → 2R ≤ S
        if (2 * R <= S) {
            cout << "Square\n";         // The square can contain the circle
        }
        // CASE 2: Can the square fit INSIDE the circle?
        // Condition: diagonal of square ≤ diameter of circle
        //   S√2 ≤ 2R  →  S² ≤ 2R²  (after squaring both sides)
        else if (S * S <= 2 * R * R) {
            cout << "Circle\n";         // The circle can contain the square
        }
        // CASE 3: Neither shape fully contains the other
        else {
            cout << "Complex\n";        // Partial/intersecting overlap
        }
    }
    
    return 0;
}
