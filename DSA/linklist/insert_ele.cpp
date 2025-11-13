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

Node * insertHead(Node * head , int value ){  // insert the head of the linklist
    return new Node(value , head); //here value is data and head is next pointer of the new node which form the new head of the linklist
}
Node * insertTail(Node * head , int value){   //insert the  tail of the linklist
    if(head == NULL) return new Node(value);
    Node * temp = head;
    while(temp->next != NULL){
        temp = temp->next;
    }
    temp->next = new Node(value);
    return head;
}
Node * insertNodeK(Node * head , int k , int value){  //insert the node at position k 
    if(head == NULL) {
        if(k == 1) return new Node(value);
        else return head;
    }
    if(k == 1) return new Node( value  , head);
    Node * temp = head ;
    int cnt = 0;
    while(temp != NULL){
        cnt++;
        if(cnt == k-1){
            Node * newNode = new Node(value , temp->next);
            temp->next = newNode;
            break;
        }
        temp = temp->next;
    }
    return head;
    
}

Node *insertBeforeVAlue(Node * head , int value , int ele){ //insert the node before the value
    if(head == NULL) return NULL;
    if (head->data == value){
        return new Node(ele, head);
    }
    Node * temp = head;
    while(temp->next != NULL){
        if(temp->next->data == value){
            Node * newNode = new Node (ele, temp->next);
            temp->next = newNode;
            break;

        }
        temp = temp->next;
    }
    return head;
}

void deleteNode(Node* node) { //function to delete a node in the linklist when the head is not given (leetcode problem 237)
    Node* prev = nullptr;

    while (node != nullptr && node->next != nullptr) {
        node->data = node->next->data;   // Step 1: copy value from next node
        prev = node;                     // Step 2: update previous pointer
        node = node->next;               // Step 3: move to next node
    }

    if (prev != nullptr) {
        prev->next = nullptr;            // Step 4: remove last copied node
        delete node;                     // Step 5: delete that last node
    }
}
 void deleteNode1(Node* node) {   //function to delete a node in the linklist when the head is not given (leetcode problem 237) alternative approch 
       node->data = node->next->data;         // Step 1: copy value from next node
    Node* temp = node->next;                    // Step 2: store next node
    node->next = node->next->next;       // Step 3: skip over the next node
    delete temp; 
    }

int main(){
    vector<int> arr = {1,2,3,4,5,6};
    Node * head = convertArr2All(arr);
    print(head);

    cout<<"inserting at head"<<endl;
    head = insertHead(head , 0);
    print(head);
    
    cout<<"inerting at tail"<<endl;

    head = insertTail(head , 7 );
    print(head);

    cout<<"inderting at possition k"<<endl;

    head = insertNodeK(head , 4, 100);
    print(head);

    cout<<"inserting before the value"<<endl;
    head = insertBeforeVAlue(head , 100 , 50);
    print(head);
    
    // deleteNode(head->next->next);
    // print(head);
    
    
    
    
    return 0;
}