#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class Node {
    public:
    int data ;
    Node * next;
    Node * back;

    public:
    Node(int data1 , Node * next1 , Node * back1){    //constructor to initialize the node with data, next and back pointers
        data = data1;
        next = next1;
        back = back1;
    }
    public:
    Node(int data1){  //another constructor for node so we don't have to define next and back as null.
        data = data1;
        next = nullptr;
        back = nullptr;
    }
};

Node *  convertToDoublyLinkedList(vector<int>& arr){
    Node * head = new Node(arr[0]);  //this will create the node as the head using the second constructor 
    Node * prev = head;  //prev will used as a pointer to the prevoius node 
    for(int i = 1;i<arr.size();i++){
        Node * temp = new Node(arr[i],nullptr, prev); //create a new node with data , next as null and back as prev using the first constructor
        prev->next = temp;  // link the pevious node to the new node 
        prev = temp;  //move the prev pointer to the new node

    }
    return head;  //reuturn the head of the DLL;
}
void printDoublyLinklist(Node * head){
    while(head != nullptr){
        cout<<head->data<<" ";
        head = head->next;
    }
}

Node * deleteAllOccurence( Node * head , int key){
    if( head == nullptr) return head ; //base case if head is null return head
    Node * temp = head; // create a temp pointer to traverse the list
    while ( temp != nullptr){
        if( temp ->data == key ){
            if( temp == head ) { //if the key is at the head node 
                head  = head->next;
            }

            Node * prev_node = temp->back;
            Node * next_node = temp->next;

            if( prev_node) prev_node->next = next_node;
            if( next_node) next_node->back = prev_node;

            Node * nodeToDelete = temp;
            temp = temp->next;
            delete nodeToDelete;
        }
        else {
            temp = temp->next;
        }
    }
    return head;
}


int main(){
    vector<int> arr = {3,2,3,4,3,5,3};
    Node * head = convertToDoublyLinkedList(arr);
    head = deleteAllOccurence(head, 3);
    printDoublyLinklist(head);
    return 0;
}