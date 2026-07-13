#include <iostream>
#include <bits/stdc++.h>
using namespace std;

/*
    QUESTION: 1338. Reduce Array Size to The Half

    You are given an integer array arr. You can choose a set of integers and
    remove all occurrences of those integers in the array.
    Return the minimum size of the set (number of distinct values chosen) so
    that at least half of the integers of the array are removed.

    Example:
        Input: arr = [3,3,3,3,5,5,5,2,2,7]
        Output: 2
        Explanation: Choosing {3,7} removes 5 elements (3,3,3,3,7) which is >= 5 (half of 10).
                     {3,5} also works but we need the minimum set size.
*/


// =========================================================
// APPROACH 1: Bucket Sort (Counting Sort) — Optimal O(n)
// =========================================================
/*
    LOGIC:
        1. Count frequency of each element in arr using a hashmap.
        2. Create a bucket array of size (n+1) where bucket[f] stores the
           count of distinct elements that have frequency = f.
        3. Iterate from the highest possible frequency (n) down to 1.
           For each frequency f, we can remove bucket[f] distinct elements,
           each contributing f removals. Keep removing until we reach target.
        4. The number of distinct elements chosen (ans) is the answer.

    TIME COMPLEXITY:
        - Counting frequencies: O(n)
        - Filling bucket array: O(k) where k = number of distinct values (k <= n)
        - Iterating bucket array from n down to 1: O(n) in worst case
        - Overall: O(n)

    SPACE COMPLEXITY:
        - Hashmap: O(k)
        - Bucket array: O(n)
        - Overall: O(n)
*/
class Solution {
public:
    int minSetSize(vector<int>& arr) {

        unordered_map<int,int> freq;

        for(int x : arr)
            freq[x]++;

        int n = arr.size();
        vector<int> bucket(n + 1, 0);

        for(auto &it : freq)
            bucket[it.second]++;

        int removed = 0;
        int ans = 0;
        int target = n / 2;

        for(int f = n; f >= 1 && removed < target; f--) {

            while(bucket[f] > 0 && removed < target) {

                removed += f;
                ans++;
                bucket[f]--;
            }
        }

        return ans;
    }
};


// =========================================================
// APPROACH 2: Max-Heap (Priority Queue) — O(n log k)
// =========================================================
/*
    LOGIC:
        1. Count frequency of each element in arr using a hashmap.
        2. Push all frequencies into a max-heap (priority_queue).
           The max-heap ensures the highest frequency is always at the top.
        3. Greedily pop the highest frequency and add it to 'removed'.
           Increment ans (each pop = choosing one distinct element).
        4. Stop when removed >= target (n/2) and return ans.

    TIME COMPLEXITY:
        - Counting frequencies: O(n)
        - Pushing k distinct frequencies into max-heap: O(k log k)
        - In worst case k = n (all distinct), so O(n log n)
        - Popping from heap: O(k log k) in worst case
        - Overall: O(n log n) worst case

    SPACE COMPLEXITY:
        - Hashmap: O(k)
        - Max-heap: O(k)
        - Overall: O(n)
*/
class Solution {
public:
    int minSetSize(vector<int>& arr) {
        int n = arr.size();

        // Step 1: Count frequencies
        unordered_map<int , int>freq;
        for( int i = 0 ; i < n; i++){
            freq[arr[i]]++;
        };

        // Step 2: Push all frequencies into max-heap
        priority_queue<int>pq;
        for( auto &it : freq){
            pq.push(it.second);
        }

        // Step 3: Greedily remove highest frequency elements
        int remove = 0;
        int ans = 0;
        int target = n / 2;

        while( remove < target){
            remove += pq.top();
            pq.pop();
            ans++;
        }

        return ans;
    }
};


// =========================================================
// APPROACH 3: Sorting Frequencies — O(n log n)
// =========================================================
/*
    LOGIC:
        1. Count frequency of each element in arr using a hashmap.
        2. Collect all frequencies into a vector 'f'.
        3. Sort frequencies in descending order (highest first).
        4. Iterate through sorted frequencies, accumulating removed count.
           Increment ans each time we take a distinct element.
        5. Return ans as soon as removed >= target.

    TIME COMPLEXITY:
        - Counting frequencies: O(n)
        - Sorting k distinct frequencies: O(k log k)
        - In worst case k = n (all distinct), so O(n log n)
        - Iterating through sorted frequencies: O(k)
        - Overall: O(n log n) worst case

    SPACE COMPLEXITY:
        - Hashmap: O(k)
        - Frequency vector: O(k)
        - Overall: O(n)
*/
class Solution {
public:
    int minSetSize(vector<int>& arr) {

        unordered_map<int,int> freq;

        for(int x : arr)
            freq[x]++;

        vector<int> f;

        for(auto &it : freq)
            f.push_back(it.second);

        sort(f.begin(), f.end(), greater<int>());

        int removed = 0;
        int ans = 0;
        int target = arr.size()/2;

        for(int x : f){

            removed += x;
            ans++;

            if(removed >= target)
                return ans;
        }

        return ans;
    }
};
int main(){
    return 0;
}
