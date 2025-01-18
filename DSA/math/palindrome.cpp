#include <iostream>
using namespace std;
//Problem Statement: Given an integer N, return true if it is a palindrome else return false.
//A palindrome is a number that reads the same backward as forward. For example, 121, 1331, and 4554 are palindromes because they remain the same when their digits are reversed.

int main(){
    int n;
    cin>>n;
    int reverse=0;
    int dup=n;

    while(n>0){
        int lastdigit=n%10;
        reverse=(reverse*10)+lastdigit;
        
        n=n/10;
    }
    cout<<"reverse number is "<<reverse<<endl;
    if(dup==reverse)
        cout<<"number is palindrome";
    
    else
        cout<<"number is not palindrome";
    
    return 0;
}