/*
=====================================================================
 PROBLEM: Cellular Network (Codeforces 702C)
=====================================================================

 You are given n cities and m cell towers placed on a number line.
 Each city must be covered by at least one tower. A tower covers a
 city if the distance between them is <= r (the signal radius).

 Find the MINIMUM radius r such that every city is covered.

 EXAMPLE:
   Cities:    [1, 5, 10, 15]
   Towers:    [3, 7, 12, 18]

   The answer is r = 3, because:
     City 1  -> closest tower at 3   -> distance = 2
     City 5  -> closest tower at 7   -> distance = 2
     City 10 -> closest tower at 12  -> distance = 2
     City 15 -> closest tower at 12  -> distance = 3 (max)

   So minimum r = 3 covers all cities.

 DIAGRAM (Number Line):

   Towers (T) and Cities (C):

   1   3   5   7   10  12  15  18
   C   T   C   T   C   T   C   T
   |---2---|                   |---3---|
           |---2---|                   (City 15 to Tower 12)
                   |---2---|

   Each city connects to its NEAREST tower.
   The answer = maximum of all these minimum distances.

=====================================================================
 APPROACH (Two Pointers):
=====================================================================
 Both cities and towers are SORTED (input is given sorted).
 We use two pointers - one for cities (i) and one for towers (j).

 For each city, we find its closest tower and track the max distance.

 Time Complexity: O(n + m)
 Space Complexity: O(n + m)
=====================================================================
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;

    vector<long long> cities(n);
    vector<long long> towers(m);

    for (int i = 0; i < n; i++) {
        cin >> cities[i];
    }

    for (int i = 0; i < m; i++) {
        cin >> towers[i];
    }

    /*
     KEY IDEA:
     ========
     Since both arrays are sorted, for city[i], the closest tower
     must be somewhere around tower[j]. We don't need to scan all
     towers for every city. We can move j forward as we go.

     For city[i], if tower[j+1] is closer than tower[j], then
     tower[j+1] is a better candidate. We keep moving j forward
     until tower[j] is the closest tower to city[i].

     This works because:
       - Cities are processed left to right
       - Once we move j forward for city[i], we never need to
         go back (towers to the left are even farther for future cities)
    */

    long long r = 0;
    int j = 0;

    // Process each city left to right
    for (int i = 0; i < n; i++) {

        // Move tower pointer j to find the CLOSEST tower to cities[i]
        // Condition: if next tower is equally close or closer, move forward
        // This ensures j stops at the closest tower (or leftmost if tie)
        while (j + 1 < m &&
               abs(cities[i] - towers[j]) >=
               abs(cities[i] - towers[j + 1])) {
            j++;
        }

        // Now towers[j] is the closest tower to cities[i]
        long long distance = abs(cities[i] - towers[j]);

        // The answer must be at least this distance to cover city[i]
        // Take max because we need to cover ALL cities
        r = max(r, distance);
    }

    cout << r << endl;

    return 0;
}