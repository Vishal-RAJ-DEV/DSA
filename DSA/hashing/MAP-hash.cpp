#include <iostream>
#include <bits/stdc++.h>
using namespace std;
int main()
{
    int n;
    cout << "enter the size of array" << endl;
    cin >> n;
    cout << "enter the elements of array" << endl;
    int arr[n];
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }

    // precompute
    map<int, int> mpp; //first int store the number and second int  store the frequency of that number
    for (int i = 0; i < n; i++)
    {
        mpp[arr[i]]++; //indicis are the number and the value is the frequency of that number in the array and 
    }

    //iterate in the map 
    for(auto i:mpp){
        cout<<i.first<<"="<<i.second<<endl;
    }

    int q;
    cout << "enter the number of queries" << endl;
    cin >> q;
    cout << "enter the number to be searched" << endl;
    while (q--)
    {
        int number;
        cin >> number;
        // fetch
        cout << mpp[number] << endl;
    }
    return 0;
}