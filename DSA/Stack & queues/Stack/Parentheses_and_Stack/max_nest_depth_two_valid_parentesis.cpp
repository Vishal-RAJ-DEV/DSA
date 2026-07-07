#include <iostream>
#include <bits/stdc++.h>
using namespace std;

// Problem idea:
// We are given a valid parentheses string seq.
// We need to split every parenthesis into one of two groups: 0 or 1.
// The goal is to make the maximum nesting depth of the two groups as small as possible.
//
// Key observation:
// If we assign parentheses by the parity of the current depth,
// then deeply nested brackets get distributed between the two groups.
//
// Rule used here:
// - Odd depth  -> group 1
// - Even depth -> group 0
//
// We only need one variable:
// depth = current nesting depth while scanning the string left to right.
//
// Why this works:
// - Every '(' creates a new nesting level.
// - Every ')' closes the current nesting level.
// - So the parity of depth tells us which group the current parenthesis belongs to.
class Solution {
public:
    vector<int> maxDepthAfterSplit(string seq) {
        int depth = 0 ;
        vector<int>ans;

        // Scan the string from left to right.
        for(char ch : seq){
            if( ch == '('){
                // For '(' we increase depth first.
                // This '(' belongs to the new level it creates.
                depth++;
                // Even depth -> group 0, odd depth -> group 1.
                ans.push_back(depth % 2);

            }else{
                // For ')' we assign it before decreasing depth.
                // It closes the current level, so it still belongs to that level.
                ans.push_back(depth % 2);
                depth--;
            }
        }

        return ans;
    }
};


int main(){
    return 0;
}
