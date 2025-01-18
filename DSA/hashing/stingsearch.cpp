#include <iostream>
#include <bits/stdc++.h>
using namespace std;
int main(){
    string s;
    cout<<"enter your string"<<endl;
    cin>>s;

    //precompute
    int hash[26]={0};
    for(int i=0;i<s.size();i++){
        hash[s[i]-'a']++;

    }

    int q;
    cout<<"enter no of qureies"<<endl;
    cin>>q;
    while(q--){
        char ch;
        cin>>ch;
        //fetch
        cout<<hash[ch-'a']<<endl;
    }
    return 0;
}