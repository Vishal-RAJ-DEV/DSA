#include <iostream>
#include <bits/stdc++.h>
using namespace std;

/*
    PROBLEM: K Closest Points to Origin (LeetCode 973)

    Given an array of [x, y] points, find the k closest points to the
    origin (0, 0). Distance is Euclidean: sqrt(x² + y²). Since we only
    need to compare distances, we compare squared distances (x² + y²)
    to avoid floating-point sqrt.

    EXAMPLE:
    points = [[1,3], [-2,2], [5,8], [0,1]], k = 2
    Squared distances: [10, 8, 89, 1]
    Closest 2: [0,1] (dist=1)  and  [-2,2] (dist=8)
    Output: [[0,1], [-2,2]]

    ================================================================
    APPROACH 1: Max-Heap of Size K (Optimal)
    ================================================================

    INTUITION:
    - We only need the k closest points → keep a max-heap of size k.
    - A max-heap gives us O(1) access to the farthest among the k candidates.
    - For each point:
        1. Compute squared distance.
        2. Push (distance, index) into the heap.
        3. If heap size exceeds k, pop the farthest (max distance).
    - At the end, the heap contains exactly the k closest points.
    - We can discard any point farther than the kth closest so far.

    ALGORITHM:
    1. Create a max-heap of pairs (distance, index).
    2. Iterate all points:
       a. Compute d = x² + y².
       b. Push (d, i) into heap.
       c. If heap size > k, pop top (farthest).
    3. Pop remaining k elements from heap and collect their indices.

    TIME COMPLEXITY: O(n log k) — each push/pop is O(log k), heap size ≤ k
    SPACE COMPLEXITY: O(k) — heap stores at most k elements

    WHY NOT MIN-HEAP?
    - A min-heap approach would push ALL n points (O(n log n)),
      then pop k times (O(k log n)) → O(n log n) total.
    - Max-heap of size k is better: O(n log k), which is faster when k << n.
*/

class Solution_MaxHeap {
public:
    vector<vector<int>> kClosest(vector<vector<int>>& points, int k) {
        // Max-heap: stores {squaredDistance, index}
        // By default, priority_queue is a max-heap (largest pair first)
        priority_queue<pair<int, int>> pq;

        for (int i = 0; i < points.size(); i++) {
            int x = points[i][0];
            int y = points[i][1];
            int dist = x * x + y * y; // squared distance (avoids sqrt)

            pq.push({dist, i});       // add current point

            // Keep only the k closest points so far
            // Pop the farthest if we exceed size k
            if (pq.size() > k) {
                pq.pop();
            }
        }

        // Collect remaining k points from the heap
        vector<vector<int>> ans;
        while (!pq.empty()) {
            auto it = pq.top();
            pq.pop();
            int idx = it.second;
            ans.push_back(points[idx]);
        }

        // Note: order of ans may be arbitrary (closest to farthest or not)
        return ans;
    }
};

/*
    ================================================================
    APPROACH 2: Min-Heap (All Points, Then Pop K)
    ================================================================

    INTUITION:
    - Push ALL points with their distances into a min-heap.
    - The smallest distance will always be at the top.
    - Pop k times to get the k closest points.

    ALGORITHM:
    1. Create a min-heap of pairs (distance, index).
       (Use greater<pair<int,int>> comparator for min-heap.)
    2. Push (d, i) for every point into the heap.  → O(n log n)
    3. Pop k times → collect the indices of the k closest.  → O(k log n)

    TIME COMPLEXITY: O(n log n) — push all n points, then pop k times
    SPACE COMPLEXITY: O(n) — heap stores all n elements

    NOTE:
    - This is simpler to understand but less efficient than the max-heap
      approach when k << n.
    - However, when k is close to n, both perform similarly.
    - The max-heap approach (Approach 1) is preferred for this problem.

    VISUALISATION:
    points = [[1,3], [-2,2], [5,8], [0,1]], k = 2
    
    Min-Heap (distance, index):
    Step 1: push (10, 0) → heap: [(10,0)]
    Step 2: push (8, 1)  → heap: [(8,1), (10,0)]
    Step 3: push (89, 2) → heap: [(8,1), (10,0), (89,2)]
    Step 4: push (1, 3)  → heap: [(1,3), (8,1), (89,2), (10,0)]
    
    Pop 2 times:
    Pop 1: (1, 3)  → points[3] = [0,1]
    Pop 2: (8, 1)  → points[1] = [-2,2]
    Result: [[0,1], [-2,2]]
*/

class Solution_MinHeap {
public:
    vector<vector<int>> kClosest(vector<vector<int>>& points, int k) {
        // Min-heap: smallest distance on top
        // Using greater<pair<int,int>> makes it a min-heap
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

        // Push ALL points with their squared distances
        for (int i = 0; i < points.size(); i++) {
            int x = points[i][0];
            int y = points[i][1];
            int dist = x * x + y * y;
            pq.push({dist, i});
        }

        // Pop the k closest points (top k from min-heap)
        vector<vector<int>> ans;
        while (k--) {
            auto it = pq.top();
            pq.pop();
            int idx = it.second;
            ans.push_back(points[idx]);
        }

        // ans is ordered from closest to farthest
        return ans;
    }
};

/*
    ================================================================
    COMPARISON
    ================================================================

    | Aspect         | Max-Heap (size k)      | Min-Heap (all n)     |
    |----------------|------------------------|----------------------|
    | Heap size      | ≤ k                    | n                    |
    | Build time     | O(n log k)             | O(n log n)           |
    | Pop time       | O(k log k)             | O(k log n)           |
    | Total time     | O(n log k)             | O(n log n)           |
    | Space          | O(k)                   | O(n)                 |
    | Best for       | k << n                 | k ≈ n or simplicity  |

    Both produce correct results. The max-heap approach is the standard
    optimal solution for "top k smallest/largest" problems.
*/

int main() {
    Solution_MaxHeap s1;
    Solution_MinHeap s2;

    vector<vector<int>> points = {{1, 3}, {-2, 2}, {5, 8}, {0, 1}};
    int k = 2;

    cout << "Max-Heap approach: ";
    vector<vector<int>> res1 = s1.kClosest(points, k);
    for (auto& p : res1) cout << "[" << p[0] << "," << p[1] << "] ";
    cout << endl;

    cout << "Min-Heap approach: ";
    vector<vector<int>> res2 = s2.kClosest(points, k);
    for (auto& p : res2) cout << "[" << p[0] << "," << p[1] << "] ";
    cout << endl;

    // Edge case: k = total points
    vector<vector<int>> points2 = {{0, 0}, {1, 1}, {2, 2}};
    cout << "Edge (k=n): ";
    vector<vector<int>> res3 = s1.kClosest(points2, 3);
    for (auto& p : res3) cout << "[" << p[0] << "," << p[1] << "] ";
    cout << endl;

    return 0;
}
