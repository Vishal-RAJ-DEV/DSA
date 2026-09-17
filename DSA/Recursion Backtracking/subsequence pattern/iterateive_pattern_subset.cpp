#include <iostream>
#include <vector>
using namespace std;

vector<vector<int>> findSubsets(vector<int>& nums) {
    vector<vector<int>> result;
    
    // Start with empty subset
    result.push_back({});

    for (int num : nums) {
        int size = result.size();

        for (int i = 0; i < size; i++) {
            vector<int> subset = result[i];
            subset.push_back(num);
            result.push_back(subset);
        }
    }

    return result;
}

int main() {
    vector<int> nums = {1, 2, 3};
    vector<vector<int>> subsets = findSubsets(nums);
    cout << "Subsets:" << endl;
    for (const auto& subset : subsets) {
        cout << "[";
        for (size_t i = 0; i < subset.size(); i++) {
            cout << subset[i];
            if (i < subset.size() - 1) cout << ", ";
        }
        cout << "]" << endl;
    }
    

    return 0;
}