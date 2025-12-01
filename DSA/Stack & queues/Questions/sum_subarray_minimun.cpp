#include <iostream>
#include <bits/stdc++.h>
using namespace std;

int sumSubarrayMins(vector<int>& arr){
    int n = arr.size();
    stack<int> st;
    vector<int> left(n), right(n);
    
    // Calculate left array
    for(int i = 0; i < n; i++){
        while(!st.empty() && arr[i] < arr[st.top()]) {
            st.pop();
        }
        left[i] = st.empty() ? -1 : st.top();
        st.push(i);
    }
    
    // Clear stack
    while(!st.empty()) st.pop();
    
    // Calculate right array
    for(int i = n - 1; i >= 0; i--){
        while(!st.empty() && arr[i] <= arr[st.top()]){
            st.pop();
        }
        right[i] = st.empty() ? n : st.top();
        st.push(i);
    }
    
    // Calculate sum with proper modulo arithmetic
    long long ans = 0;
    long long mod = 1e9 + 7;  // Changed to long long
    
    for(int i = 0; i < n; i++){
        // Apply modulo at each step to prevent overflow
        long long leftCount = (i - left[i]);
        long long rightCount = (right[i] - i);
        
        // Calculate contribution with proper modulo
        long long count = (leftCount * rightCount) % mod;
        long long contribution = (count * arr[i]) % mod;
        
        ans = (ans + contribution) % mod;
    }
    
    cout << "Total Sum of Subarray Minimums: " << ans << endl;
    return ans;  // Added return statement
}

int main(){
    vector<int> arr = {3, 1, 2, 2, 4};
    int result = sumSubarrayMins(arr);
    return 0;
}