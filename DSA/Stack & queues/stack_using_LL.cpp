#include <iostream>
#include <bits/stdc++.h>
using namespace std;

struct StackNode{
    public:
    int data; //data of the node 
    StackNode * next;

    StackNode(int data1){  //another constructure for node so we don't have to defined next as null.
        data = data1;
        next = nullptr;
    }
    
};

struct Stack{
    StackNode * Top;
    int size;
    Stack(){
        Top = nullptr;
        size = 0;
    }

    void Push(int x ){
        StackNode * newEle = new StackNode(x);
        newEle->next = Top;
        Top = newEle;
        cout<<"Element Pushed: "<<newEle->data<<" "<<endl;
        size ++;

    }
    int stackPop(){
        if(Top == nullptr) return -1;
        int topData =  Top->data;
        StackNode * temp = Top;
        Top = Top->next;
        delete temp;
        size--;
        return topData;

    }
    int stackPeek(){
        if(Top == nullptr) return -1;
        return Top->data;
    }
    int stackSize(){
        return size;
    }
    void printStack(){
        StackNode * current  = Top;
        while(current !=  nullptr){
            cout<<current->data<<" ";
            current = current->next;
        }
    }
};


int main(){
    Stack s;
    s.Push(12);
    s.Push(34);
    s.Push(86);
    s.Push(65);
    s.printStack();
    s.stackPop();
    cout<<endl;
    s.printStack();

    return 0;
}