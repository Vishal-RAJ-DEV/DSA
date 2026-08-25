#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:

    // Function to calculate nC2
    // C(n, 2) = n * (n - 1) / 2
    long long combinationOfTwo(long long n) {
        return n * (n - 1) / 2;
    }

    long long distributeCandies(int n, int limit) {

        // Maximum candies possible:
        // limit + limit + limit = 3 * limit
        if (n > 3 * limit) {
            return 0;
        }

        /*
            Step 1: Count all distributions

            x + y + z = n

            Using Stars and Bars:

            C(n + 3 - 1, 3 - 1)
            = C(n + 2, 2)
        */
        long long totalWays = combinationOfTwo(n + 2);


        /*
            Step 2: Subtract invalid cases

            Cases where one child gets more than limit.

            Suppose:

            x >= limit + 1

            Reserve limit + 1 candies for x.

            Remaining:

            n - (limit + 1)

            Distribute among x, y, z:

            C(n - limit - 1 + 2, 2)
            = C(n - limit + 1, 2)

            There are 3 possible children.
        */
        if (n > limit) {

            totalWays -=
                3 * combinationOfTwo(n - limit + 1);
        }


        /*
            Step 3: Add back cases where
            two children exceed the limit.

            These cases were subtracted twice.

            Two children need at least:

            (limit + 1) + (limit + 1)

            Remaining:

            n - 2 * (limit + 1)

            Stars and Bars:

            C(n - 2*limit - 2 + 2, 2)

            = C(n - 2*limit, 2)

            There are C(3,2) = 3 pairs of children.
        */
        if (n >= 2 * (limit + 1)) {

            totalWays +=
                3 * combinationOfTwo(n - 2 * limit);
        }

        return totalWays;
    }
};


int main(){
    return 0;
}