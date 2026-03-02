#include <bits/stdc++.h>
using namespace std;

/*
Space Optimization
If we closely look at the relation,

dp[i] =  dp[i-1] + dp[i-2]

we see that for any i, we do need only the last two values in the array. So is there a need to maintain a whole array for it? The answer is ‘No’. Let us call dp[i-1] as prev and dp[i-2] as prev2. Now understand the following illustration.

1.Each iteration’s cur_i and prev becomes the next iteration’s prev and prev2 respectively.
2.Therefore after calculating cur_i, if we update prev and prev2 according to the next step, we will always get the answer. 
3.After the iterative loop has ended we can simply return prev as our answer.
*/

//time complexity: O(n) as we are calculating the answer for each value from 2 to n once and then storing it in the prev and prev2 variables so that we can use it later without recalculating it again
//space complexity: O(1) as we are using only constant space for the prev and prev2 variables and curr variable to store the current fib value and we are not using any extra space for the dp array
class Solution {
public:
    int fib(int n) {
        // If n is 0 return 0
        if(n == 0) return 0;
        // If n is 1 return 1
        if(n == 1) return 1;

        // prev2 stores fib(n-2)
        int prev2 = 0;
        // prev stores fib(n-1)
        int prev = 1;
        // curr stores current fib
        int curr;

        // Loop from 2 to n
        for(int i = 2; i <= n; i++) {
            // Calculate current fib
            curr = prev + prev2;
            // Update prev2
            prev2 = prev;
            // Update prev
            prev = curr;
        }
        // Return final answer
        return prev;
    }
};

int main() {
    Solution s;
    int n = 10;
    cout << s.fib(n);
    return 0;
}
