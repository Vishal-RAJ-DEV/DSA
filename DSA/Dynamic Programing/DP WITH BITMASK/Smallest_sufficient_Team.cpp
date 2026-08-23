#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class Solution 
{
public:
    vector<int> smallestSufficientTeam(vector<string>& req_skills, 
                                      vector<vector<string>>& people) 
    {
        int n = req_skills.size();
        int m = people.size();

        // Map every skill to a bit position
        unordered_map<string, int> skillIndex;

        for(int i = 0; i < n; i++) 
        {
            skillIndex[req_skills[i]] = i;
        }

        // Convert every person's skills into a bitmask
        vector<int> personMask(m, 0);

        for(int i = 0; i < m; i++) 
        {
            for(string& skill : people[i]) 
            {
                int bit = skillIndex[skill];

                personMask[i] |= (1 << bit);
            }
        }

        // dp[mask] = smallest team that can cover 'mask'
        vector<vector<int>> dp(1 << n);

        // Mark unreachable states
        for(int mask = 1; mask < (1 << n); mask++) 
        {
            dp[mask] = vector<int>(100);
        }

        // dp[0] = empty team
        dp[0] = {};

        // Try adding every person
        for(int i = 0; i < m; i++) 
        {
            // Traverse all possible skill states
            for(int mask = 0; mask < (1 << n); mask++) 
            {
                // Skip unreachable states
                if(dp[mask].size() == 100)
                    continue;

                // Add current person's skills
                int newMask = mask | personMask[i];

                // If this creates a smaller team
                if(dp[newMask].size() > dp[mask].size() + 1) 
                {
                    dp[newMask] = dp[mask];
                    dp[newMask].push_back(i);
                }
            }
        }

        // Full skill mask
        int fullMask = (1 << n) - 1;

        return dp[fullMask];
    }
};



int main(){
    return 0;
}