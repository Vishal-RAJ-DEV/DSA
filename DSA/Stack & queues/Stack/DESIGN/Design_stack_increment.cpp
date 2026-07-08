#include <iostream>
#include <bits/stdc++.h>
using namespace std;

//using the array to implement the stack and increment the first k elements in the stack by val
class CustomStack {
public:
    int maxsize ;
    int currsize;
    vector<int>arr;
    CustomStack(int maxSize) {
        maxsize = maxSize;
        arr.resize(maxsize);
        currsize = 0;
    }
    
    void push(int x) {
        if( currsize == maxsize) return;
        arr[currsize] = x;
        currsize++;
    }
    
    int pop() {
        if( currsize == 0 ) return -1;
        currsize--;
        int x = arr[currsize];
        return x;
    }
    
    void increment(int k, int val) {
        int limit = min( k , currsize);
        for(int i = 0 ; i < limit; i++){
            arr[i] += val;
        }
    }
};

/**
 * Your CustomStack object will be instantiated and called as such:
 * CustomStack* obj = new CustomStack(maxSize);
 * obj->push(x);
 * int param_2 = obj->pop();
 * obj->increment(k,val);
 */

class CustomStack {
public:
    vector<int> stack;
    int top;

    CustomStack(int maxSize) {
        stack.resize(maxSize);
        top = -1;
    }

    void push(int x) {
        if (top < stack.size() - 1) {
            top++;
            stack[top] = x;
        }
    }

    int pop() {
        if (top != -1) {
            return stack[top--];
        }
        return -1;
    }

    void increment(int k, int val) {
        for (int i = 0; i < min(k, top + 1); i++) {
            stack[i] += val;
        }
    }
};