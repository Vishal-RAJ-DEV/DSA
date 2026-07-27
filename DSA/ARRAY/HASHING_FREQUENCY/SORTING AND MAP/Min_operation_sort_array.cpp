#include <iostream>
#include <bits/stdc++.h>
using namespace std;
/*
Method 1: Map + Swap (Easy to Implement)

1. Copy the array and sort it.
2. Store (value -> current index) in a map.
3. Traverse the array:
   - If current value is already correct, continue.
   - Otherwise, find where the correct value is using the map.
   - Swap both values.
   - Update their indices in the map.
   - Increment swap count.
4. Return total swaps.
*/


int minimumSwaps(vector<int>& arr) {

    vector<int> sorted = arr;
    sort(sorted.begin(), sorted.end());

    unordered_map<int,int> pos;

    for(int i=0;i<arr.size();i++)
        pos[arr[i]] = i;

    int swaps = 0;

    for(int i=0;i<arr.size();i++){

        if(arr[i] == sorted[i])
            continue;

        swaps++;

        int correctIndex = pos[sorted[i]];

        pos[arr[i]] = correctIndex;
        pos[sorted[i]] = i;

        swap(arr[i], arr[correctIndex]);
    }

    return swaps;
}

/*

Method 2: Cycle Detection (Classical Interview Method)

1. Store (value, original index) for every element.
2. Sort the pairs by value.
3. Create a visited array.
4. Traverse each index:
   - Skip if already visited or already in correct position.
   - Follow the cycle using original indices.
   - Count cycle length.
   - Add (cycle length - 1) to the answer.
5. Return total swaps.
*/

int minimumSwaps(vector<int>& nums) {

    int n = nums.size();

    vector<pair<int,int>> arr;

    for(int i=0;i<n;i++)
        arr.push_back({nums[i], i});

    sort(arr.begin(), arr.end());

    vector<bool> visited(n,false);

    int swaps = 0;

    for(int i=0;i<n;i++) {

        // Already visited or already in correct position
        if(visited[i] || arr[i].second == i)
            continue;

        int cycleSize = 0;
        int j = i;

        while(!visited[j]) {

            visited[j] = true;

            j = arr[j].second;

            cycleSize++;
        }

        swaps += cycleSize - 1;
    }

    return swaps;
}

// | Map + Swap               | Cycle Detection                      |
// | ------------------------ | ------------------------------------ |
// | Actually performs swaps  | Doesn't perform swaps                |
// | Uses `value → index` map | Uses `(value, original index)` pairs |
// | Easier to code           | Standard interview solution          |
// | `O(n log n)`             | `O(n log n)`                         |
// | `O(n)` space             | `O(n)` space                         |

/*Map + Swap
Sort → Find Correct Element → Swap → Update Map

Cycle
Sort → Find Cycles → Answer += (Cycle Size - 1)
*/



int main(){
    return 0;
}