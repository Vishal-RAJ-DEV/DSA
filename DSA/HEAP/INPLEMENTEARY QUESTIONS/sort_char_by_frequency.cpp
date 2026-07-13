#include <iostream>
#include <bits/stdc++.h>
using namespace std;

/*
    QUESTION: 451. Sort Characters By Frequency

    Given a string s, sort it in decreasing order based on the frequency
    of the characters. Return the sorted string. If multiple characters
    have the same frequency, their relative order does not matter.

    Example:
        Input: s = "tree"
        Output: "eert"
        Explanation: 'e' appears twice, 'r' and 't' both appear once.
                     So 'e' must appear before both 'r' and 't'.

    Example:
        Input: s = "cccaaa"
        Output: "aaaccc" or "cccaaa"
        Explanation: Both 'c' and 'a' appear three times.

    Example:
        Input: s = "Aabb"
        Output: "bbAa"
        Explanation: 'b' appears twice, 'A' and 'a' appear once.
*/


// =========================================================
// APPROACH 1: Sorting with Fixed-Size Vector — O(n)
// =========================================================
/*
    LOGIC:
        1. Create a vector of pair<char, int> of size 123 (covers all ASCII
           characters 0-122). Index = ASCII value of character.
        2. Iterate through the string and for each character ch, update
           vec[ch] = {ch, current_freq + 1}.
        3. Sort the vector in descending order of frequency using a custom
           comparator lambda.
        4. Iterate through sorted vector and append each character 'freq'
           times to the result string.

    TIME COMPLEXITY:
        - Counting frequencies: O(n) where n = string length
        - Sorting 123 elements: O(123 log 123) = O(1) (constant size)
        - Building result string: O(n)
        - Overall: O(n) since the sort is on a constant-sized array

        Note: This approach works because the character set is limited to
        ASCII (0-122), making the sort constant time. If using full Unicode,
        this approach would not scale.

    SPACE COMPLEXITY:
        - Vector of 123 pairs: O(1) constant space
        - Result string: O(n)
        - Overall: O(n)
*/
class Solution {
public:
    typedef pair<char , int  > P;
    string frequencySort(string s) {
        vector<P>vec(123);
        for(char &ch : s) {
            int freq = vec[ch].second;
            vec[ch] = {ch , 1 + freq};
        }
        auto lambda = [&] ( P &p1 , P & p2){
            return p1.second > p2.second;
        };
        sort(begin(vec) , end(vec) , lambda);
        string result = "";
        for(int i = 0 ; i< 123;i++){
            if(vec[i].second > 0){
            char ch = vec[i].first;
            result += string(vec[i].second , ch);
            }

        }
        return result;
    }
};


// =========================================================
// APPROACH 2: Bucket Sort — O(n) Optimal
// =========================================================
/*
    LOGIC:
        1. Count frequency of each character using an unordered_map.
        2. Create a bucket array of size (n+1) where buckets[f] stores a
           vector of all characters that have frequency = f.
        3. Iterate buckets from highest frequency (n) down to 1.
           For each character in buckets[i], append it 'i' times to result.
        4. Return the result string.

    This avoids sorting entirely by using the frequency as the index into
    the bucket array. Since frequencies range from 1 to n, and string length
    is limited, we can directly place characters into their frequency bucket.

    TIME COMPLEXITY:
        - Counting frequencies: O(n)
        - Placing characters into buckets: O(k) where k = distinct chars
        - Iterating buckets from n down to 1: O(n)
        - Building result string: O(n)
        - Overall: O(n)

        This is the optimal solution since we process each character exactly
        once and never need to sort.

    SPACE COMPLEXITY:
        - Hashmap: O(k) where k = distinct characters (max 256 for extended ASCII)
        - Bucket array of vectors: O(n) if all characters are the same (single bucket)
        - Result string: O(n) — we reuse the input string
        - Overall: O(n)
*/
class Solution {
public:
    string frequencySort(string s) {
        unordered_map<char, int> mpp;
        for (char c : s) mpp[c]++;

        vector<vector<char>> buckets(s.size() + 1);
        for (auto&it : mpp) {
            buckets[it.second].push_back(it.first);
        }

        s = "";
       
        for (int i = buckets.size() - 1; i >= 1; i--) {
            for (char c : buckets[i]) {
                s.append(i, c);
            }
        }

        return s;
    }
};
int main(){
    return 0;
}
