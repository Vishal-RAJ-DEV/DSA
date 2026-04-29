#include <iostream>
#include <bits/stdc++.h>
using namespace std;

/*
Alice has some number of cards and she wants to rearrange the cards into groups so that each group is of size groupSize, and consists of groupSize consecutive cards.

Given an integer array hand where hand[i] is the value written on the ith card and an integer groupSize, return true if she can rearrange the cards, or false otherwise.

 

Example 1:

Input: hand = [1,2,3,6,2,3,4,7,8], groupSize = 3
Output: true
Explanation: Alice's hand can be rearranged as [1,2,3],[2,3,4],[6,7,8]
Example 2:

Input: hand = [1,2,3,4,5], groupSize = 4
Output: false
Explanation: Alice's hand can not be rearranged into groups of 4.*/


/*
Approach:
->Check if total cards can be divided into groups → if not, return false.
->Store all cards in a sorted map with frequency.
->Always pick the smallest available card to start a group.
->Try to form groupSize consecutive numbers → reduce their frequency.
->If any number is missing → false, else continue until map empty → true.
*/


class Solution {
public:
    bool isNStraightHand(vector<int>& hand, int groupSize) {
        //edge case check 
        if( hand.size() % groupSize != 0 ) return false;

        //now store all the value in the ordered map with the frequency 
        map<int , int> mpp;
        for( int &num : hand){ //O(nlogn)
            mpp[num]++;
        }

        //iterate in the map and make the group
        while( !mpp.empty()){ //O(n*groupSize)

            int curr = mpp.begin()->first;
            //use the first element to make the group which has the frequency not 0 
            for(int i = 0 ; i < groupSize ; i++){
                //if curr is 1 then curr + 1 is should be 2 , means 2 should be in the map
                if( mpp[curr + i] == 0) return false;

                mpp[curr + i]--;//decrese the freqency which is used 
        
                //remove the element which frequency is 0 
                if( mpp[curr + i] < 1 ) mpp.erase(curr + i);

            }
        }

        //all group are formed , no false return 
        return true;
    }
};

//another approch using the successor element 
class Solution {
public:
   bool findSuccessors(vector<int>& hand, int groupSize, int i, int n) {
        int next = hand[i] + 1;
        hand[i] = -1;  // Mark as used
        int count = 1;
        i += 1;
        while (i < n && count < groupSize) {
            if (hand[i] == next) {
                next = hand[i] + 1;
                hand[i] = -1;
                count++;
            }
            i++;
        }
        return count == groupSize;
    }

    bool isNStraightHand(vector<int>& hand, int groupSize) {
        int n = hand.size();
        if (n % groupSize != 0) return false;
        std::sort(hand.begin(), hand.end());
        for (int i = 0; i < n; i++) {
            if (hand[i] >= 0) {
                if (!findSuccessors(hand, groupSize, i, n)) return false;
            }
        }
        return true;
    }
};


int main(){
    Solution sol;
    vector<int> hand = {1, 2, 3, 6, 2, 3, 4, 7, 8};
    int groupSize = 3;
    cout << sol.isNStraightHand(hand, groupSize) << endl;   
    return 0;
}
