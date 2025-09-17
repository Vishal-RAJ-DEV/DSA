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

Node * RemoveNthNodeEnd(Node * head , int n){
    if(head == nullptr && head->next == nullptr) return head;
   
    Node * fast = head;
    for(int i = 0; i< n ; i++){  //first move the fast pointer n steps ahead and after that move both fast and slow pointer at the same time 
        fast = fast->next; 
    }
    if(fast == nullptr) return head; // if n is greater than the length of the linklist 
    Node * slow = head;
    //now move both fast and slow pointer at the same time until the fast pointer reaches the end of the linklist
    //when the fast pointer reaches the end of the linklist, the slow pointer will be at the (n-1)th node from the end of the linklist
    //so we can remove the nth node from the end of the linklist by linking the slow pointer to the next of the next node
    while(fast->next != nullptr){
        slow = slow->next;
        fast = fast->next;
    }

    Node * deleteNode = slow->next; //the node to be deleted is the next of the slow pointer
    slow->next = slow->next->next; // link the slow pointer to the next of the next node to remove the nth node form the linklist 

    delete(deleteNode); //delete the node to be deleted
    return head; //return the head of the linklist
}


int main(){
    vector<int> arr = {1,2,3,4,5,6};
    Node * head = convertArr2All(arr);
    print(head);

    cout<<"After removing 2nd node from end:"<<endl;
    head = RemoveNthNodeEnd(head , 2);
    print(head);
    return 0;
}