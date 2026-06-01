#include <bits/stdc++.h>
using namespace std;

/*
    Problem:
    We are given:
    - student[i] = greed of the ith student
    - cookie[j] = size of the jth cookie

    A student becomes content only if:
    cookie size >= student greed

    Each cookie can be given to at most one student.
    We need to find the maximum number of content students.

    Main Algorithm:
    1. Sort the students by greed.
    2. Sort the cookies by size.
    3. At every state, we decide what to do with the current cookie:
       - TAKE it if it can satisfy the current student.
       - SKIP it and try the next cookie for the same student.

    Why sorting is done?
    Sorting helps us consider smaller greed students and smaller cookies first.
    This gives a clean order for the DP states:
    if we are at student index i and cookie index j, then all students before i
    and all cookies before j have already been decided.

    Why DP is applied here?
    From every pair (i, j), where:
    - i = current student index
    - j = current cookie index

    we may again reach the same state through different decision paths.
    For example, after skipping/taking previous cookies, we can repeatedly ask:
    "What is the maximum answer from student i and cookie j onward?"

    So this problem has:
    1. Overlapping subproblems:
       The same (student index, cookie index) state can be solved again and again.

    2. Optimal substructure:
       The best answer from (i, j) depends on the best answer of smaller future
       states like (i, j + 1) and (i + 1, j + 1).

    DP State:
    dp[i][j] = maximum number of students we can satisfy using students from
    index i to end and cookies from index j to end.

    Choices:
    1. skip = dp[i][j + 1]
       Do not use cookie[j]. Try the next cookie for the same student.

    2. take = 1 + dp[i + 1][j + 1]
       Use cookie[j] for student[i], but only if cookie[j] >= student[i].
       Then one student is satisfied, and both indexes move forward.

    Final answer:
    dp[0][0], because we start with the first student and first cookie.

    Note:
    This question also has a simpler greedy solution, but here DP is shown to
    understand the take/skip pattern used in subsequence-style problems.
*/

class MemoizationSolution {
public:
    // Function to find the maximum number of content students
    int findContentChildren(vector<int>& student, vector<int>& cookie) {
        // Sort both arrays to apply the greedy strategy
        sort(student.begin(), student.end());
        sort(cookie.begin(), cookie.end());

        // memo[i][j] stores the answer when we are trying to satisfy
        // student[i] using cookies from cookie[j] onward.
        vector<vector<int>> memo(student.size(), vector<int>(cookie.size(), -1));

        // Start recursion from index 0 for both arrays
        return helper(0, 0, student, cookie, memo);
    }

private:
    // Recursive helper function with memoization
    int helper(int studentIndex, int cookieIndex, vector<int>& student, vector<int>& cookie, vector<vector<int>>& memo) {
        // Base case: if we reach end of either list
        if (studentIndex >= (int)student.size() || cookieIndex >= (int)cookie.size())
            return 0;

        // Return memoized result if already computed
        if (memo[studentIndex][cookieIndex] != -1)
            return memo[studentIndex][cookieIndex];

        int result = 0;

        /*
            TAKE choice:
            If cookie[cookieIndex] can satisfy student[studentIndex],
            we assign this cookie to this student.

            After taking:
            - one student is satisfied, so we add 1.
            - move to next student because current student is done.
            - move to next cookie because one cookie can be used only once.
        */
        if (cookie[cookieIndex] >= student[studentIndex]) {
            result = max(result, 1 + helper(studentIndex + 1, cookieIndex + 1, student, cookie, memo));
        }

        /*
            SKIP choice:
            Do not use the current cookie for the current student.

            This can be useful when the cookie is too small, or when DP is
            comparing all choices. We move only cookieIndex forward because
            the same student still needs a cookie.
        */
        result = max(result, helper(studentIndex, cookieIndex + 1, student, cookie, memo));

        // Store the result in memo table
        return memo[studentIndex][cookieIndex] = result;
    }
};


class TabulationSolution {
public:
    // Function to find the maximum number of content students using tabulation
    int findContentChildren(vector<int>& student, vector<int>& cookie) {
        int n = student.size();
        int m = cookie.size();

        // Sort both arrays to prepare for DP
        sort(student.begin(), student.end());
        sort(cookie.begin(), cookie.end());

        /*
            dp[i][j] means:
            maximum students we can satisfy starting from student index i
            and cookie index j.

            Why size is n + 1 and m + 1?
            Recursion has this base case:
            if i == n or j == m, return 0.

            That means the tabulation table must contain one extra row
            for i == n and one extra column for j == m.

            dp[n][j] = 0 means no students are left.
            dp[i][m] = 0 means no cookies are left.

            vector initializes all cells with 0, so these base cases are
            already handled automatically.
        */
        vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

        // Fill DP table from bottom up because dp[i][j] depends on
        // dp[i][j + 1] and dp[i + 1][j + 1], which are future states.
        for (int i = n - 1; i >= 0; --i) {
            for (int j = m - 1; j >= 0; --j) {
                /*
                    SKIP:
                    Do not give cookie[j] to student[i].
                    Student i remains the same, but we try the next cookie.
                */
                int skip = dp[i][j + 1];

                /*
                    TAKE:
                    Give cookie[j] to student[i] only if cookie size is
                    greater than or equal to the student's greed.

                    Then 1 student is satisfied, and both indexes move ahead.
                */
                int take = 0;
                if (cookie[j] >= student[i]) {
                    take = 1 + dp[i + 1][j + 1];
                }

                // Take the best of both choices
                dp[i][j] = max(skip, take);
            }
        }

        return dp[0][0];
    }
};

class SpaceOptimizationSolution {
public:
    // Function to find the maximum number of content students using space optimization
    int findContentChildren(vector<int>& student, vector<int>& cookie) {
        int n = student.size();
        int m = cookie.size();

        sort(student.begin(), student.end());
        sort(cookie.begin(), cookie.end());

        /*
            Space Optimization:

            In tabulation:
            dp[i][j] depends on:
            1. dp[i][j + 1]     -> same row, next column
            2. dp[i + 1][j + 1] -> next row, next column

            So we do not need the full n + 1 by m + 1 table.
            We only keep:
            - nextRow, which represents dp[i + 1][...]
            - currRow, which represents dp[i][...]

            Why size is m + 1?
            We still need the extra column j == m for the base case:
            if no cookies are left, answer is 0.

            nextRow initially represents dp[n][...].
            This is the base case where no students are left, so every
            value is 0. vector<int>(m + 1, 0) handles it automatically.
        */
        vector<int> nextRow(m + 1, 0);

        for (int i = n - 1; i >= 0; --i) {
            /*
                currRow[m] = 0 is the base case for this row:
                when j == m, no cookies are left, so no more students
                can be satisfied.
            */
            vector<int> currRow(m + 1, 0);

            for (int j = m - 1; j >= 0; --j) {
                // SKIP: leave student[i] unsatisfied for now and try cookie[j + 1].
                int skip = currRow[j + 1];

                // TAKE: assign cookie[j] to student[i] if it can satisfy the greed.
                int take = 0;
                if (cookie[j] >= student[i]) {
                    take = 1 + nextRow[j + 1];
                }

                currRow[j] = max(skip, take);
            }

            // Current row becomes the next row for the student above it.
            nextRow = currRow;
        }

        return nextRow[0];
    }
};

int main() {
    vector<int> student = {1, 2, 3};
    vector<int> cookie = {1, 1};

    // Create solver object
    SpaceOptimizationSolution solver;

    // Get the number of content students and print it
    int result = solver.findContentChildren(student, cookie);
    cout << "Maximum number of content students: " << result << endl;

    return 0;
}
