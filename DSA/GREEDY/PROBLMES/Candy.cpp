#include <bits/stdc++.h>
using namespace std;

class Solution1 {
public:
    // Function to calculate the minimum number of candies 
    int candy(vector<int>& ratings) {
        // Total number of children
        int n = ratings.size();
        
        // Array to keep track of candies given to each child, initialized to 1
        vector<int> candies(n, 1);
        
        // Boolean flag to track if we made any change in the current iteration
        bool updated = true;

        // Repeat until no changes are made in a full scan
        while (updated) {
            updated = false;

            // Left to right pass to check increasing rating condition
            for (int i = 1; i < n; ++i) {
                if (ratings[i] > ratings[i - 1] && candies[i] <= candies[i - 1]) {
                    candies[i] = candies[i - 1] + 1;
                    updated = true;
                }
            }

            // Right to left pass to check decreasing rating condition
            for (int i = n - 2; i >= 0; --i) {
                if (ratings[i] > ratings[i + 1] && candies[i] <= candies[i + 1]) {
                    candies[i] = candies[i + 1] + 1;
                    updated = true;
                }
            }
        }

        // Return the total candies by summing the array
        return accumulate(candies.begin(), candies.end(), 0);
    }
};

class Solution2{
public:
   // Function to calculate the minimum number of candies 
    int candy(vector<int>& ratings) {
        // Initialize each child with 1 candy
        int n = ratings.size();
        vector<int> candies(n, 1);

        // Traverse from left to right
        for (int i = 1; i < n; ++i) {
            // If current rating is higher than previous, give more candies
            if (ratings[i] > ratings[i - 1])
                candies[i] = candies[i - 1] + 1;
        }

        // Traverse from right to left
        for (int i = n - 2; i >= 0; --i) {
            // If current rating is higher than next, adjust candy count
            if (ratings[i] > ratings[i + 1])
                candies[i] = max(candies[i], candies[i + 1] + 1);
        }

        // Sum up all candies
        return accumulate(candies.begin(), candies.end(), 0);
    }
};

//increasing and decreasing slope approach
class Solution {
public:
    int candy(vector<int>& ratings) {
        int n = ratings.size();
        int candies = n; //initally all the n child have the one candy , total candies will be n
        //using the incresing and decresing slope to get the candy
        int i = 1 ; //interate in the rating , from to 1 to n-1

        while(i < n ){

            //if the rating is same , skip and continue
            if(ratings[i] == ratings[i-1]){
                i++;
                continue;
            }

            //incrsing slope 
            int peak = 0; //increse at greater slope
            while( ratings[i-1] < ratings[i]){
                peak++;
                candies += peak;
                i++;
                if( i == n )return candies;
            }

            //decresing slope 
            int dip = 0 ;
            while(i < n && ratings[i-1] > ratings[i]){
                dip++; //increase the decresing slope 
                candies += dip; //add to the candies 
                i++;
            }

            //now remove the smaller one from the peak and dip from the candies 
            //beacuse peak and dip for and rating , we take maximum one 
            candies -= min( peak , dip);
        }

        return candies;
    }
};


// Driver code
int main() {
    Solution obj;
    vector<int> ratings = {1, 0, 5};
    cout << "Minimum candies: " << obj.candy(ratings) << endl;
    return 0;
}
