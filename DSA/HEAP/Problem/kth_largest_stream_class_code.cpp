#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class KthLargest {
private:
    //min heap priority queue
    priority_queue<int , vector<int> , greater<int>> pq;
    int gk;
public:
    KthLargest(int k, vector<int>& nums) {
        gk = k;
        for( int num : nums){
            pq.push(num);
            //if heap size is greater than k , remove the element 
            //at top there of the pq , kth largest value will be there 
            //so kth + 1 elemets comes and min heap rearange and put the smallest on the top 
            //at last top 3 largest element will remain in the pq 
            //and at top smallest one which is kth smallest
            if( pq.size() > k ) pq.pop();
        }
    }
    
    int add(int val) {
        pq.push(val);
        if( pq.size() > gk) pq.pop();
        return pq.top();
        
    }
};


int main(){
    vector<int> arr = {3, 2, 1, 5, 6, 4};
    int k = 2;
    KthLargest kthLargest(k, arr);
    cout << "Kth largest element using class: " << kthLargest.add(7) << endl;

    return 0;
}
