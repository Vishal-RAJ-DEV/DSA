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

void print(Node * head){  //to print the linklist - changed return type to void
    while(head!= nullptr){
        cout<<head->data<<" ";
        head = head->next;
    }
    cout<<endl;
}

Node *getIntersectionNode(Node *headA, Node *headB) {  // Changed ListNode to Node
    if(headA == nullptr && headB == nullptr) return nullptr; // Changed NULL to nullptr
    Node * t1 = headA;  // Changed ListNode to Node
    Node * t2 = headB;  // Changed ListNode to Node
    while(t1 != t2){
        t1 = t1->next;
        t2 = t2->next;
        if(t1 == t2) return t1;
        if(t1 == nullptr) t1 = headB;
        if(t2 == nullptr) t2 = headA;
    }
    return t1;
}



int main(){
    // Create two linked lists with intersection
    vector<int> arr1 = {1, 3, 5, 7, 9};
    vector<int> arr2 = {2, 4};
    
    Node* head1 = convertArr2All(arr1);
    Node* head2 = convertArr2All(arr2);
    
    // Create intersection point - connect the second list to the middle of first list
    Node* temp = head1;
    for(int i = 0; i < 2; i++) { // Move to the 3rd node (index 2)
        temp = temp->next;
    }
    
    // Find the last node of second list
    Node* last = head2;
    while(last->next != nullptr) {
        last = last->next;
    }
    
    // Connect the end of second list to node in first list
    last->next = temp;
    
    cout << "First linked list: ";
    print(head1);
    
    cout << "Second linked list: ";
    print(head2);
    
    Node* intersectionNode = getIntersectionNode(head1, head2);
    
    if(intersectionNode != nullptr) {
        cout << "Intersection found at node with value: " << intersectionNode->data << endl;
    } else {
        cout << "No intersection found." << endl;
    }
    
    return 0;
}