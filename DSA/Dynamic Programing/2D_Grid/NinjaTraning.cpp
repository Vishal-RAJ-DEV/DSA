/*
Example 1:
Input: matrix = [[10, 40, 70], [20, 50, 80], [30, 60, 90]]
Output: 210
Explanation:
Day 1: fighting practice = 70
Day 2: stealth training = 50
Day 3: fighting practice = 90
Total = 70 + 50 + 90 = 210
This gives the optimal points.

Example 2:
Input: matrix = [[70, 40, 10], [180, 20, 5], [200, 60, 30]]
Output: 290
Explanation:
Day 1: running = 70
Day 2: stealth training = 20
Day 3: running = 200
Total = 70 + 20 + 200 = 290
This gives the optimal points.
*/

#include <bits/stdc++.h>
using namespace std;

class Memization
{
public:
//time complexity is O(n*4*3) and space complexity is O(n*4) + O(n) for the recursion stack
    // Recursive function to calculate the maximum points for the ninja training
    int f(int day, int last, vector<vector<int>> &points, vector<vector<int>> &dp)
    {
        // If the result for this day and last activity is already calculated, return it
        if (dp[day][last] != -1)
            return dp[day][last];

        // Base case: When we reach the first day (day == 0)
        if (day == 0)
        {
            int maxi = 0;
            // Calculate the maximum points for the first day by choosing an activity
            // different from the last one
            for (int i = 0; i <= 2; i++)
            {
                if (i != last)
                    maxi = max(maxi, points[0][i]);
            }
            // Store the result in dp array and return it
            return dp[day][last] = maxi;
        }

        int maxi = 0;
        // Iterate through the activities for the current day
        for (int i = 0; i <= 2; i++)
        {
            if (i != last)
            {
                // Calculate the points for the current activity and add it to the
                // maximum points obtained so far (recursively calculated)
                int activity = points[day][i] + f(day - 1, i, points, dp);
                maxi = max(maxi, activity);
            }
        }

        // Store the result in dp array and return it
        return dp[day][last] = maxi;
    }

    // Function to find the maximum points for ninja training
    int ninjaTraining(int n, vector<vector<int>> &points)
    {
        // Create a memoization table (dp) to store intermediate results
        vector<vector<int>> dp(n, vector<int>(4, -1));
        // Start the recursive calculation from the last day with no previous activity
        return f(n - 1, 3, points, dp);
    }
};

class Tabulation
{
public:
    // Function to find the maximum points for ninja training using tabulation
    // Function to find the maximum points for ninja training
    //time complexity is O(n*4*3) and space complexity is O(n*4)
    int ninjaTraining(int n, vector<vector<int>> &points)
    {
        // Create a 2D DP (Dynamic Programming) table to store the maximum points
        // dp[i][j] represents the maximum points at day i, considering the last activity as j
        vector<vector<int>> dp(n, vector<int>(4, 0));

        // Initialize the DP table for the first day (day 0)
        dp[0][0] = max(points[0][1], points[0][2]);
        dp[0][1] = max(points[0][0], points[0][2]);
        dp[0][2] = max(points[0][0], points[0][1]);
        dp[0][3] = max(points[0][0], max(points[0][1], points[0][2])); // Max points for day 0 considering any activity

        // Iterate through the days starting from day 1
        for (int day = 1; day < n; day++)
        {
            // For each day, check all possible "last activities" (0, 1, 2, or no previous activity 3)
            for (int last = 0; last < 4; last++)
            {
                dp[day][last] = 0; // Initialize dp[day][last] to 0
                // Iterate through the tasks (activities) for the current day
                for (int task = 0; task <= 2; task++)
                {
                    // If the current task is different from the last task, we can perform this task
                    if (task != last)
                    {
                        // Calculate the points for the current activity and add it to the maximum points obtained
                        // on the previous day with the previous task
                        int activity = points[day][task] + dp[day - 1][task];
                        // Update the maximum points for the current day and last activity
                        dp[day][last] = max(dp[day][last], activity);
                    }
                }
            }
        }

        // The maximum points for the last day with any activity can be found in dp[n-1][3]
        return dp[n - 1][3];
    }
};

class Space_Optimization
{
    // using the space optimization technique to reduce the space complexity from O(n*4) to O(4)
    //  Function to find the maximum points for ninja training
    //time complexity is O(n*4*3) and space complexity is O(4)
    int ninjaTraining(int n, vector<vector<int>> &points)
    {
        // Initialize a vector to store the maximum points for the previous day's activities
        vector<int> prev(4, 0);

        // Initialize the DP table for the first day (day 0)
        prev[0] = max(points[0][1], points[0][2]);
        prev[1] = max(points[0][0], points[0][2]);
        prev[2] = max(points[0][0], points[0][1]);
        prev[3] = max(points[0][0], max(points[0][1], points[0][2])); //this only for the filling the grid for the first day , there is no use of this in the next days

        // Iterate through the days starting from day 1
        for (int day = 1; day < n; day++)
        {
            // Create a temporary vector to store the maximum points for the current day's activities
            vector<int> temp(4, 0);
            for (int last = 0; last < 4; last++)
            {
                temp[last] = 0;
                // Iterate through the tasks for the current day
                for (int task = 0; task <= 2; task++)
                {
                    if (task != last)
                    {
                        // Calculate the points for the current activity and add it to the
                        // maximum points obtained on the previous day (stored in prev)
                        temp[last] = max(temp[last], points[day][task] + prev[task]);
                    }
                }
            }
            // Update prev with the maximum points for the current day
            prev = temp;
        }

        // The maximum points for the last day with any activity can be found in prev[3]
        return prev[3];
    }
};

int main()
{
    // Define the points matrix
    vector<vector<int>> points = {{10, 40, 70},
                                  {20, 50, 80},
                                  {30, 60, 90}};

    int n = points.size(); // Get the number of days
    // Call the ninjaTraining function to find the maximum points and print the result
    Memization obj;
    cout << obj.ninjaTraining(n, points) << endl;
}
