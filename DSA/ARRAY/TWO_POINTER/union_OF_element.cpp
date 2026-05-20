
// Algorithm (simple steps):
// 1) Use two pointers, one for each sorted array.
// 2) Pick the smaller element and add it if it's new.
// 3) Move that pointer forward.
// 4) When one array ends, add the remaining unique elements.

// Problem Statement: Given two sorted arrays, arr1, and arr2 of size n and m. Find the union of two sorted arrays.

#include <bits/stdc++.h>

using namespace std;

vector < int > FindUnion(int arr1[], int arr2[], int n, int m) {
  int i = 0, j = 0; // pointers for arr1 and arr2
  vector < int > Union; // result array with unique elements
  while (i < n && j < m) { // compare both arrays
    if (arr1[i] <= arr2[j]) { // take from arr1
      if (Union.size() == 0 || Union.back() != arr1[i])
        Union.push_back(arr1[i]); // add if new
      i++;
    } else { // take from arr2
      if (Union.size() == 0 || Union.back() != arr2[j])
        Union.push_back(arr2[j]); // add if new
      j++;
    }
  }
  while (i < n) { // add leftover elements from arr1
    if (Union.back() != arr1[i])
      Union.push_back(arr1[i]);
    i++;
  }
  while (j < m) { // add leftover elements from arr2
    if (Union.back() != arr2[j])
      Union.push_back(arr2[j]);
    j++;
  }
  return Union; // final union
}

int main()

{
  int n = 10, m = 7; // sizes of arrays
  int arr1[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}; // sorted array 1
  int arr2[] = {2, 3, 4, 4, 5, 11, 12}; // sorted array 2
  vector < int > Union = FindUnion(arr1, arr2, n, m); // compute union
  cout << "Union of arr1 and arr2 is  " << endl;
  for (auto & val: Union) // print all elements
    cout << val << " ";
  return 0; // end program
}

