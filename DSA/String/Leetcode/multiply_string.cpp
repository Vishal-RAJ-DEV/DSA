#include <iostream>
#include <bits/stdc++.h>
using namespace std;
 string multiply(string num1, string num2) {
        if(num1 == "0" ||  num2 == "0") return "0";
        int n = num1.size();
        int m = num2.size();
        vector<int> res (n + m , 0);
        for(int i = n-1 ; i>=0 ;i--){ //traverse the from the back 
            for(int j = m-1; j>=0;j--){ //traverse form the back 
                int mul = (num1[i]  - '0') * (num2[j] - '0');//store the multiplication 
                int sum = mul + res[i + j + 1]; //add the previoust carry 

                res[i+j + 1] = sum % 10; //extract the carry form the sum 
                res[i+j] += sum / 10; //store the value in the res 
            }
        }
        string result ;
        int i = 0;
        //skip the leading zeroes by this loop
        while(i<res.size() && res[i] == 0 ) i++;
        for(; i<res.size() ;i++)result.push_back(res[i] + '0');
        return result.empty() ? "0" : result;
    }
int main(){
    string num1 = "123";
    string num2 = "456";
    cout << multiply(num1, num2) << endl; // Output: 56088  
    return 0;
}