#include <bits/stdc++.h>
using namespace std;

// using liner search
/*
Complexity Analysis
Time Complexity: O(N * (sum(arr[])-max(arr[])+1)), where N = size of the array,
sum(arr[]) = sum of all array elements, max(arr[])

Space Complexity:  O(1) as we are not using any extra space to solve this
problem.
*/
class Solution {
public:
  int countStudents(vector<int> &arr, int pages) {
    int n = arr.size(); // size of array.
    int students = 1;
    long long pagesStudent = 0;
    for (int i = 0; i < n; i++) {
      if (pagesStudent + arr[i] <= pages) {
        // add pages to current student
        pagesStudent += arr[i];
      } else {
        // add pages to next student
        students++;
        pagesStudent = arr[i];
      }
    }
    return students;
  }

  int findPages(vector<int> &arr, int n, int m) {
    // book allocation impossible:
    if (m > n)
      return -1;

    int low = *max_element(arr.begin(), arr.end());
    int high = accumulate(arr.begin(), arr.end(), 0);

    for (int pages = low; pages <= high; pages++) {
      if (countStudents(arr, pages) == m) {
        return pages;
      }
    }
    return low;
  }
};

// using binary search
/*
Complexity Analysis

Time Complexity: O(N * log(sum(arr[])-max(arr[])+1)), where N = size of the
array, sum(arr[]) = sum of all array elements, max(arr[]) = maximum of all array
elements.

Space Complexity:  O(1) as we are not using any extra space to solve this
problem.
*/
class Solution1 {
public:
  int countStudents(vector<int> &arr, int pages) {
    int n = arr.size(); // size of array.
    int students = 1;
    long long pagesStudent = 0;
    for (int i = 0; i < n; i++) {
      if (pagesStudent + arr[i] <= pages) {
        // add pages to current student
        pagesStudent += arr[i];
      } else {
        // add pages to next student
        students++;
        pagesStudent = arr[i];
      }
    }
    return students;
  }

  int findPages(vector<int> &arr, int n, int m) {
    // book allocation impossible:
    if (m > n)
      return -1;

    int low = *max_element(arr.begin(), arr.end());
    int high = accumulate(arr.begin(), arr.end(), 0);
    while (low <= high) {
      int mid = (low + high) / 2;
      int students = countStudents(arr, mid);
      if (students > m) {
        low = mid + 1;
      } else {
        high = mid - 1;
      }
    }
    return low;
  }
};

int main() {
  vector<int> arr = {25, 46, 28, 49, 24};
  int n = 5;
  int m = 4;
  Solution sol;
  int ans = sol.findPages(arr, n, m);
  cout << "The answer is: " << ans << "\n";
  return 0;
}