#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class MedianFinder {
private:
        priority_queue<int , vector<int>> l_max_h; //left max heap
        priority_queue<int , vector<int> , greater<int>>r_min_h;//right min heap

public:
    MedianFinder() {
        
    }
    
    void addNum(int num) {
        //when the left heap is empty and num is lesser than left heap 
        if(l_max_h.empty() || num <= l_max_h.top()){
            l_max_h.push(num);
        }else{
            r_min_h.push(num);
        }

        //balance the size of the both the heap
        //always the left heap should be greater then right heap by the differnce of 1
        //left heap should have more element than right heap

        //maintain the right heap size 
        //if it less then left heap even if size + 1 then push in the right part
        //eg left = 4 and right = 2 , so right + 1 = 3 is lesser then left so balanced it 
        if( l_max_h.size() > r_min_h.size() + 1 ){
            r_min_h.push(l_max_h.top()); //push the top ele of left max heap
            l_max_h.pop();
        }
        //if the left heap is lesser then push the right top element
        else if ( l_max_h.size() < r_min_h.size()){
            l_max_h.push(r_min_h.top());
            r_min_h.pop();
        }


    }
    
    double findMedian() {
        //now left top have and right top is the centre element ( mediam)
        //and if left part is greater then elements are odd size and 
        //-> and left top is single median 
        //and when left and rigth is same size , then 
        //->both left and right top are median
        if( l_max_h.size() == r_min_h.size()){
            double mean = (l_max_h.top() + r_min_h.top()) / 2.0;
            return mean;
        }
        else return l_max_h.top();
        
    }
};


int main(){
    MedianFinder mf; // create median finder instance
    mf.addNum(1); // add number 1
    mf.addNum(2); // add number 2
    cout << "Current median: " << mf.findMedian() << endl; // should print 1.5
    mf.addNum(3); // add number 3
    cout << "Current median: " << mf.findMedian() << endl; // should print 2
    return 0;
}
