#include <iostream>
#include <bits/stdc++.h>
using namespace std;
/*
Algorithm:-
1.Initialize an empty stack to track asteroids after collisions
2.Loop through each asteroid in the input array
3.If the asteroid is moving right, push it onto the stack
4.If the asteroid is moving left, check for collisions with top elements of the stack
5.While the top of the stack is a smaller right-moving asteroid, pop it from the stack
6.If the top of the stack is a right-moving asteroid of equal size, pop it and do not push the current asteroid
7.If the stack is empty or the top is a left-moving asteroid, push the current asteroid
8.After the loop ends, return the stack as the final result
*/
vector<int> asteroidCollision(vector<int> &asteroids)
{
    int n = asteroids.size();               // Get size of asteroid array
    vector<int> ans;                        // Stack to store surviving asteroids
    
    for (int i = 0; i < n; i++)            // Process each asteroid one by one
    {
        if (asteroids[i] < 0)              // Current asteroid is moving LEFT (negative)
        {
            // Keep destroying smaller RIGHT-moving asteroids in the stack
            while (!ans.empty() &&                    // Stack not empty AND
                   abs(asteroids[i]) > ans.back() &&  // LEFT asteroid is bigger AND
                   ans.back() > 0)                     // Top asteroid is moving RIGHT
            {
                ans.pop_back();            // Destroy the smaller RIGHT-moving asteroid
            }
            
            // Check if LEFT asteroid meets equal-sized RIGHT asteroid
            if (!ans.empty() && abs(asteroids[i]) == ans.back())
            {
                ans.pop_back();            // Both asteroids destroy each other
            }
            // LEFT asteroid survives if stack is empty OR top is also moving LEFT
            else if (ans.empty() || ans.back() < 0)
            {
                ans.push_back(asteroids[i]); // Add surviving LEFT asteroid
            }
            // If none of above conditions: LEFT asteroid gets destroyed by bigger RIGHT asteroid
        }
        else                               // Current asteroid is moving RIGHT (positive)
        {
            ans.push_back(asteroids[i]);   // RIGHT-moving asteroids never collide with previous ones
        }
    }
    return ans;                            // Return final state of surviving asteroids
}
int main()
{
    vector<int> asteroids1 = {5, 10, -5};
    vector<int> asteroids2 = {8 , -8};
    vector<int> asteroids3 = {10, 2, -5};
    vector<int> asteroids4 = {3,5,-6,2,-1,4};
    for (auto &it : asteroidCollision(asteroids1))
    {
        cout << it << " ";
    }
    cout << endl;
    for (auto &it : asteroidCollision(asteroids2))
    {
        cout << it << " ";
    }
    cout << endl;
    for (auto &it : asteroidCollision(asteroids3))
    {
        cout << it << " ";
    }
    cout << endl;
    for (auto &it : asteroidCollision(asteroids4))
    {
        cout << it << " ";
    }
    cout << endl;
    return 0;
}