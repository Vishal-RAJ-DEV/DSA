#include <iostream>
#include <bits/stdc++.h>
using namespace std;

//the time complexity is O(n^2) and space complexity is O(1) if we don't consider the output space
//Approach: sort the array and then fix one element and use two pointer approach to find
vector<vector<int>> threeSum(vector<int> &nums)
{
    vector<vector<int>> result;
    sort(nums.begin(), nums.end());
    int n = nums.size();
    for (int i = 0; i < n - 2; i++) //n-2 because we need at least three elements to form a triplet
    {
        if (i > 0 && nums[i] == nums[i - 1])
            continue;
        int left = i + 1;
        int right = n - 1;

        while (left < right)
        {
            int sum = nums[i] + nums[left] + nums[right];
            if (sum == 0)
            {
                result.push_back({nums[i], nums[left], nums[right]});

                while (left < right && nums[left] == nums[left + 1])  //skip the duplicate elements
                    left++;
                while (left < right && nums[right] == nums[right - 1]) //skip the duplicate elements
                    right--;

                left++; // move to the next different element
                right--;// move to the next different element
            }
            else if (sum < 0)
                left++;
            else
                right--;
        }
    }
    return result;
}
int main()
{
    vector<int> arr = {-1, 0, 1, 2, -1, -4};
    vector<vector<int>> res = threeSum(arr);
    for (const auto &triplet : res)
    {
        cout << "[";
        for (int i = 0; i < triplet.size(); i++)
        {
            cout << triplet[i];
            if (i < triplet.size() - 1)
                cout << ", ";
        }
        cout << "]" << endl;
    }
    return 0;
}
