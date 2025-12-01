#include <iostream>
#include <bits/stdc++.h>
using namespace std;
void reverseUsingstack(vector<int>& arr){
    stack<int> s;
    for( auto & it : arr ){
        s.push(it);
    }
    for( int i = 0 ; i < arr.size() ; i++ ){
        arr[i] = s.top();
        s.pop();
    }
}
int main(){
    vector<int> arr = {1, 2, 3, 4, 5};
    reverseUsingstack(arr);
    for(int i : arr){
        cout << i << " ";
    }
    cout << endl;
    return 0;
}