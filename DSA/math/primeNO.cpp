#include <iostream>
#include <bits/stdc++.h>
//Problem Statement: Given an integer N, check whether it is prime or not. A prime number is a number that is only divisible by 1 and itself and the total number of divisors is 2.


using namespace std;
void printdivisor(int n){
    vector<int>list;
    int count=0;
    //6*6<=36 true
    //7*7<=36 flase   loop will stop
    for(int i=1;i*i<=n;i++){
        if(n%i==0){ //36%3==0 true then 3 will store in list
            count++;
            list.push_back(i); //i will store in list one next one

            if((n/i)!=i){  //then 36/3=12 !=i true the 12 will store in list
                count++;
                list.push_back(n/i); // i will store in list one next one
            }
        }
    }
    if(count==2)
       cout<<"number is prime";
       else
         cout<<"number is not prime";
         cout<<endl;    
    sort(list.begin(),list.end());//this will sort list in ascensing order
    cout<<"Divisor of : "<< n <<endl; 
    for(auto it:list)cout<<it<<"\t";  //print the list vector
}

int printPrimeFactors(int n) {
    int count=0;
    //6*6<=36 true
    //7*7<=36 flase   loop will stop
    for(int i=1;i*i<=n;i++){
        if(n%i==0){ //36%3==0 true then 3 will store in list
            count++;

            if((n/i)!=i){  //then 36/3=12 !=i true the 12 will store in list
                count++;
             }
        }   
    }
    return count;
}

int main(){
    int n;
    cout<<"enter your number";
    cin>>n;
    
    printdivisor(n);
    cout<<endl;
    for(int i = 2 ; i < n ; i++){
        if( printPrimeFactors(i) == 2 )
            cout<<i<<"\t";
    }

    return 0;
}