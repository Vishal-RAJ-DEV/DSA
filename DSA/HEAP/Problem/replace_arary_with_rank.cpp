#include <bits/stdc++.h>
using namespace std;

//brute force approch
//time  complexity of the n^2
class Solution {
public:
    // Function to replace elements with their rank
    vector<int> replaceWithRank(vector<int>& arr) {
        // Final answer vector
        vector<int> rankArr;

        // Loop through each element of the array
        for (int i = 0; i < arr.size(); i++) {
            // Set to store unique elements less than arr[i]
            unordered_set<int> smaller;

            // Loop again to compare with every other element
            for (int j = 0; j < arr.size(); j++) {
                if (arr[j] < arr[i]) {
                    // Add to set if element is smaller
                    smaller.insert(arr[j]);
                }
            }

            // Rank is number of unique smaller elements + 1
            int rank = smaller.size() + 1;

            // Store the rank
            rankArr.push_back(rank);
        }

        return rankArr;
    }
};

//optimal approch 
//time complexity of the nlogn
class Solution {
public:
    // Function to replace elements by their rank in the array
    vector<int> replaceWithRank(vector<int>& arr) {
        // Copy the original array for sorting
        vector<int> sortedArr = arr;

        // Sort the array
        sort(sortedArr.begin(), sortedArr.end());

        // Create a map to store rank of each unique number
        unordered_map<int, int> rankMap;

        // Initialize rank counter
        int rank = 1;

        // Assign rank to each unique element in sorted order
        for (int num : sortedArr) {
            // If this number is not already assigned a rank
            if (rankMap.find(num) == rankMap.end()) {
                rankMap[num] = rank;
                rank++;
            }
        }

        // Replace each element in original array with its rank
        vector<int> result;
        for (int num : arr) {
            result.push_back(rankMap[num]);
        }

        return result;
    }
};

// Driver code
int main() {
    vector<int> arr = {20, 15, 26, 2, 98, 6};
    Solution sol;
    vector<int> result = sol.replaceWithRank(arr);

    for (int r : result) {
        cout << r << " ";
    }
    cout << endl;
    return 0;
}
