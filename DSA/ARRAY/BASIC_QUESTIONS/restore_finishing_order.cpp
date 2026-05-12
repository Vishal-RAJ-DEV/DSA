#include <iostream>
#include <bits/stdc++.h>
using namespace std;

//time comnplexity : O(n) and space complexity : O(n)
class Solution {
public:
    vector<int> recoverOrder(vector<int>& order, vector<int>& friends) {
        vector<int>ans;
        unordered_set<int> st( friends.begin() , friends.end());

        for( int i = 0 ; i< order.size() ; i++){
            if( st.count(order[i]) > 0){
                ans.push_back(order[i]);
            }
        }
        return ans; 
    }
};
int main(){
    vector<int> order = {1, 2, 3, 4, 5};
    vector<int> friends = {2, 4};
    Solution sol;
    vector<int> ans = sol.recoverOrder(order, friends);
    cout << "The finishing order of the friends is: ";
    for (int i = 0; i < ans.size(); i++) {
        cout << ans[i] << " ";
    }

    return 0;
}
