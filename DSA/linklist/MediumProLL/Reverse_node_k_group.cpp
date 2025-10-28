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

void print(Node * head){  //to print the linklist 
    while(head!= nullptr){
        cout<<head->data<<" ";
        head = head->next;
    }
    cout<<endl;
}

Node* findKnode(Node* temp, int k) {
    k -= 1;
    while (temp != nullptr && k > 0) {
        k--;
        temp = temp->next;
    }
    return temp;
}

Node* reverseLL(Node* head) {
    Node* temp = head;
    Node* prev = nullptr;
    while (temp != nullptr) {
        Node* front = temp->next;
        temp->next = prev;
        prev = temp;
        temp = front;
    }
    return prev;
}

Node* reverseKGroup(Node* head, int k) {
    Node* temp = head;
    Node* prev = nullptr;

    while (temp != nullptr) {
        Node* KNode = findKnode(temp, k);
        if (KNode == nullptr) {
            // fewer than k nodes remain → stop reversing
            if (prev) prev->next = temp;
            break;
        }

        Node* nextNode = KNode->next;  // save next segment
        KNode->next = nullptr;         // cut connection

        Node* reversedHead = reverseLL(temp);  // reverse current group

        if (prev == nullptr)
            head = reversedHead;  // update new head after first group
        else
            prev->next = reversedHead;  // link previous reversed segment

        prev = temp;     // move prev to tail of this reversed segment
        temp = nextNode; // move to next group
    }

    return head;
}

int main(){
    vector<int> arr = {1,2,3,4,5,6,7};
    Node * head = convertArr2All(arr);
    print(head);

    cout<<"After reversing the linklist in k groups:  "<<endl;
    head = reverseKGroup(head, 3); // Changed function name and k value
    print(head);
    return 0;
}