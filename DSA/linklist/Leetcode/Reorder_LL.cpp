#include <iostream>
#include <bits/stdc++.h>
using namespace std;
/*You are given the head of a singly linked-list. The list can be represented as:

L0 → L1 → … → Ln - 1 → Ln
Reorder the list to be on the following form:

L0 → Ln → L1 → Ln - 1 → L2 → Ln - 2 → …
You may not modify the values in the list's nodes. Only nodes themselves may be changed.

Example 1:
Input: head = [1,2,3,4]
Output: [1,4,2,3]
*/
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

void reorderList(Node* head) {  // Changed ListNode* to Node*
    if(head == nullptr || head->next == nullptr) return;

    // Step 1: Find the middle of the linked list
    Node* slow = head;      // Changed ListNode* to Node*
    Node* fast = head;      // Changed ListNode* to Node*
    while(fast->next && fast->next->next){
        slow = slow->next;
        fast = fast->next->next;
    }
    
    // Step 2: Reverse the second half
    Node* prev = nullptr;   // Changed ListNode* to Node*
    Node* curr = slow->next; // Changed ListNode* to Node*
    while(curr){
        Node* front = curr->next; // Changed ListNode* to Node*
        curr->next = prev;
        prev = curr;
        curr = front;
    }
    slow->next = nullptr;
    
    // Step 3: Merge the two halves
    Node* head1 = head;     // Changed ListNode* to Node*
    Node* head2 = prev;     // Changed ListNode* to Node*
    while(head2){
        Node* temp1 = head1->next; // Changed ListNode* to Node*
        Node* temp2 = head2->next; // Changed ListNode* to Node*
        
        head1->next = head2;
        head2->next = temp1;

        head1 = temp1;
        head2 = temp2;
    }
}

int main(){
    vector<int> arr1 = {1,2,3,4,5,6};
    Node * head1 = convertArr2All(arr1);
    
    cout << "Original list: ";
    print(head1);
    
    reorderList(head1);
    
    cout << "Reordered list: ";
    print(head1);
    
    return 0;
}