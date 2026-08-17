#include <iostream>
#include <bits/stdc++.h>
using namespace std;\


class Solution {
public:
    int numRescueBoats(vector<int>& people, int limit) {

        // Sort so that:
        // left  -> lightest remaining person
        // right -> heaviest remaining person
        sort(people.begin(), people.end());

        int left = 0;
        int right = people.size() - 1;

        int boats = 0;

        while (left <= right) {

            // Try to pair the heaviest person with the lightest person.
            // If they fit, both can share one boat.
            if (people[left] + people[right] <= limit) {
                left++;
                right--;
            }
            else {
                // Even the lightest person cannot fit with the heaviest.
                // Therefore, the heaviest person cannot fit with anyone
                // and must take a boat alone.
                right--;
            }

            // In both cases, one boat is used.
            boats++;
        }

        return boats;
    }
};
int main(){
    return 0;
}