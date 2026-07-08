#include <iostream>
#include <bits/stdc++.h>
using namespace std;

/*
Question:
You are given an integer array arr.
Return true if the number of occurrences of each value in the array is unique.
Otherwise return false.

What does unique occurrence mean?
- First count how many times each number appears.
- Then check whether any two different numbers have the same frequency.
- If no frequency repeats, return true.

Example:
arr = [1, 2, 2, 1, 1, 3]

Frequency of each number:
1 -> 3 times
2 -> 2 times
3 -> 1 time

Frequencies are [3, 2, 1]
All are different, so answer = true

Another example:
arr = [1, 2]
1 -> 1 time
2 -> 1 time

Frequencies are [1, 1]
Frequency 1 is repeated, so answer = false
*/

/*
Approach 1: Hash map + hash set + size comparison

Logic:
1. Use a hash map to count frequency of each number.
2. Put all frequency values into a hash set.
3. A set stores only unique values.
4. If all frequencies were unique, then:
   number of keys in map == number of frequencies in set
5. Otherwise, if some frequency repeats, set size becomes smaller.

Intuition:
- map tells us: "how many times does each number appear?"
- set tells us: "which frequency values are present?"
- repeated frequencies get merged inside the set

Example:
frequencies = [3, 2, 1]
set = {3, 2, 1}
map size = 3, set size = 3 => true

frequencies = [1, 1]
set = {1}
map size = 2, set size = 1 => false
*/
class SolutionApproach1 {
public:
    bool uniqueOccurrences(vector<int>& arr) {
        unordered_map<int, int> freq;

        // Count how many times each number appears.
        for (auto x : arr) {
            freq[x]++;
        }

        unordered_set<int> s;

        // Insert each frequency into the set.
        for (auto x : freq) {
            s.insert(x.second);
        }

        // If no frequency repeated, both sizes must match.
        return freq.size() == s.size();
    }
};

/*
Approach 2: Hash map + hash set with early duplicate check

Logic:
1. Use a hash map to count frequency of each number.
2. Traverse each frequency one by one.
3. Before inserting a frequency into the set, check if it already exists.
4. If yes, return false immediately.
5. Otherwise insert it.
6. If loop finishes, all frequencies were unique.

Intuition:
- This approach is similar to Approach 1,
  but instead of waiting until the end and comparing sizes,
  it stops immediately when a duplicate frequency is found.

Difference from Approach 1:
- Approach 1 checks uniqueness indirectly using sizes.
- Approach 2 checks uniqueness directly using set lookup.
- Approach 2 may return earlier if a duplicate is found quickly.
*/
class SolutionApproach2 {
public:
    bool uniqueOccurrences(vector<int>& arr) {
        unordered_map<int, int> freq;

        // Count frequency of each number.
        for (int num : arr) {
            freq[num]++;
        }

        unordered_set<int> st;

        // Check whether any frequency is already used.
        for (auto it : freq) {
            if (st.count(it.second))
                return false;

            st.insert(it.second);
        }

        return true;
    }
};

/*
Approach 3: Sorting-based approach without using frequency hash map

Logic:
1. Sort the array.
2. Equal elements now come together.
3. Count how many times each distinct number appears.
4. Store those counts inside a vector.
5. Sort the count vector.
6. If any adjacent counts are equal, then frequency is repeated.

Intuition:
- After sorting the array, same numbers are grouped together.
- So we can count occurrences by walking once through the sorted array.
- Then we only need to check whether the occurrence counts themselves are unique.

Example:
arr = [1, 2, 2, 1, 1, 3]
After sort: [1, 1, 1, 2, 2, 3]
Counts become: [3, 2, 1]
After sorting counts: [1, 2, 3]
No equal adjacent values => true

Difference from first two approaches:
- First two use hashing directly on values and frequencies.
- This approach uses sorting to group equal numbers.
- It may be useful when you want to solve the problem without hash maps,
  but sorting increases time complexity.
*/
class SolutionApproach3 {
public:
    bool uniqueOccurrences(vector<int>& arr) {
        sort(arr.begin(), arr.end());
        vector<int> v;

        for (int i = 0; i < arr.size(); i++) {
            int cnt = 1;

            // Count how many times the current sorted value appears.
            while (i + 1 < arr.size() && arr[i] == arr[i + 1]) {
                cnt++;
                i++;
            }

            v.push_back(cnt);
        }

        // Sort the frequency list so equal counts become adjacent.
        sort(v.begin(), v.end());

        // If two adjacent frequencies are same, occurrence is not unique.
        for (int i = 1; i < v.size(); i++) {
            if (v[i] == v[i - 1]) {
                return false;
            }
        }

        return true;
    }
};

int main() {
    vector<int> arr = {1, 2, 2, 1, 1, 3};

    SolutionApproach1 a1;
    SolutionApproach2 a2;
    SolutionApproach3 a3;

    cout << a1.uniqueOccurrences(arr) << '\n';
    cout << a2.uniqueOccurrences(arr) << '\n';
    cout << a3.uniqueOccurrences(arr) << '\n';

    return 0;
}
