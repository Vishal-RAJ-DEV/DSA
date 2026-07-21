#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    /*
        Logic / Intuition:
        We need to check whether there are two equal values nums[i] and nums[j]
        such that the distance between their indexes is at most k:

            abs(i - j) <= k

        Instead of comparing every pair, we keep a sliding window of the last
        k elements using an unordered_set.

        The set named "window" stores only the elements whose indexes are close
        enough to the current index "right". So, before inserting nums[right],
        if nums[right] is already present in the set, it means the same value
        appeared within distance k, and we can return true.

        If the window becomes bigger than k distance, we remove nums[left] and
        move left forward. This keeps only the useful recent elements.

        Dry run:
        nums = [1, 2, 3, 1], k = 3

        right = 0, nums[right] = 1
        window = {}
        1 is not present, insert 1
        window = {1}

        right = 1, nums[right] = 2
        window = {1}
        2 is not present, insert 2
        window = {1, 2}

        right = 2, nums[right] = 3
        window = {1, 2}
        3 is not present, insert 3
        window = {1, 2, 3}

        right = 3, nums[right] = 1
        window = {1, 2, 3}
        1 is already present, so another 1 exists within distance 3.
        Return true.

        Time Complexity: O(n), because each element is inserted and removed at most once.
        Space Complexity: O(k), because the set stores at most k nearby elements.
    */
    bool containsNearbyDuplicate(vector<int>& nums, int k) {
        int n = nums.size();

        // This set represents the current sliding window of nearby elements.
        // It helps us check duplicate values in O(1) average time.
        unordered_set<int>window;

        // left and right are the boundaries of the sliding window.
        int right = 0;
        int left  = 0;

        while( right< n){
            // If nums[right] already exists in the current window,
            // then we found the same value at two indexes whose distance is <= k.
            if(window.count(nums[right])) return true;

            // Add the current element to the window.
            window.insert(nums[right]);

            // If the distance between right and left reaches k,
            // remove nums[left] before moving further.
            // This keeps the window limited to elements close to the next right index.
            if(right - left >= k){//distance between should be lesser than k 
                window.erase(nums[left]); //if greater than remove it 
                left++; //increse the left 
            }

            // Move to the next element.
            right++;
        }

        // No duplicate pair was found within distance k.
        return false;
    }
};

//this is another approch to solve the problem using hash map, we will store the index of the element in the hash map and if we find the same element again then we will check the difference of the index and if it is less than or equal to k then we will return true otherwise we will update the index of the element in the hash map.
class Solution {
public:
    bool containsNearbyDuplicate(vector<int>& nums, int k) {

        // Stores the last index where each number was seen.
        unordered_map<int, int> lastIndex;

        // Traverse the array.
        for (int i = 0; i < nums.size(); i++) {

            // Check if we've seen this number before.
            if (lastIndex.count(nums[i])) {

                // If the distance between the current index and the
                // previous occurrence is at most k, we found a valid pair.
                if (i - lastIndex[nums[i]] <= k) {
                    return true;
                }
            }

            // Update the latest index of the current number.
            lastIndex[nums[i]] = i;
        }

        // No valid duplicate found.
        return false;
    }
};  

int main(){
    return 0;
}
