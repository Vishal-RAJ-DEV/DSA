#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    /*
        Problem:
        - We have n cities numbered from 0 to n - 1.
        - edges contains roads in the form:
              {city1, city2, weight}
          because the graph is undirected, city1 -> city2 and city2 -> city1
          both have the same distance.
        - distanceThreshold is the maximum distance allowed.

        Goal:
        - For every city, count how many cities can be reached from it with
          shortest distance <= distanceThreshold.
        - Return the city having the smallest reachable-city count.
        - If two cities have the same count, return the greater city number.

        Algorithm used:
        - Floyd-Warshall Algorithm.
        - It finds the shortest path between every pair of cities.
        - After that, we can easily count reachable cities for each city.

        Time Complexity: O(n^3), because of the three nested loops in Floyd.
        Space Complexity: O(n^2), because we store an n x n distance matrix.
    */
    int findCity(int n, int m, vector<vector<int>>& edges, int distanceThreshold) {
        
        /*
            dist[i][j] stores the shortest known distance from city i to city j.

            Initially, we do not know any path between most cities, so we set
            them as INT_MAX, which means unreachable / infinity.
        */
        vector<vector<int>> dist(n, vector<int> (n, INT_MAX));
        
        // Fill the direct road distances from the input edges.
        for (auto it : edges) {
            dist[it[0]][it[1]] = it[2];  // Set the distance from city1 to city2
            dist[it[1]][it[0]] = it[2];  // Set the distance from city2 to city1
        }
        
        // Set the diagonal to 0, as the distance from a city to itself is 0
        for (int i = 0; i < n; i++) dist[i][i] = 0;

        /*
            Floyd-Warshall Algorithm:

            k   = intermediate city
            i   = source city
            j   = destination city

            For every pair (i, j), we try to check whether going through k gives
            a shorter route:

                i -> k -> j

            Formula:
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j])

            Example:
            If current distance 0 -> 3 is 10,
            but 0 -> 2 is 4 and 2 -> 3 is 1,
            then going through 2 gives distance 5, so we update 10 to 5.
        */
        for (int k = 0; k < n; k++) {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    /*
                        If i -> k or k -> j is unreachable, then path
                        i -> k -> j does not exist, so skip it.

                        This check is also important because INT_MAX + something
                        can overflow.
                    */
                    if (dist[i][k] == INT_MAX || dist[k][j] == INT_MAX)
                        continue;

                    // Keep the shorter distance: direct/old path or path via k.
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }

        /*
            Selection part after Floyd-Warshall:

            cntCity:
            - Stores the minimum number of reachable cities found so far.
            - We start it with n because no city can have more than n reachable
              cities, so the first city will definitely update it.

            cityNo:
            - Stores the answer city number.
            - It is updated whenever we find a city with a smaller reachable count.

            Tie rule:
            - The problem asks for the greatest city number if counts are equal.
            - That is why we use:
                  if (cnt <= cntCity)
              instead of:
                  if (cnt < cntCity)

            Because city is increasing from 0 to n - 1, using <= means when the
            count is equal, the later city replaces the earlier city. Therefore,
            the final cityNo becomes the largest city index among tied cities.
        */
        int cntCity = n;
        int cityNo = -1;

        // Check every city as the starting city.
        for (int city = 0; city < n; city++) {
            int cnt = 0;

            // Count how many cities are reachable from this city within threshold.
            for (int adjCity = 0; adjCity < n; adjCity++) {
                // If the distance to the adjacent city is within the threshold, increment count
                if (dist[city][adjCity] <= distanceThreshold)
                    cnt++;
            }

            /*
                If this city can reach fewer cities, it becomes the new answer.

                If this city can reach the same number of cities, it also becomes
                the new answer because this city number is greater than previous
                ones due to the increasing loop order.

                Example:
                    city 0 has count 3  -> answer = 0
                    city 1 has count 2  -> answer = 1 because 2 is smaller
                    city 2 has count 2  -> answer = 2 because same count,
                                           but city number 2 is greater
            */
            if (cnt <= cntCity) {
                cntCity = cnt;
                cityNo = city;
            }
        }
        return cityNo;
    }
};

int main() {
    // Input data
    int n = 4;
    int m = 4;
    vector<vector<int>> edges = {{0, 1, 3}, {1, 2, 1}, {1, 3, 4}, {2, 3, 1}};
    int distanceThreshold = 4;

    // Create an object of the Solution class
    Solution obj;

    // Find the city with the least reachable cities within the threshold distance
    int cityNo = obj.findCity(n, m, edges, distanceThreshold);

    // Output the result
    cout << "The answer is node: " << cityNo << endl;

    return 0;
}
