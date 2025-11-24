#include <iostream>
#include <bits/stdc++.h>
using namespace std;
/*
nput :cardScore = [1, 2, 3, 4, 5, 6] , k = 3
Output : 15
Explanation :Choosing the rightmost cards will maximize your total score. 
So optimal cards chosen are the rightmost three cards 4 , 5 , 6.
Th score is 4 + 5 + 6 => 15.


Input :cardScore = [5, 4, 1, 8, 7, 1, 3 ] , k = 3
Output :12
Explanation : In first step we will choose card from beginning with score of 5.
In second step we will choose the card from beginning again with score of 4.
In third step we will choose the card from end with score of 3.
The total score is 5 + 4 + 3 => 12
*/
// Brute force approach
// int maxScore(vector<int>& cardPoints, int k) {
//         // Get total number of cards
//         int n = cardPoints.size();

//         // Initialize the answer to 0
//         int maxSum = 0;

//         // Try taking i cards from the start and (k-i) from the end
//         for (int i = 0; i <= k; i++) {
//             // Initialize temporary sum for this combination
//             int tempSum = 0;

//             // Sum of i cards from the front
//             for (int j = 0; j < i; j++) {
//                 tempSum += cardPoints[j];
//             }

//             // Sum of (k - i) cards from the back
//             for (int j = 0; j < k - i; j++) {
//                 tempSum += cardPoints[n - 1 - j];
//             }

//             // Update max if this is a better combination
//             maxSum = max(maxSum, tempSum);
//         }

//         // Return the best total found
//         return maxSum;
//     }
// also optimized approach
int maxPointsCanObtain(vector<int> &scorePoints, int k)
{
    int n = scorePoints.size();
    int maxPoints = 0;
    for (int i = 0; i < k; i++)
    {
        maxPoints += scorePoints[i];

    }
    int finalMaxPoints = maxPoints;
    cout << "Initial maxPoints :" << maxPoints << endl;
    int left = k - 1;
    int right = n - 1;
    cout << "left :" << left << endl;
    cout << "right :" << right << endl;
    for (int i = 0; i < k; i++)
    {
        // Remove the leftmost card from current window
        maxPoints -= scorePoints[left--];

        // Add the rightmost card to current window
        maxPoints += scorePoints[right--];

        // Update maxPoints if current sum is better
        finalMaxPoints = max(finalMaxPoints, maxPoints);
        // so here we are removing the leftmost element and adding the rightmost element
        // and also decreasing the left pointer and right pointer till we reach k elements
        // means we are sliding the window from left to right and calculating the max sum by comaparing the previous max sum
        cout << "maxPoints :" << maxPoints << endl;
    }
    return finalMaxPoints;
}
// Optimized approach
int maxScore(vector<int> &cardPoints, int k)
{
    // Get the total number of cards
    int n = cardPoints.size();

    // Calculate initial sum by picking first k cards from front
    int total = 0;
    for (int i = 0; i < k; ++i)
    {
        total += cardPoints[i];
    }

    // Store current max score
    int maxPoints = total;

    // Move the window from front to back k times
    for (int i = 0; i < k; ++i)
    {
        // Subtract card from front
        total -= cardPoints[k - 1 - i]; // here k-1 is same as left pointer and i used to move the left pointer to left side like left -- decresing 

        // Add card from back
        total += cardPoints[n - 1 - i]; //same as here n-1 points to last element and i used move the left side like right -- decreasing in left side 

        // Update max score if needed
        maxPoints = max(maxPoints, total);
    }

    // Return the best score
    return maxPoints;
}

int main()
{
    vector<int> scorePoints = {1, 2, 3, 4, 5, 6, 1};
    vector<int> scorePoint= {100,40,17,9,73,75};
    int k = 3;
    cout << maxPointsCanObtain(scorePoints, k) << endl;
    cout<<endl;
    cout << maxPointsCanObtain(scorePoint, k) << endl;
    cout << maxScore(scorePoints, k) << endl;

    return 0;
}
