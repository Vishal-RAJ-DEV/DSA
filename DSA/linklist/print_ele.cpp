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
Node * convertArr2All (vector<int>&a){
    Node * head = new Node(a[0]);
    Node * mover = head;   //head is the first node of the linked list and mover is a pointer that willl point to the current node 
    for(int i = 1;i<a.size();i++){
        Node * temp = new Node(a[i]);
        mover->next = temp; // link the current  node(mover) to the new node (temp)
        mover = temp;  //so the current node (mover) will poiint to the new node (temp)
 
         
    }
    return head;
    
}
int checkpresent(Node * head , int value){
    Node * temp = head;
    while(temp){
        if(temp->data ==value) return 1;
        temp = temp->next; //move to the next node
    } 
    return 0;
}
int main(){
    vector<int> a= {1 ,2 ,3,4 ,5 ,6, 7 , 8,9,10};
    Node * head = convertArr2All(a);
    cout<<head->data<<endl;  //printing the first elenment of the linked list 
    Node * temp = head;
    int cnt = 0;
    
    while(temp){
        cout<<temp->data<<" ";  //print the data of the current node
        temp = temp->next;   //move to the next node 
        cnt++;
       
    }
    cout<<endl;
    cout<<"length of the linked list is"<<" "<<cnt<<endl;

    cout<<"enter the value you want to check in the linked list"<<endl;
    cout<<checkpresent(head , 5)<<endl;


  
    return 0;
}

//here is the explanation of the how the node moves to the next node.

// Let’s zoom in on this part:

// Node* mover = head;
// for (int i = 1; i < a.size(); i++) {
//     Node* temp = new Node(a[i]);   // Create a new node with data a[i]
//     mover->next = temp;            // Link current node (mover) to new node (temp)
//     mover = temp;                  // Move 'mover' to point to the new node
// }
// Let’s simulate with a few elements: a = {1, 2, 3}

// Step-by-Step Dry Run:
// First Node:

// Node* head = new Node(1);
// Node* mover = head;
// head → [1 | next → NULL]

// mover points to the same node.

// Loop for i = 1:

// Node* temp = new Node(2); // Creates [2 | NULL]
// mover->next = temp;       // Links 1's next to temp
// mover = temp;             // mover now points to [2 | NULL]
// Now the structure is:

// head → [1 | next →] → [2 | next → NULL]
// Loop for i = 2:


// Node* temp = new Node(3); // Creates [3 | NULL]
// mover->next = temp;       // Links 2's next to temp
// mover = temp;             // mover now points to [3 | NULL]
// Final structure:

// head → [1 | →] → [2 | →] → [3 | NULL]