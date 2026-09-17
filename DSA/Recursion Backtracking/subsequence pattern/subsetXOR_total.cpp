#include <iostream>
#include <bits/stdc++.h>
using namespace std;

// Helper recursive function to generate subsequences
void helper(vector<int> &digits, int index, vector<int> &current, vector<int> &result , int &totalXOR)
{
    // Base case: If index reaches digits length, add current subsequence to result
    if (index == digits.size())
    {
        int xor_val = 0;
        for(auto &it : current){
            xor_val ^= it;
        }
        totalXOR += xor_val;
        result.push_back(xor_val);
        return;
    }

    // Exclude current digit and recurse
    helper(digits, index + 1, current, result, totalXOR);

    // Include current digit and recurse
    current.push_back(digits[index]);
    helper(digits, index + 1, current, result, totalXOR);
    // Backtrack: remove last digit before returning to previous call
    current.pop_back();
}

// Function to return all subsequences of digits in number s
vector<int> getSubsequences(vector<int> &arr)
{
    // Vector to store all subsequences
    vector<int> result;
    int totalXOR = 0;

    // Current subsequence being built
    vector<int> current;
    helper(arr, 0, current, result , totalXOR);
    cout<<"The total XOR of all subsequences is: "<<totalXOR<<endl;
    return result;
}

int main()
{
    vector<int> arr = {5, 1, 6};
    vector<int> subsequences = getSubsequences(arr);
    cout<<"The XOR values of all subsequences are: "<<endl;
    for (auto &it : subsequences)
    {
        cout << it << endl;
    }
    

    return 0;
}
