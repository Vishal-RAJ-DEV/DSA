#include <iostream>
#include <bits/stdc++.h>
using namespace std;
int main(){
    string s;
    cout<<"enter your string"<<endl;
    cin>>s;

    //precompute
    int hash[26]={0}; //also use hash[256] for all ascii values another way to store
    for(int i=0;i<s.size();i++){
        hash[s[i]-'a']++;   //also use hash[s[i]]++;  another way to store

    }

    int q;
    cout<<"enter no of qureies"<<endl;
    cin>>q;
    while(q--){
        char ch;
        cin>>ch;
        //fetch
        cout<<hash[ch-'a']<<endl; //also use hash[ch]  another way to fetch
    }
    return 0;
}