#include <bits/stdc++.h>
using namespace std;


// Naive approach
// Here we are using two loop to count the number of platform required at a time
//if the current train arrival time is greater than or equal to the arrival time of the other train and less than or equal to the departure time of the other train then we need one more platform
//same as if the other train arrival time is greater than or equal to the arrival time of the current train and less than or equal to the departure time of the current train then we need one more platform
//increase the count and update the answer with maximum count

// Class to group the solution method
class Solution {
public:
    // Function to count minimum platforms needed
    int countPlatforms(int n, int arr[], int dep[]) {

        // Initialize answer to 1
        int ans = 1;

        // Loop over all arrival times
        for (int i = 0; i < n; i++) {

            // Initialize count of overlapping intervals
            int count = 1;

            // Check overlap with every other train
            for (int j = i + 1; j < n; j++) {

                // Check if there is overlap between train i and j
                if ((arr[i] >= arr[j] && arr[i] <= dep[j]) ||
                    (arr[j] >= arr[i] && arr[j] <= dep[i])) {
                    count++;
                }
            }

            // Update maximum platform count
            ans = max(ans, count);
        }

        return ans;
    }
};

//algorithm
//here we are sorting the arrival and departure time of the train and then we are using two pointer approach to count the number of platform required at a time
//then we traversing in both the array 
//if the their is the arrival time is less than or equal to the departure time then we need one more platform and move the pointer of arrival time
//if the departure time is less than the arrival time then we can free one platform and move the pointer of departure time
//counter is incresing when there is train is arrived means one platform is needed and counter is decresing when there is train is departed means one platform is freed
class Solution {
public:
    // Function to find minimum platforms required
    int countPlatforms(int n, int arr[], int dep[]) {
        // Sort the arrival and departure times
        sort(arr, arr + n);
        sort(dep, dep + n);

        // Initialize pointers and counters
        int platforms = 1;
        int result = 1;
        int i = 1, j = 0;

        // Traverse both arrays
        while (i < n && j < n) {
            // If next train arrives before current one departs
            if (arr[i] <= dep[j]) {
                // One more platform needed
                platforms++;
                i++;
            } else {
                // One train departs, platform freed
                platforms--;
                j++;
            }

            // Update maximum required platforms
            result = max(result, platforms);
        }

        return result;
    }
};

int main() {
    int arr[] = {900, 945, 955, 1100, 1500, 1800};
    int dep[] = {920, 1200, 1130, 1150, 1900, 2000};
    int n = sizeof(arr) / sizeof(arr[0]);

    Solution obj;
    cout << "Minimum number of Platforms required " 
         << obj.countPlatforms(n, arr, dep) << endl;

    return 0;
}
