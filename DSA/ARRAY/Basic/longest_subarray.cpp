// Longest Subarray with sum K | [Postives and Negatives]


// Problem Statement: Given an array of integers, find the length of the longest subarray with a sum equal to K. The array can contain both positive and negative integers.

#include <bits/stdc++.h>
using namespace std;

int getLongestSubarray(vector<int>& a, long long k) {
    int n = a.size(); // size of the array.

    map<long long, int> preSumMap;
    long long sum = 0;
    int maxLen = 0;
    for (int i = 0; i < n; i++) {
        //calculate the prefix sum till index i:
        sum += a[i];

        // if the sum = k, update the maxLen:
        if (sum == k) {
            maxLen = max(maxLen, i + 1);  //here we do the i+1 because the inclusive range starts from 0
        }

        // calculate the sum of remaining part i.e. x-k:
        long long rem = sum - k;

        //Calculate the length and update maxLen:
        if (preSumMap.find(rem) != preSumMap.end()) {
            int len = i - preSumMap[rem];
            maxLen = max(maxLen, len);
        }

        //Finally, update the map checking the conditions:
        if (preSumMap.find(sum) == preSumMap.end()) {     //means:If this prefix sum has never been stored before...
            preSumMap[sum] = i;
        }
    }

    return maxLen;
}
/*
Step 1 → Initialize:

sum = 0

maxLen = 0

preSumMap = {}

Step 2 → Loop:

i = 0 → a[0] = 1

sum = 1

sum != k

rem = 1 - 6 = -5 (not in map)

Add {1: 0}

Map → {1:0}



i = 1 → a[1] = 2

sum = 3

sum != k

rem = 3 - 6 = -3 (not in map)

Add {3: 1}

Map → {1:0, 3:1}



i = 2 → a[2] = 3

sum = 6

✅ sum == k → maxLen = max(0, 3) = 3

rem = 6 - 6 = 0 (not in map)

Add {6: 2}

Map → {1:0, 3:1, 6:2}



i = 3 → a[3] = 1

sum = 7

sum != k

rem = 7 - 6 = 1 → Found in map at index 0

Length = 3 - 0 = 3 → maxLen = 3

Add {7: 3}

Map → {1:0, 3:1, 6:2, 7:3}



i = 4 → a[4] = 1

sum = 8

rem = 8 - 6 = 2 (not in map)

Add {8: 4}



i = 5 → a[5] = 1

sum = 9

rem = 9 - 6 = 3 → Found at index 1

Length = 5 - 1 = 4 → ✅ maxLen = 4

Add {9: 5}



i = 6 → a[6] = 1

sum = 10

rem = 10 - 6 = 4 (not in map)

Add {10: 6}



i = 7 → a[7] = 4

sum = 14

rem = 14 - 6 = 8 → Found at index 4

Length = 7 - 4 = 3 → no update

Add {14: 7}



i = 8 → a[8] = 2

sum = 16

rem = 16 - 6 = 10 → Found at index 6

Length = 8 - 6 = 2 → no update

Add {16: 8}



i = 9 → a[9] = 3

sum = 19

rem = 19 - 6 = 13 (not in map)

Add {19: 9}

✅ Final Answer:

maxLen = 4 */

int getLongestSubarray1(vector<int>& a, long long k) {
    int n = a.size(); // size of the array.

    int left = 0, right = 0; // 2 pointers
    long long sum = a[0];
    int maxLen = 0;
    while (right < n) {
        // if sum > k, reduce the subarray from left
        // until sum becomes less or equal to k:
        while (left <= right && sum > k) {
            sum -= a[left];
            left++;
        }

        // if sum = k, update the maxLen i.e. answer:
        if (sum == k) {
            maxLen = max(maxLen, right - left + 1);
        }

        // Move forward thw right pointer:
        right++;
        if (right < n) sum += a[right];
    }

    return maxLen;
}

/*
| Iteration | left | right | sum | Condition hit         | maxLen | Window Subarray                                                     |
| --------- | ---- | ----- | --- | --------------------- | ------ | ------------------------------------------------------------------- |
| Start     | 0    | 0     | 1   | init                  | 0      | {1}                                                                 |
| right=1   | 0    | 1     | 3   | —                     | 0      | {1,2}                                                               |
| right=2   | 0    | 2     | 6   | ✅ sum==k              | 3      | {1,2,3}                                                             |
| right=3   | 0    | 3     | 7   | shrink → left=1,sum=6 | 3      | {2,3,1}                                                             |
| right=4   | 1    | 4     | 7   | shrink → left=2,sum=5 | 3      | {3,1,1}                                                             |
| right=5   | 2    | 5     | 6   | ✅ sum==k              | 4      | {3,1,1,1}                                                           |
| right=6   | 2    | 6     | 7   | shrink → left=3,sum=4 | 4      | {1,1,1,1}                                                           |
| right=7   | 3    | 7     | 8   | shrink → left=5,sum=6 | 4      | {1,1,4} → then {1,4}                                                |
| right=8   | 5    | 8     | 6   | ✅ sum==k              | 4      | {1,4,1}? correction {1,4,2}? actually window= {1,4,2}? wait careful |
| right=9   | 7    | 9     | 9   | shrink → left=8,sum=5 | 4      | {2,3}                                                               |
*/

int main()
{
    vector<int> a = {2, 3, 5, 1, 9};
    long long k = 10;
    int len = getLongestSubarray(a, k);
    cout << "The length of the longest subarray is: " << len << "\n";
    return 0;
}

// Time complexity: O(N), where N is the size of the array.
// Space complexity: O(1), as we only use a constant amount of space to store the variables.