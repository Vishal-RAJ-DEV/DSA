#include <iostream>
#include <bits/stdc++.h>
using namespace std;
//this is for the grid problem but the approach is same for the array problem also
class Solution {
public:
    vector<int> findMissingAndRepeatedValues3(vector<vector<int>>& grid) {
        //we use the hash map to solve this question 
        int n = grid.size();
        int size = n * n ;
        //hash map to store the frequency of the element
        vector<int>hash( size + 1, 0 );

        for( int i= 0 ; i<n ; i++){
            for( int j = 0 ; j < n ; j++){
                hash[grid[i][j]]++;
            }
        }

        //now check the frequency in the hash map
        int a = -1, b = -1;
        for( int i = 1 ; i <= size ; i++){
            if( hash[i] == 2){ //duplicate 
                a = i;
            }else if(hash[i] == 0){ //missing 
                b = i;
            }
        }

        return { a , b};
    }
};



//this the brute force approoch 
vector<int>findMissingAndDuplicate2( vector<int>& arr){
    int missing = -1, duplicate = -1;
    for( int i = 1 ;  i <= arr.size() ; i++){
        int count = 0;
        for( int j = 0 ; j < arr.size() ; j++){
            if( arr[j] == i ) count++;
        }
        if( count == 0) missing = i;
        else if( count == 2) duplicate = i;
    }
    return {missing, duplicate};
}

//using the hash map
vector<int> findMissingAndDuplicate1( vector<int>& arr){
    int missing = -1 , duplicate = -1;
    int hash[arr.size() + 1] = { 0 }; //declare a hash array of of the size of the input array + 1 and initialize it with 0
    for( int i = 0 ; i < arr.size() ; i++){
        hash[arr[i]]++;
    }
    for( int i = 1 ; i <= arr.size() ; i++){
        if( hash[i] == 0 ) missing = i;
        else if( hash[i] == 2 ) duplicate = i;

        if( missing != -1 && duplicate != -1) break; //if both missing and duplicate are found, we can break early  
    }
    return {missing, duplicate};
}

//using the formula of sum and sum of squares
vector<int>findMissingAndDuplicate( vector<int>& arr){
    int n = arr.size();
    long long sum = 0 , sumOfSquares = 0;
    for( int i = 0 ; i < n ; i++){
        sum += arr[i];
        sumOfSquares += (long long)arr[i] * arr[i]; //cast to long long to prevent overflow
    }
    long long expectedSum = (long long)n * (n + 1) / 2; //sum of first n natural numbers
    long long expectedSumOfSquares = (long long)n * (n + 1) * (2 * n + 1) / 6; //sum of squares of first n natural numbers

    long long diff = expectedSum - sum; //missing - duplicate
    long long diffOfSquares = expectedSumOfSquares - sumOfSquares; //missing^2 - duplicate^2

    long long sumOfNumbers = diffOfSquares / diff; //missing + duplicate
    //its like you have two equations:
    // x^2 - y^2 = diffOfSquares  (1) and this is equivalent to (x - y)(x + y) = diffOfSquares
    // so ( x + y ) = diffOfSquares / (x - y) = diffOfSquares / diff  (2)
    // from (1) we can express x as x = y + diff
    int missing = (diff + sumOfNumbers) / 2; //missing = (diff + sumOfNumbers) / 2
    int duplicate = missing - diff; //duplicate = missing - diff
    return {missing, duplicate};
}

int main(){
    vector<int> arr = {1,2,3,3,4,6,7,8};
    vector<int> numbers =  findMissingAndDuplicate(arr);
    cout<<"missing number is"<<"\n"<<numbers[0]<<"\n";
    cout<<"duplicate number is"<<"\n"<<numbers[1]<<"\n";
    return 0;
}
