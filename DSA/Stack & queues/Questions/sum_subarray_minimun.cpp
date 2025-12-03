#include <iostream>
#include <bits/stdc++.h>
using namespace std;

//summary algorithm 
/*
1. Initialize two arrays left and right to store the indices of the previous less element and next less element for each element in the input array.
2. Use a stack to help find the previous less elements:
   - Iterate through the array from left to right.
   - For each element, pop elements from the stack until the top of the stack is less than the current element.
   - The top of the stack (if not empty) will be the index of the previous less element; otherwise, use -1.
   - Push the current index onto the stack.
3. Clear the stack and repeat a similar process to find the next less elements:
    - Iterate through the array from right to left.
    - For each element, pop elements from the stack until the top of the stack is less than or equal to the current element.
    - The top of the stack (if not empty) will be the index of the next less element; otherwise, use n (size of the array).
    - Push the current index onto the stack.
4. Calculate the sum of subarray minimums:
   - For each element in the array, calculate the number of subarrays where it is the minimum using the left and right arrays by muiltiplying the counts of subarrays on the left and right.
   - The contribution of each element to the total sum is its value multiplied by the number of such subarrays.
*/
int sumSubarrayMins(vector<int>& arr){
    int n = arr.size();
    stack<int> st;
    vector<int> left(n), right(n);
    
    // Calculate left array
    // where each elemetnt's left[i] is the index of the previous less element
    for(int i = 0; i < n; i++){
        while(!st.empty() && arr[i] < arr[st.top()]) {
            st.pop();
        }
        left[i] = st.empty() ? -1 : st.top(); //we use -1 so that when there is no smaller element on left side we can use i-(-1) = i+1 to get the count of left subarrays
        st.push(i);
    }
    
    // Clear stack
    while(!st.empty()) st.pop();
    
    // Calculate right array
    // where each element's right[i] is the index of the next less element
    for(int i = n - 1; i >= 0; i--){
        while(!st.empty() && arr[i] <= arr[st.top()]){
            st.pop();
        }
        right[i] = st.empty() ? n : st.top(); //wew use n so that when there is no smaller element on right side we can use n-i get the count of left subarrays
        st.push(i);
    }
    
    // Calculate sum with proper modulo arithmetic
    long long ans = 0;
    long long mod = 1e9 + 7;  // Changed to long long
    
    for(int i = 0; i < n; i++){
        // Apply modulo at each step to prevent overflow
        long long leftCount = (i - left[i]); // Number of subarrays on the left where arr[i] is the minimum
        long long rightCount = (right[i] - i); // Number of subarrays on the right where is arr[i] is the minimum
        
        // Calculate contribution with proper modulo
        long long count = (leftCount * rightCount) % mod; //total subarrays where arr[i] is the minimum
        long long contribution = (count * arr[i]) % mod; //sum of the minimums where arr[i] is the minimum and multiply it with total subarrays where arr[i] is the minimum
        
        ans = (ans + contribution) % mod; //add the contribution to the final answer with modulo
    }
    
    cout << "Total Sum of Subarray Minimums: " << ans << endl;
    return ans;  // Added return statement
}

int main(){
    vector<int> arr = {3, 1, 2, 2, 4};
    int result = sumSubarrayMins(arr);
    return 0;
}