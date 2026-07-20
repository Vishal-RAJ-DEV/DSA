#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> relativeSortArray(vector<int>& arr1, vector<int>& arr2) {
        vector<int> result;
     
        for (int i = 0; i < arr2.size(); i++) {
            for (int j = 0; j < arr1.size(); j++) {   
                if (arr1[j] == arr2[i]) {
                    result.push_back(arr1[j]);
                    arr1[j] = -1;
                }
            }
        }
        sort(arr1.begin(), arr1.end());

        for (int i = 0; i < arr1.size(); i++) {
            if (arr1[i] != -1) {
                result.push_back(arr1[i]);
            }
        }
        return result;
    }
};

class Solution {
public:
    vector<int> relativeSortArray(vector<int>& arr1, vector<int>& arr2) {
        unordered_map<int, int> countMap;
        vector<int> remaining, result;
        // Initialize count map with relative order elements
        for (int i = 0; i < arr2.size(); i++) {
            countMap[arr2[i]] = 0;
        }
        // Count occurrences of elements in target array
        for (int i = 0; i < arr1.size(); i++) {
            if (countMap.find(arr1[i]) != countMap.end()) {
                countMap[arr1[i]]++;
            } else {
                remaining.push_back(arr1[i]);
            }
        }
        // Sort the remaining elements
        sort(remaining.begin(), remaining.end());
        // Add elements as per relative order
        for (int i = 0; i < arr2.size(); i++) {
            for (int j = 0; j < countMap[arr2[i]]; j++) {
                result.push_back(arr2[i]);
            }
        }
        // Add remaining elements
        for (int i = 0; i < remaining.size(); i++) {
            result.push_back(remaining[i]);
        }
        return result;
    }
};


class Solution {
public:
    vector<int> relativeSortArray(vector<int>& arr1, vector<int>& arr2) {
        int maxElement = *max_element(arr1.begin(), arr1.end());
        vector<int> count(maxElement + 1);

        // Count occurrences of each element
        for (int element : arr1) {
            count[element]++;
        }

        vector<int> result;
        // Add elements as per relative order
        for (int element : arr2) {
            while (count[element] > 0) {
                result.push_back(element);
                count[element]--;
            }
        }
        // Add remaining elements in ascending order
        for (int num = 0; num <= maxElement; num++) {
            while (count[num] > 0) {
                result.push_back(num);
                count[num]--;
            }
        }
        return result;
    }
};


int main(){
    return 0;
}