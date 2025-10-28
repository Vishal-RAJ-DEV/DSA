#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class MinStack {
public:
    stack <int> st;
    stack <int> minSt;
    MinStack() {
        
    }
    
    void push(int val) {
        st.push(val);
        if(minSt.empty() ||  val <= minSt.top()){
            minSt.push(val);
        }else{
            minSt.push(minSt.top());
        }
    }
    
    void pop() {
        st.pop();
        minSt.pop();
    }
    
    int top() {
        return st.top();
    }
    
    int getMin() {
        return minSt.top();
    }
};
int main(){
    MinStack* obj = new MinStack();
    obj->push(-2);
    obj->push(0);
    obj->push(-3);
    cout << obj->getMin(); 
    cout<<endl;  // Returns -3
    obj->pop();
    cout << obj->top();
    cout<<endl;      // Returns 0
    cout << obj->getMin();   // Returns -2
    return 0;
}
