#include <iostream>
#include <bits/stdc++.h>
using namespace std;

void insertBottom( stack <int> &st , int val){
    if(st.empty()){
        st.push(val);
        return;
    }
    int top = st.top();  //store the top element in a variable so that we can push the latest ele in the bottom and top ele in the top
    st.pop();
    insertBottom( st , val ); //call until the stack is empty to reach the bottom of the stack
    st.push( top);
}
void reverseStack( stack <int > st){
    if(st.empty()) return ;
    
    int top = st.top();
    st.pop();
    reverseStack(st);

    insertBottom( st , top);
}
int main(){
    stack<int> st;
    st.push(1);
    st.push(2);
    st.push(3);
    st.push(4);
    st.push(5);
    reverseStack(st);
    cout<<"Reversed stack is: "<<endl;
    while(!st.empty()){
        cout<<st.top()<<endl;
        st.pop();
    }
    

    return 0;
}