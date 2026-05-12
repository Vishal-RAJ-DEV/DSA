
#include <bits/stdc++.h>
using namespace std;

/*
Question Explanation (Reverse Pair):
Count pairs (i, j) such that:
1) i < j
2) arr[i] > 2 * arr[j]

This is different from normal inversion counting (arr[i] > arr[j]).
Here left value must be strictly greater than twice the right value.

Example:
arr = [4, 1, 2, 3, 1]
Valid reverse pairs are:
- (4, 1) at indices (0,1) because 4 > 2*1
- (4, 1) at indices (0,4) because 4 > 2*1
Answer = 2
*/

//brute force approach : we can use two loops to count the number of pairs which is the pair of the left index and the right index where the value in the left index is greater than twice the value in the right index
//Time Complexity: O(N^2), where N = size of the given array.
//Space Complexity: O(1), as we are not using any extra space.
int countPairs(vector<int> &arr) {
    int cnt = 0;
    for (int i = 0; i < arr.size(); i++) {
        for (int j = i + 1; j < arr.size(); j++) {
            // Pair condition: i < j and arr[i] > 2*arr[j]
            if ((long long)arr[i] > 2LL * arr[j]) cnt++; //here we are checking if the value in the left index is greater than twice the value in the right index
        }
    }
    return cnt;
}


//this is the optimal approach to count the number of reverse pairs in the given array where we are using the merge sort algorithm to sort the array and while merging we are counting the number of pairs which is the pair of the left index and the right index where the value in the left index is greater than twice the value in the right index
//Time Complexity: O(2N*logN), where N = size of the given array.
//Space Complexity: O(N), as in the merge sort We use a temporary array to store elements in sorted order.
void merge(vector<int> &arr, int low, int mid, int high) {
    vector<int> temp; // temporary array
    int left = low;      // starting index of left half of arr
    int right = mid + 1;   // starting index of right half of arr

    // At this point, both halves [low..mid] and [mid+1..high] are already sorted.

    //storing elements in the temporary array in a sorted manner//

    while (left <= mid && right <= high) {
        if (arr[left] <= arr[right]) {
            temp.push_back(arr[left]);
            left++;
        }
        else {
            temp.push_back(arr[right]);
            right++;
        }
    }

    // if elements on the left half are still left //

    while (left <= mid) {
        temp.push_back(arr[left]);
        left++;
    }

    //  if elements on the right half are still left //
    while (right <= high) {
        temp.push_back(arr[right]);
        right++;
    }

    // transfering all elements from temporary to arr //
    for (int i = low; i <= high; i++) {
        arr[i] = temp[i - low];
    }
}
// Modification 1 : cnt variable to count the pairs
int countPairs(vector<int> &arr, int low, int mid, int high) {
    int right = mid + 1;
    int cnt = 0;

    // Count cross reverse-pairs where left part index i is in [low..mid]
    // and right part index is in [mid+1..high].
    // Since both halves are sorted, we can move 'right' only forward (two-pointer optimization).
    for (int i = low; i <= mid; i++) {
        while (right <= high && (long long)arr[i] > 2LL * arr[right]) right++; //here we are checking if the value in the left index is greater than twice the value in the right index
        //right will go till the while condition is false 
        // Number of valid j for this i = indices from (mid+1) to (right-1)
        cnt += (right - (mid + 1)); //total pairs can be formed for the ith element all the elements in the right half which are less than right index 
        //so all ele from mid + 1 to right - 1 can form a pair with the ith element as they are less than right index and greater than twice the value in the right index
    }
    return cnt;
}

//here cnt will store the total number of pairs which is the pair of the left index and the right index where the value in the left index is greater than twice the value in the right index
//and is store in the variable cnt and we will return cnt at the end of the merge sort function
//this cnt will be updated in the countPairs function which is called in the merge sort function and while merging we are counting the number of pairs which is the pair of the left index and the right index where the value in the left index is greater than twice the value in the right index
//then after counting the pairs we are merging the two halves of the array in sorted order and then returning the total count of pairs at the end of the merge sort function
// Time Complexity: O(2N*logN), where N = size of the given array.
// Space Complexity: O(N), as in the merge sort We use a temporary array to store
int mergeSort(vector<int> &arr, int low, int high) {
    int cnt = 0;
    // Base case: one element has no pair.
    if (low >= high) return cnt;
    int mid = (low + high) / 2 ;

    // 1) Count reverse pairs in left half.
    cnt += mergeSort(arr, low, mid);  // left half

    // 2) Count reverse pairs in right half.
    cnt += mergeSort(arr, mid + 1, high); // right half

    // 3) Count cross reverse pairs (left index in left half, right index in right half).
    cnt += countPairs(arr, low, mid, high); //Modification

    // 4) Merge halves so parent recursion level receives sorted segment.
    merge(arr, low, mid, high);  // merging sorted halves
    return cnt;
}

int team(vector <int> & skill, int n)
{
    // Wrapper function: returns total reverse pair count in whole array.
    return mergeSort(skill, 0, n - 1);
}

int main()
{
    vector<int> a = {4, 1, 2, 3, 1};
    int n = 5;

    // Dry run expectation for this input:
    // Reverse pairs are (4,1) at (0,1) and (4,1) at (0,4), so answer = 2.
    int cnt = team(a, n);
    cout << "The number of reverse pair is: "
         << cnt << endl;
    return 0;
}

