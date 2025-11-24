#include <iostream>
#include <bits/stdc++.h>
using namespace std;


void insertInSortedStack(stack<int> & st , int val ){
    if(st.empty() || st.top() <= val){ //if the stack is empty or the top element is less than or equal to the val then we can push the val in the stack
        st.push(val);
        return ;
    }
    int top = st.top();
    st.pop();
    insertInSortedStack(st , val);
    //at last when the val is inserted in the correct position then we will push back the elements which was poped earlier

    st.push(top);
}
//sort the stack in the ascending order using recursion
void sortStack (stack<int> &st ){
    if(st.empty()) return;

    //pop all the elements from the stack in every recursive call and store the top element in a variable so that we can use that top element to insert it in the sorted stack
    int top = st.top();
    st.pop();

    sortStack(st);  //call until the stack is empty

    insertInSortedStack(st , top); //then use the top element to insert it in the sorted stack
}
int main(){
    stack<int> st;
    st.push(34);
    st.push(3);
    st.push(31);
    st.push(98);
    st.push(92);
    st.push(23);
    sortStack(st);
    cout<<"sorted stack is: "<<endl;
    while(!st.empty()){
        cout<<st.top()<<endl;
        st.pop();
    }
    return 0;
}
