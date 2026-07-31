#include <bits/stdc++.h>
using namespace std;
/*
Problem Statement: Given an array/list of length ‘N’, where the array/list represents the boards and each element of the given array/list represents the length of each board. Some ‘K’ numbers of painters are available to paint these boards. Consider that each unit of a board takes 1 unit of time to paint. You are supposed to return the area of the minimum time to get this job done of painting all the ‘N’ boards under the constraint that any painter will only paint the continuous sections of boards.

Examples
Example 1:
Input Format: N = 4, boards[] = {5, 5, 5, 5}, k = 2
Result: 10
Explanation: We can divide the boards into 2 equal-sized partitions, so each painter gets 10 units of the board and the total time taken is 10.

*/
// Class to solve the Painter Partition Problem using Binary Search
class PainterPartition {
public:
    // Helper function: counts how many painters are needed if each can paint at most 'time' units
    int countPainters(vector<int> &boards, int time) {
        int painters = 1;
        long long boardsPainter = 0;

        for (int i = 0; i < boards.size(); i++) {
            if (boardsPainter + boards[i] <= time) {
                // Allocate board to current painter
                boardsPainter += boards[i];
            } else {
                // Allocate board to new painter
                painters++;
                boardsPainter = boards[i];
            }
        }

        return painters;
    }

    // Main function: finds the minimum max time using binary search
    int findLargestMinDistance(vector<int> &boards, int k) {
        int low = *max_element(boards.begin(), boards.end());      // At least the largest board
        int high = accumulate(boards.begin(), boards.end(), 0);    // At most the total sum

        int result = high;

        while (low <= high) {
            int mid = (low + high) / 2;  // Mid time to test
            int painters = countPainters(boards, mid);

            if (painters > k) {
                low = mid + 1; // Too few painters → increase time
            } else {
                result = mid;  // Valid solution → try to minimize
                high = mid - 1;
            }
        }

        return result;
    }
};

int main() {
    vector<int> boards = {10, 20, 30, 40};
    int k = 2;

    PainterPartition pp;
    int ans = pp.findLargestMinDistance(boards, k);
    cout << "The answer is: " << ans << "\n"; // Expected: 60
    return 0;
}
