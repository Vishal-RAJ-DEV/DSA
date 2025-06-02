#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class Node{
    public:
    int data; //data of the node 
    Node * next;
    Node(int data1, Node * next1){
        data = data1;
        next = next1;
    }
    Node(int data1){  //another constructure for node so we don't have to defined next as null.
        data = data1;
        next = nullptr;
    }
    
}; 

int main(){
    vector<int> a= {1 ,2 ,3,4 ,5 ,6, 7 , 8,9,10};
    Node * y = new Node(a[0]);
    cout<<y->data<<endl; // here y is the head of the linked  list  

  
    return 0;
}