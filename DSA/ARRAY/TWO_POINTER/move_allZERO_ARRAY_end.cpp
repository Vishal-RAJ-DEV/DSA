

#include <bits/stdc++.h>
using namespace std;

vector<int> moveZeros(int n, vector<int> a)
{
    // temporary array:
    vector<int> temp;
    // copy non-zero elements
    // from original -> temp array:
    for (int i = 0; i < n; i++)
    {
        if (a[i] != 0)
            temp.push_back(a[i]);
    }

    // number of non-zero elements.
    int nz = temp.size();

    // copy elements from temp
    // fill first nz fields of
    // original array:
    for (int i = 0; i < nz; i++)
    {
        a[i] = temp[i];
    }

    // fill rest of the cells with 0:
    for (int i = nz; i < n; i++)
    {
        a[i] = 0;
    }
    return a;
}

// Optimized code   Time Complexity: O(n), as we iterate through the array only once.
// Space Complexity: O(1), as we only use a constant amount of space to store the temporary variables.
void moveZeroes1(vector<int> &nums)
{
    int n = nums.size();
    int j = -1;
    for (int i = 0; i < n; i++)
    {
        if (nums[i] == 0)
        { // here we find the first zero in the array and store its index in j
            j = i;
            break;
        }
    }
    if (j == -1)
        return; // if there is no zero in the array we return the array as it is
    // now we will move all the non-zero elements to the left side of the array and
    for (int i = j + 1; i < n; i++)
    { // here we start from j+1 because we have already found the first zero at index j
        if (nums[i] != 0)
        { // then loop through the array and whenever we find a non-zero element we swap it with the element at index j and increment j
            // its like the j is keeping track of the position where the next non-zero element should be placed
            swap(nums[i], nums[j]);
            j++;
        }
    }
}
// Another approach to move all zeros to the end of the array while maintaining the relative order of non-zero elements.
void pushZerosToEnd(vector<int> &arr)
{

    // Pointer to track the position
    // for next non-zero element
    int count = 0;

    for (int i = 0; i < arr.size(); i++)
    {

        // If the current element is non-zero
        // count will keep track where the non - zero element
        // should be placed
        // it will skip if it not equal and count will remain to the
        // where zero will be
        // in the further loop when we find the non - zero ele
        // then it will be swap by that count element
        if (arr[i] != 0)
        {

            // Swap the current element with
            // the 0 at index 'count'
            swap(arr[i], arr[count]);
            // Move 'count' pointer to the
            // next position
            count++;
        }
    }
}

int main()
{
    vector<int> arr = {1, 0, 2, 3, 2, 0, 0, 4, 5, 1};
    int n = 10;
    vector<int> ans = moveZeros(n, arr);
    for (auto &it : ans)
    {
        cout << it << " ";
    }
    cout << '\n';
    return 0;
}

// dry run

// nums = [1, 0, 3, 0, 5]

// Step 1: Find the first zero

// j = -1 initially

// Loop i = 0 → 4:

// nums[0] = 1 → not zero

// nums[1] = 0 → ✅ found zero → set j = 1, break

// Now: j = 1

// Step 2: Move non-zero elements after j

// Loop i = j+1 = 2 to 4:

// i = 2: nums[2] = 3 (non-zero)

// swap(nums[2], nums[1]) → [1, 3, 0, 0, 5]

// increment j → 2

// i = 3: nums[3] = 0 (zero) → skip

// i = 4: nums[4] = 5 (non-zero)

// swap(nums[4], nums[2]) → [1, 3, 5, 0, 0]

// increment j → 3

// Final Output:

// nums = [1, 3, 5, 0, 0]