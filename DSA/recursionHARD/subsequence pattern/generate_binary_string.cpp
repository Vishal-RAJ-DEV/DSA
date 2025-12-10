#include <iostream>
#include <bits/stdc++.h>
using namespace std;

//basic algorithm is first generate binary strings where '0'  and when the '000' is added then go back by return statement and add '1' only if the last character is '0' or string is empty to avoid consecutive 1s
//this will create two part of recursion tree one where '0' is added and other where '1' is added only if last character is '0' or string is empty
void generateBinaryStrings( int n , string str , vector<string> &result){
    if( str.size() == n){
        result.push_back(str);
        return;
    }
     generateBinaryStrings( n , str + '0' , result);

     if( str.empty() || str.back() == '0'){ //this is other recursive part where '1' is added only if the last character is '0' or string is empty
        generateBinaryStrings( n , str + '1' ,  result);
     }
}
int main(){
    int n;
    cin>>n;
    vector<string> result;
    string str="";
    generateBinaryStrings(n, str, result);
    for(auto &it : result){
        cout<<it<<endl;
    }
    return 0;
}

// //Complexity Analysis:
// Time Complexity: O(φⁿ) where φ ≈ 1.618 (Golden Ratio)

// Each valid string generation takes O(n) time
// Number of valid strings follows Fibonacci sequence
// Space Complexity: O(n) for recursion depth

/*
                    generateBinaryStrings(3, "", result)
                                    |
                        ┌───────────┴───────────┐
                        │                       │
                   Add '0'                 Add '1' (allowed: empty string)
                        │                       │
        generateBinaryStrings(3, "0", result)   generateBinaryStrings(3, "1", result)
                        │                       │
            ┌───────────┴───────────┐          │ (no '1' after '1')
            │                       │          │
       Add '0'                 Add '1'        Add '0'
            │               (last='0')         │
generateBinaryStrings    generateBinaryStrings  generateBinaryStrings
   (3, "00", result)        (3, "01", result)    (3, "10", result)
            │                       │                      │
    ┌───────┴───────┐       ┌───────┴───────┐      ┌─────┴─────┐
    │               │       │               │      │           │
Add '0'        Add '1'   Add '0'        Add '1'  Add '0'   Add '1'
    │        (last='0')     │        (last='1')    │     (last='0')
    │               │       │          (blocked)   │           │
   "000"          "001"    "010"        (no call) "100"      "101"
 (len=3)        (len=3)  (len=3)                 (len=3)    (len=3)
   RETURN        RETURN   RETURN                  RETURN     RETURN
*/

/*

Step-by-Step Call Stack Execution:
Level 1: Initial Call
Call: generateBinaryStrings(3, "", result)
- str.size() = 0, n = 3 → continue
- Add '0': Call generateBinaryStrings(3, "0", result)
- str.empty() = true → can add '1'
- Add '1': Call generateBinaryStrings(3, "1", result)

Level 2: Branch 1 - "0"
Call: generateBinaryStrings(3, "0", result)
- str.size() = 1, n = 3 → continue
- Add '0': Call generateBinaryStrings(3, "00", result)
- str.back() = '0' → can add '1'
- Add '1': Call generateBinaryStrings(3, "01", result)


Level 2: Branch 2 - "1"
Call: generateBinaryStrings(3, "1", result)
- str.size() = 1, n = 3 → continue
- Add '0': Call generateBinaryStrings(3, "10", result)
- str.back() = '1' → CANNOT add '1' (consecutive 1s blocked)


Level 3: Branch 1.1 - "00"
Call: generateBinaryStrings(3, "00", result)
- str.size() = 2, n = 3 → continue
- Add '0': Call generateBinaryStrings(3, "000", result)
- str.back() = '0' → can add '1'
- Add '1': Call generateBinaryStrings(3, "001", result)

Level 3: Branch 1.2 - "01"
Call: generateBinaryStrings(3, "01", result)
- str.size() = 2, n = 3 → continue
- Add '0': Call generateBinaryStrings(3, "010", result)
- str.back() = '1' → CANNOT add '1' (consecutive 1s blocked)


Level 3: Branch 2.1 - "10"
Call: generateBinaryStrings(3, "10", result)
- str.size() = 2, n = 3 → continue
- Add '0': Call generateBinaryStrings(3, "100", result)
- str.back() = '0' → can add '1'
- Add '1': Call generateBinaryStrings(3, "101", result)


Level 4: Base Cases (Length = 3)
Call: generateBinaryStrings(3, "000", result)
- str.size() = 3 = n → BASE CASE
- result.push_back("000")
- RETURN ↑

Call: generateBinaryStrings(3, "001", result)
- str.size() = 3 = n → BASE CASE  
- result.push_back("001")
- RETURN ↑

Call: generateBinaryStrings(3, "010", result)
- str.size() = 3 = n → BASE CASE
- result.push_back("010")  
- RETURN ↑

Call: generateBinaryStrings(3, "100", result)
- str.size() = 3 = n → BASE CASE
- result.push_back("100")
- RETURN ↑

Call: generateBinaryStrings(3, "101", result)
- str.size() = 3 = n → BASE CASE
- result.push_back("101")
- RETURN ↑
*/