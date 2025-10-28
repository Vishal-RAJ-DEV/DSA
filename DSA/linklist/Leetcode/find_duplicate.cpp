#include <iostream>
#include <bits/stdc++.h>
using namespace std;
int findDuplicate(vector<int>& nums) {
    int slow = nums[0];                // Initialize slow pointer starting at first element
    int fast = nums[0];                // Initialize fast pointer starting at first element

    // Phase 1: Find intersection point of slow and fast pointers in the cycle
    do {
        slow = nums[slow];             // Move slow pointer one step (follow array value as index)
        fast = nums[nums[fast]];       // Move fast pointer two steps (follow array values as indices)
    } while (slow != fast);            // Continue until pointers meet

    // Phase 2: Find the entrance to the cycle (the duplicate number)
    slow = nums[0];                    // Reset slow pointer to beginning
    while (slow != fast) {             // Continue until pointers meet again
        slow = nums[slow];             // Move slow pointer one step
        fast = nums[fast];             // Move fast pointer one step (not two!)
    }
    return slow;                       // Return the duplicate number
}

int main(){
    vector<int> nums = {1, 3, 4, 2, 2};
    cout << "Duplicate number: " << findDuplicate(nums) << endl;
    return 0;
}

/*
Dry Run of Find Duplicate Number Algorithm
Let's trace through the execution of the algorithm for the input array nums = [1, 3, 4, 2, 2]:

Initial setup:
slow = nums[0] = 1
fast = nums[0] = 1
Phase 1: Find intersection point
Iteration 1:
slow = nums[slow] = nums[1] = 3
[fast = nums[nums[fast]] = nums[nums[1]] = nums[3] = 2]
slow (3) != fast (2), so continue
Iteration 2:
slow = nums[slow] = nums[3] = 2
[fast = nums[nums[fast]] = nums[nums[2]] = nums[4] = 2]
slow (2) != fast (2), wait, they're equal! This is confusing...
Let me trace more carefully - the values represent the indices we're moving to:

Iteration 2 (corrected):
slow = nums[slow] = nums[3] = 2
[fast = nums[nums[fast]] = nums[2] = 4]
slow (2) != fast (4), so continue

Iteration 3:
slow = nums[slow] = nums[2] = 4
[fast = nums[nums[fast]] = nums[4] = 2]
slow (4) != fast (2), so continue

Iteration 4:
slow = nums[slow] = nums[4] = 2
[fast = nums[nums[fast]] = nums[2] = 4]
slow (2) != fast (4), so continue

Iteration 5:
slow = nums[slow] = nums[2] = 4
[fast = nums[nums[fast]] = nums[4] = 2]
slow (4) != fast (2), so continue

Iteration 6:
slow = nums[slow] = nums[4] = 2
[fast = nums[nums[fast]] = nums[2] = 4]
slow (2) != fast (4), so continue

Iteration 7:
slow = nums[slow] = nums[2] = 4
[fast = nums[nums[fast]] = nums[4] = 2]
slow (4) == fast (2), wait, they're not equal yet...
Let me trace once more, making sure to track the actual values correctly:

Corrected Phase 1:
Iteration 1:
slow = nums[1] = 3
[fast = nums[nums[1]] = nums[3] = 2]  

Iteration 2:
slow = nums[3] = 2
[fast = nums[nums[2]] = nums[4] = 2]
Now slow (2) == fast (2), so we exit the loop
Phase 2: Find the entrance to the cycle
slow = nums[0] = 1
fast = 2 (remained from Phase 1)
Iteration 1:
slow = nums[1] = 3
fast = nums[2] = 4
slow (3) != fast (4), so continue
Iteration 2:
slow = nums[3] = 2
fast = nums[4] = 2
slow (2) == fast (2), so we exit the loop
Result:
Return slow = 2
The duplicate number in the array is 2.
*/