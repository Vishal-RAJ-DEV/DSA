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
void * print(Node * head){  //to print the linklist 
    while(head!= nullptr){
        cout<<head->data<<" ";
        head = head->next;
    }
    cout<<endl;
}


int findLength(Node * slow , Node * fast){
    int cnt = 1; // Initialize count to 1 for the first node in the cycle
    fast = fast->next; // Move fast one step to start counting
    while(fast != slow){  // Continue until slow and fast meet again
        cnt++; // Increment the count for each node in the cycle
        fast= fast->next; // Move fast one step
    }
    return cnt;
}


int  detectCycle(Node* head) { //using Floyd's Cycle-Finding Algorithm (Tortoise and Hare)
    // Step 1: Check if the linked list is empty    
    // Initialize two pointers, slow and fast,
    // to the head of the linked list
    if (head == nullptr) {
        return 0;  // No loop in an empty list
    }
    Node* slow = head;
    Node* fast = head;
    
    // Step 2: Traverse the linked list with
    // the slow and fast pointers
    while (fast != nullptr && fast->next != nullptr) {
        // Move slow one step
        slow = slow->next;
        // Move fast two steps
        fast = fast->next->next;

        // Check if slow and fast pointers meet
        if (slow == fast) {
            return findLength(slow , fast); // If they meet, there is a loop
        }
    }

    // If fast reaches the end of the list,
    // there is no loop
    return 0;
}






int main(){
    vector<int> arr = {1, 2, 3, 4, 5,6,7,8,9,10};
    Node* head = convertArr2All(arr);
    // Create a loop by connecting the last node to the second node (index 1)
    Node* temp = head;
    while (temp->next != nullptr) {
        temp = temp->next;
    }
    // Get the node at index 1
    Node* secondNode = head->next->next;
    // Connect last node to second node
    temp->next = secondNode;  // This creates a loop in the linked list
    cout<<"length of the linkked list cycle is :"<<detectCycle(head)<<endl;

    return 0;
}