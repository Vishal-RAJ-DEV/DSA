#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class Stack
{
    int *arr;
    int top;
    int size;

public:
    Stack()
    {
        top = -1;//
        size = 10; //default size of stack
        arr = new int[size];
    }
    void Push(int x){
        if(top == size - 1) return; //if stack is full, do not push
        top++;
        arr[top] = x;
    }
    int Pop(){
        int x; //variable to store popped element
        if(top == -1) return -1;
        x = arr[top]; 
        top--; //decrement top to remove the element
        return x;
    }
    int Top(){
        if(top == -1) return -1; //if stack is empty, return -1
        return arr[top];
    }
    int Size(){
        return top + 1;
    }

} ;

int main()
{
    Stack s;
    s.Push(5);
    s.Push(7);
    s.Push(11);
    cout<<"top element of the stack is: "<<s.Top()<<endl;
    cout<<"size of the stack is: "<<s.Size()<<endl;
    cout<<"popped element is: "<<s.Pop()<<endl;
    cout<<"top element of the stack after pop is: "<<s.Top()<<endl;
    cout<<"size of the stack after pop is: "<<s.Size()<<endl;
    s.Push(3);
    cout<<"top element of the stack after pushing 3 is: "<<s.Top()<<endl;
    cout<<"size of the stack after pushing 3 is: "<<s.Size()<<endl;

    return 0;
}

//Time complexity of Push, Pop, Top and Size is O(1) as we are just accessing the array elements and not traversing through the stack.
//Space complexity is O(n) where n is the size of the stack as we are using an array to store the elements of the stack.