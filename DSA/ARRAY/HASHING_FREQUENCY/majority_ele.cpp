
// Find the Majority Element that occurs more than N/2 times

#include <bits/stdc++.h>
using namespace std;

int majorityElement(vector<int> v) {

    //size of the given array:
    int n = v.size();

    //declaring a map:
    map<int, int> mpp;

    //storing the elements with its occurnce:
    for (int i = 0; i < n; i++) {
        mpp[v[i]]++;
    }

    //searching for the majority element:
    for (auto it : mpp) {
        if (it.second > (n / 2)) {
            return it.first;
        }
    }

    return -1;
}
//optimal approach : also called as Boyer-Moore Voting Algorithm
//where we votes for the majority element and if we get a different element then we decrease the vote and if the vote becomes 0 then we take that element as the majority element and at the end we will get the majority element in el but we have to check if it is the majority element or not by counting its occurence again and checking if it is greater than n/2 or not
//time complexity O(n)
//space complexity O(1)
int majorityElement1(vector<int> v) {

    //size of the given array:
    int n = v.size();
    int cnt = 0; // count
    int el; // Element

    //applying the algorithm: here we are taking the first element as the assumption that it is the majotity element 
    // and then we are counting the number of times it occurs and it decreses when another element ocuurs
    //if the count becomes 0 again the we take that element as the majority element where count becomes 0 
    //at the end we will get the majority element in el but we have to check if it is the majority element or not by counting its occurence again and checking if it is greater than n/2 or not
    for (int i = 0; i < n; i++) {
        if (cnt == 0) {
            cnt = 1;
            el = v[i];
        }
        else if (el == v[i]) cnt++;
        else cnt--;
    }
    //  cout<<el<<endl;
    //  cout<<cnt<<endl;
    //checking if the stored element
    // is the majority element:verfication step that the element we got is the majority element or not by counting its occurence again and checking if it is greater than n/2 or not
    int cnt1 = 0;
    for (int i = 0; i < n; i++) {
        if (v[i] == el) cnt1++; // counting the occurence of the element we got as majority element
    }

    if (cnt1 > (n / 2)) return el; //it should be greater than n/2 to be the majority element
    return -1;
}

int main()
{
    vector<int> arr = {2, 2, 1, 1, 1, 2, 2};
    int ans = majorityElement1(arr);
    cout << "The majority element is: " << ans << endl;
    return 0;
}


