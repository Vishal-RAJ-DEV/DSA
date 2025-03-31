#include <iostream>
#include <vector>
using namespace std;

void merge(vector<long long>& nums1, vector<long long>& nums2) {
    int m = nums1.size(), n = nums2.size();
    int len = m + n;

    vector<long long> merged(len);
    for (int i = 0; i < m; i++) merged[i] = nums1[i];
    for (int i = 0; i < n; i++) merged[m + i] = nums2[i];

    int gap = (len / 2) + (len % 2);

    while (gap > 0) {
        int left = 0, right = left + gap;
        while (right < len) {
            if (merged[left] > merged[right]) {
                swap(merged[left], merged[right]);
            }
            left++;
            right++;
        }
        if (gap == 1) break;
        gap = (gap / 2) + (gap % 2);
    }

    // Copy back to nums1
    for (int i = 0; i < len; i++) cout << merged[i] << " ";
    cout << endl;
}

int main() {
    vector<long long> arr1 = {1, 4, 8, 10};
    vector<long long> arr2 = {2, 3, 9};

    cout << "Merged array: ";
    merge(arr1, arr2);
    for(auto it : arr1) cout<<it<<" ";
    cout<<endl;
    for(auto it : arr2) cout<<it<<" ";
    cout<<endl;
    return 0;
}
