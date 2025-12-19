#include <iostream>
#include <bits/stdc++.h>
using namespace std;

/*
Example 1:
Input:
 k = 3, n = 7
Output:
 [[1, 2, 4]]
Explanation:

1 + 2 + 4 = 7
There are no other valid combinations.

Example 2:
Input:
 k = 3, n = 9
Output:
 [[1, 2, 6],[1, 3, 5],[2, 3, 4]]
Explanation:

1 + 2 + 6 = 9
1 + 3 + 5 = 9
2 + 3 + 4 = 9
There are no other valid combinations.
*/

void generate( int idx ,int k , int target , vector<int> & subset , vector<vector<int>> & result){
    //base case : if the target is 0 and size of the subset is k then we have found a valid combination
    if( target == 0 &&  subset.size() == k){
        result.push_back(subset);
        cout<<"[ ";
        for( auto &it : subset){
            cout<<it<<" ";
        }
        cout<<"]"<<endl;
        return;
    }

    //if target becomes negative or size if the subset exceeds k means more than k elements then reutrn 
    if( target < 0 || subset.size() > k) return ;

    //so here we will try all the elements from idx to 9 because the elements are from 1 to 9
    //and inside the loop we will include the element and call the function recursively with next index and reduced target 
    //this will crate all the combinations for the each index 
    for( int i = idx ; i<=9 ;i++){
        if( i > target ) break ; //no need to proceed further if i exceeds the target
        subset.push_back(i);
        generate( i + 1 , k , target - i , subset , result);
        subset.pop_back(); //backtrack
        //after backtracking we will try the next element in the loop 
    }
} 
int main(){

    int k = 3; //number of elements in the combination
    int target = 7; //target sum

    vector<int> subset;
    vector<vector<int>> result;
    generate( 1,  k , target , subset , result);
    return 0;
}
// generate(1, 3, 7, [], result) [idx=1, k=3, target=7, subset=[]]
// │
// ├── i=1: subset.push_back(1) → [1]
// │   │    generate(2, 3, 6, [1], result) [idx=2, k=3, target=6, subset=[1]]
// │   │    │
// │   │    ├── i=2: subset.push_back(2) → [1,2]
// │   │    │   │    generate(3, 3, 4, [1,2], result) [idx=3, k=3, target=4, subset=[1,2]]
// │   │    │   │    │
// │   │    │   │    ├── i=3: subset.push_back(3) → [1,2,3]
// │   │    │   │    │   │    generate(4, 3, 1, [1,2,3], result) [idx=4, k=3, target=1, subset=[1,2,3]]
// │   │    │   │    │   │    Check: target=1>0 ✓, subset.size()=3==k ✗ (not 0 target)
// │   │    │   │    │   │    Loop i=4 to 9:
// │   │    │   │    │   │    ├── i=4: subset.push_back(4) → [1,2,3,4] (size=4>k=3) → RETURN
// │   │    │   │    │   │    └── Loop breaks due to size>k condition
// │   │    │   │    │   │    subset.pop_back() → [1,2,3] becomes [1,2]
// │   │    │   │    │   
// │   │    │   │    ├── i=4: subset.push_back(4) → [1,2,4]
// │   │    │   │    │   │    generate(5, 3, 0, [1,2,4], result) [idx=5, k=3, target=0, subset=[1,2,4]]
// │   │    │   │    │   │    Check: target=0 ✓ AND subset.size()=3==k ✓ → SUCCESS! [1,2,4]
// │   │    │   │    │   │    result.push_back([1,2,4])
// │   │    │   │    │   │    Print: [ 1 2 4 ]
// │   │    │   │    │   │    RETURN
// │   │    │   │    │   │    subset.pop_back() → [1,2,4] becomes [1,2]
// │   │    │   │    │   
// │   │    │   │    ├── i=5: if(5 > target=4) break → LOOP BREAKS
// │   │    │   │    │   (No need to try i=6,7,8,9 as they're all > target)
// │   │    │   │    │
// │   │    │   │    subset.pop_back() → [1,2] becomes [1]
// │   │    │   │
// │   │    │   ├── i=3: subset.push_back(3) → [1,3]
// │   │    │   │   │    generate(4, 3, 3, [1,3], result) [idx=4, k=3, target=3, subset=[1,3]]
// │   │    │   │   │    │
// │   │    │   │   │    ├── i=4: if(4 > target=3) break → LOOP BREAKS
// │   │    │   │   │    │   (4 > 3, so no valid combinations possible)
// │   │    │   │   │    │
// │   │    │   │   │    subset.pop_back() → [1,3] becomes [1]
// │   │    │   │   
// │   │    │   ├── i=4: subset.push_back(4) → [1,4]
// │   │    │   │   │    generate(5, 3, 2, [1,4], result) [idx=5, k=3, target=2, subset=[1,4]]
// │   │    │   │   │    │
// │   │    │   │   │    ├── i=5: if(5 > target=2) break → LOOP BREAKS
// │   │    │   │   │    │   (5 > 2, so no valid combinations possible)
// │   │    │   │   │    │
// │   │    │   │   │    subset.pop_back() → [1,4] becomes [1]
// │   │    │   │   
// │   │    │   ├── i=5: subset.push_back(5) → [1,5]
// │   │    │   │   │    generate(6, 3, 1, [1,5], result) [idx=6, k=3, target=1, subset=[1,5]]
// │   │    │   │   │    │
// │   │    │   │   │    ├── i=6: if(6 > target=1) break → LOOP BREAKS
// │   │    │   │   │    │   (6 > 1, so no valid combinations possible)
// │   │    │   │   │    │
// │   │    │   │   │    subset.pop_back() → [1,5] becomes [1]
// │   │    │   │   
// │   │    │   └── i=6: if(6 > target=6) break → CONTINUE (6 == 6)
// │   │    │       │    subset.push_back(6) → [1,6]
// │   │    │       │    generate(7, 3, 0, [1,6], result) [idx=7, k=3, target=0, subset=[1,6]]
// │   │    │       │    Check: target=0 ✓ BUT subset.size()=2≠k=3 ✗ → RETURN
// │   │    │       │    subset.pop_back() → [1,6] becomes [1]
// │   │    │       
// │   │    │    subset.pop_back() → [1] becomes []
// │   │    
// │   ├── i=2: subset.push_back(2) → [2]
// │   │   │    generate(3, 3, 5, [2], result) [idx=3, k=3, target=5, subset=[2]]
// │   │   │    │
// │   │   │    ├── i=3: subset.push_back(3) → [2,3]
// │   │   │    │   │    generate(4, 3, 2, [2,3], result) [idx=4, k=3, target=2, subset=[2,3]]
// │   │   │    │   │    │
// │   │   │    │   │    ├── i=4: if(4 > target=2) break → LOOP BREAKS
// │   │   │    │   │    │   (4 > 2, impossible to reach target=2 with remaining numbers)
// │   │   │    │   │    │
// │   │   │    │   │    subset.pop_back() → [2,3] becomes [2]
// │   │   │    │   
// │   │   │    ├── i=4: if(4 > target=5) continue → CONTINUE (4 < 5)
// │   │   │    │   │    subset.push_back(4) → [2,4]
// │   │   │    │   │    generate(5, 3, 1, [2,4], result) [idx=5, k=3, target=1, subset=[2,4]]
// │   │   │    │   │    │
// │   │   │    │   │    ├── i=5: if(5 > target=1) break → LOOP BREAKS
// │   │   │    │   │    │   (5 > 1, impossible)
// │   │   │    │   │    │
// │   │   │    │   │    subset.pop_back() → [2,4] becomes [2]
// │   │   │    │   
// │   │   │    ├── i=5: subset.push_back(5) → [2,5]
// │   │   │    │   │    generate(6, 3, 0, [2,5], result) [idx=6, k=3, target=0, subset=[2,5]]
// │   │   │    │   │    Check: target=0 ✓ BUT subset.size()=2≠k=3 ✗ → RETURN
// │   │   │    │   │    subset.pop_back() → [2,5] becomes [2]
// │   │   │    │   
// │   │   │    └── i=6,7,8,9: if(i > target=5) break when i=6 → LOOP BREAKS
// │   │   │    
// │   │   │    subset.pop_back() → [2] becomes []
// │   │   
// │   ├── i=3: subset.push_back(3) → [3]
// │   │   │    generate(4, 3, 4, [3], result) [idx=4, k=3, target=4, subset=[3]]
// │   │   │    │
// │   │   │    ├── i=4: subset.push_back(4) → [3,4]
// │   │   │    │   │    generate(5, 3, 0, [3,4], result) [idx=5, k=3, target=0, subset=[3,4]]
// │   │   │    │   │    Check: target=0 ✓ BUT subset.size()=2≠k=3 ✗ → RETURN
// │   │   │    │   │    subset.pop_back() → [3,4] becomes [3]
// │   │   │    │   
// │   │   │    └── i=5,6,7,8,9: if(i > target=4) break when i=5 → LOOP BREAKS
// │   │   │    
// │   │   │    subset.pop_back() → [3] becomes []
// │   │   
// │   ├── i=4: subset.push_back(4) → [4]
// │   │   │    generate(5, 3, 3, [4], result) [idx=5, k=3, target=3, subset=[4]]
// │   │   │    │
// │   │   │    └── i=5,6,7,8,9: if(5 > target=3) break → LOOP BREAKS
// │   │   │    
// │   │   │    subset.pop_back() → [4] becomes []
// │   │   
// │   └── i=5,6,7,8,9: if(i > target=7) continue until i=8 → break when i=8
// │       (i=5: 5<7 ✓, i=6: 6<7 ✓, i=7: 7<7 ✓, i=8: 8>7 ✗ break)
// │       But these all lead to impossible combinations due to insufficient remaining sum

// Final Result: [[1,2,4]]    