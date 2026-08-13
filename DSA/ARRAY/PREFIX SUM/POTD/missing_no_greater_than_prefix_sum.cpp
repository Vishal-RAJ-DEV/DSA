#include <iostream>
#include <bits/stdc++.h>
using namespace std;

/*
Problem (LeetCode 2996 - Smallest Missing Integer Greater Than Sequential Prefix Sum):
Given an array nums, return the smallest missing integer that is greater than or equal to
the "sequential prefix sum".

Sequential prefix sum = sum of the longest prefix of nums where every element is
exactly (previous element + 1).

Example: nums = [1, 2, 3, 5] -> sequential prefix = [1, 2, 3] -> sum = 6

Algorithm:
1. Start sum = nums[0].
2. Keep adding nums[i] to sum while the sequence continues (nums[i] == nums[i-1] + 1).
   Stop at the first break -> now sum = sum of the longest sequential prefix.
3. Candidate answer = sum. But sum might already exist in the array,
   and we need a MISSING integer. So:
4. While loop: as long as the current sum is PRESENT in the array, increment sum by 1.
   Stop when sum is NOT found in the array -> that is the smallest missing integer >= prefix sum.

How the while loop works in detail:
    while ( find(nums.begin(), nums.end(), sum) != nums.end() ) sum++;
    - find() scans the whole array for the value `sum`.
    - It returns an iterator to the matching element, or nums.end() if not found.
    - Condition is TRUE when `sum` exists in the array (iterator != end()).
    - Body increments sum by 1 and the check repeats with the new value.
    - Loop exits on the FIRST sum value that does not exist in the array.

Trace: nums = [3, 4, 5, 1, 12, 14, 13]
    sequential prefix = [3, 4, 5] -> sum = 12
    12 in array? yes -> sum = 13
    13 in array? yes -> sum = 14
    14 in array? yes -> sum = 15
    15 in array? no  -> loop stops, answer = 15

Complexity:
    - Prefix sum: O(n)
    - Each find() call scans the array: O(n)
    - While loop can run many times -> O(n^2) worst case, O(n) extra space (find uses no extra space)
*/

class Solution {
public:
    int missingInteger(vector<int>& nums) {
        int n = nums.size();

        // Start the sum with the first element
        int sum = nums[0];

        // Add elements while the prefix stays sequential (each element = previous + 1)
        for(int i = 1; i < n ; i++){
            if(nums[i] == nums[i-1]+1){
                sum += nums[i];          // sequence continues, extend the sum
            }else{
                break;                   // sequence broke, stop adding
            }
        }

        // While the current sum ALREADY exists in the array, it cannot be the answer,
        // so keep incrementing it until we find a value not present in the array
        while(find(nums.begin(), nums.end(), sum) != nums.end()) sum++;

        // sum is now the smallest missing integer >= sequential prefix sum
        return sum;
    }
};


int main(){
    return 0;
}