#include <iostream>
#include <bits/stdc++.h>
using namespace std;

// Problem idea:
// Given two arrays nums1 and nums2, count:
// - how many elements in nums1 also appear in nums2
// - how many elements in nums2 also appear in nums1
//
// The result is a pair:
// { count_from_nums1, count_from_nums2 }
//
// Important detail:
// This code counts every matching occurrence in the array being scanned.
// If an element appears multiple times in nums1 and is present in nums2,
// each appearance contributes to ans1. The same idea applies to nums2.
//
// Algorithm used:
// 1. Store all elements of nums1 in one hash set.
// 2. Store all elements of nums2 in another hash set.
// 3. Scan nums1 and count values that are found in the nums2 set.
// 4. Scan nums2 and count values that are found in the nums1 set.
//
// Why this works:
// unordered_set gives average O(1) lookup, so checking whether a value
// appears in the other array becomes fast.
class Solution {
public:
    vector<int> findIntersectionValues(vector<int>& nums1, vector<int>& nums2) {
        // Hash sets to store unique values from both arrays.
        unordered_set<int>hs1;
        unordered_set<int>hs2;

        // Fill both sets. The loop runs until both arrays are fully processed.
        int i = 0 ; int j = 0;
        while( i < nums1.size() || j < nums2.size()){
            if( i < nums1.size()){
                hs1.insert(nums1[i]); i++;
            }
            if( j < nums2.size()){
                hs2.insert(nums2[j]); j++;
            }
                
        }

        // Count how many elements from nums1 are also present in nums2.
        int ans1 = 0 ;
        // Count how many elements from nums2 are also present in nums1.
        int ans2 = 0 ;

        // Scan nums1 and check membership in nums2's set.
        for( int i = 0 ; i < nums1.size() ; i++){
            if(hs2.find(nums1[i]) != hs2.end()){
                ans1++;
            }
        }

        // Scan nums2 and check membership in nums1's set.
        for( int x : nums2){
            if( hs1.find(x) != hs1.end()){
                ans2++;
            }
        }

        // Return the two counts as required.
        return { ans1 , ans2 };


        
        
    }
};



int main(){
    return 0;
}
