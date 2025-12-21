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
Node * convertArr2All (vector<int>&a){ //to convert the array to linklist  
    Node * head = new Node(a[0]);
    Node * mover = head;   //head is the first node of the linked list and mover is a pointer that willl point to the current node 
    for(int i = 1;i<a.size();i++){
        Node * temp = new Node(a[i]);
        mover->next = temp; // link the current  node(mover) to the new node (temp)
        mover = temp;  //so the current node (mover) will poiint to the new node (temp)
 
         
    }
    return head;
    
}
Node * print(Node * head){  //to print the linklist 
    while(head!= nullptr){
        cout<<head->data<<" ";
        head = head->next;
    }
    cout<<endl;
}
int helper(Node * & head){
    if( head == nullptr) return 1; //base case if head is null return carry as 1

    int carry = helper( head->next); //recursive call to the next node
    int sum = head->data + carry; //sum of the current node data and carry
    head->data = sum % 10 ; //update the current node data with sum mod 10

    return sum /  10; //return carry for the next node
}
Node * addOneToLL( Node * head ){
    Node * temp  = head;

    int carry = helper( temp);
    if( carry == 1){
        Node * newNode = new Node(1);
        newNode->next = head;
        head = newNode;
    }
    return head;
}
//itreatie approach 

Node * reverseLinkList(Node * head){  //iterative
    if(head == nullptr ||  head->next == nullptr) return head;
    Node * temp = head;
    Node * prev = nullptr;
    while(temp!= nullptr){
        Node * front = temp->next;
        temp->next = prev;
        prev = temp;
        temp = front;
    }

    Node * newHead = prev;
    return newHead;
}

Node * addOneToLLIterateive( Node * head){
    head = reverseLinkList( head);
    Node * temp = head;
    int carry = 1;
    while( temp != nullptr && carry != 0){
        
    }
}


int main(){
    vector<int> arr1 = {1,2,3};
    Node * head1 = convertArr2All(arr1);
    cout<<"Original Linked List: ";
    print(head1);

    head1 = addOneToLL(head1);
    cout<<"Linked List after adding 1: ";
    print(head1);


    
    return 0;
}