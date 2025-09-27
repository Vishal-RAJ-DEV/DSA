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

Node* reverseLinkList(Node* head, int left, int right) {
    // Handle edge case: empty list or single node
    if(head == nullptr || head->next == nullptr) return head;

    // Create a dummy node to handle edge cases (like reversing from first node)
    Node *dummy = new Node(-1);
    dummy->next = head;
    Node *prev = dummy;

    // Move prev to the node just before the reversal starts
    for(int i = 1; i < left; i++) {
        prev = prev->next;
    }

    // curr points to the first node that will be reversed (at position 'left')
    Node *curr = prev->next;
    Node *nextnode = nullptr;

    // The actual reversal process
    for(int i = 0; i < right - left; i++) {
        nextnode = curr->next;       // Store the next node
        curr->next = nextnode->next; // Point current to nextnode's next (skip nextnode)
        nextnode->next = prev->next; // Point nextnode to prev's next
        prev->next = nextnode;       // Point prev to nextnode
    }

    // Return the head of the modified list
    return dummy->next;
}





int main(){
    vector<int> arr = {1,2,3,4,5,6,7};
    Node * head = convertArr2All(arr);
    print(head);

    cout<<"After reversing the linklist :  "<<endl;
    head = reverseLinkList(head,2,4);
    print(head);
    return 0;
}