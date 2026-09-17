#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    /*
        Algorithm / intuition:

        We have to generate all unique permutations of nums.
        A permutation means we arrange all numbers in every possible order.

        Example:
            nums = [1, 1, 2]

        Without duplicate handling, recursion may create:
            [1, 1, 2]
            [1, 1, 2]   duplicate, because the two 1's swapped positions
            [1, 2, 1]
            [1, 2, 1]   duplicate
            [2, 1, 1]
            [2, 1, 1]   duplicate

        So this code first sorts nums:
            [1, 1, 2]

        Sorting places equal numbers together. Then during recursion, we can
        skip a duplicate number if choosing it would create the same branch
        that was already created by its previous equal number.

        Important variables:

        temp:
        - Stores the current permutation being formed.
        - It grows one element at a time.
        - When temp.size() == nums.size(), one complete permutation is ready.

        ans:
        - Stores all final unique permutations.

        used:
        - used[i] tells whether nums[i] is already present in temp.
        - If used[i] == 1, we cannot take nums[i] again in the same permutation.

        Recursion idea:
        - At every level, choose one unused number and push it into temp.
        - Recursively fill the next position.
        - After returning, pop that number out and mark it unused again.

        This "push -> recurse -> pop" pattern is called backtracking.
    */
    void solve( vector<int>&temp ,vector<vector<int>>&ans , vector<int>&used ,vector<int>& nums){
        /*
            Base case:
            If temp has the same length as nums, it means we selected one number
            for every position, so temp is a complete permutation.

            Example:
                nums = [1, 1, 2]
                temp = [1, 2, 1]
            Now temp is complete, so store it in ans.
        */
        if(temp.size() == nums.size()){
            ans.push_back( temp);
            return;
        }

        /*
            Try every index as the next element of the current permutation.

            Think of every recursive level as filling one position:
                level 0 fills temp[0]
                level 1 fills temp[1]
                level 2 fills temp[2]
                ...
        */
        for(int i= 0 ; i < nums.size(); i++){
            /*
                If nums[i] is already used in temp, skip it.

                Example:
                    nums = [1, 1, 2]
                    temp = [1 at index 0]
                We cannot use index 0 again, otherwise one number would appear
                twice from the same position.
            */
            if( used[i])continue;

            /*
                Duplicate skipping condition:

                    i > 0
                    nums[i] == nums[i - 1]
                    used[i - 1] == 0

                Meaning:
                - Current number is the same as the previous number.
                - The previous same number has NOT been used in this branch yet.

                Then skip current nums[i].

                Why?
                Because choosing the second duplicate before the first duplicate
                creates the same permutation branch as choosing the first one.

                Example:
                    nums = [1a, 1b, 2]

                At the first position:
                    Choosing 1a first will generate all permutations starting
                    with 1.

                    Choosing 1b first would generate the exact same set of
                    permutations, because 1a and 1b have equal value.

                So we allow the first unused duplicate to be chosen first, and
                skip the later duplicate until the previous duplicate has already
                been used in the current branch.

                If used[i - 1] == 1, then it is okay to use nums[i], because the
                previous duplicate is already inside temp before it. That creates
                a valid order like [1a, 1b, 2].
            */
            if( i>0 && nums[i] == nums[i-1] && !used[i-1]) continue;

            /*
                Choose step:
                - Mark nums[i] as used.
                - Add nums[i] into temp.

                This means nums[i] is now fixed at the current position.

                Example:
                    temp = [1]
                    choose 2
                    temp becomes [1, 2]
            */
            used[i] = 1;
            temp.push_back(nums[i]);

            /*
                Explore step:
                Recursively fill the next position after choosing nums[i].
            */
            solve ( temp , ans , used , nums);

            /*
                Backtracking / pop-out step:

                After the recursive call returns, all permutations that start
                with the current temp choice have already been generated.

                Now we must remove the last chosen number so that the loop can
                try another number at this same position.

                Example:
                    nums = [1, 2, 3]

                    temp = [1, 2, 3]
                    store it in ans

                    return to previous level:
                    pop 3
                    temp becomes [1, 2]

                    return again:
                    pop 2
                    temp becomes [1]

                    now the loop can try 3 after 1:
                    temp becomes [1, 3]

                Without pop_back(), temp would keep old values and the next
                branch would be wrong.
            */
            temp.pop_back();

            /*
                Restore used[i]:
                Since nums[i] was removed from temp, it becomes available again
                for another branch of recursion.

                This undo step is what allows the algorithm to try every possible
                arrangement.
            */
            used[i] = 0;
        }
    }
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        vector<int>temp;
        vector<vector<int>>ans;

        /*
            used array has the same size as nums.
            0 means this index is not used in current temp.
            1 means this index is already used in current temp.
        */
        vector<int>used(nums.size() , 0);

        /*
            Sorting is required for duplicate handling.
            Equal values come side by side, so this condition can detect them:
                nums[i] == nums[i - 1]
        */
        sort( nums.begin() , nums.end());

        // Start building permutations from an empty temp.
        solve( temp , ans , used , nums);

        return ans;
    }
};

int main(){
    return 0;
}
