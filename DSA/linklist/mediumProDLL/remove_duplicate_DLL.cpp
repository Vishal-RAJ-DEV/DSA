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

Node * removeDuplicates( Node * head){
    if( head == nullptr) return head ; //base case if head is null return head
    Node * current = head; // create a temp pointer to traverse the list
    while( current != nullptr && current->next != nullptr){
        Node * nextNode = current->next;
        while( nextNode != nullptr && nextNode->data == current->data){
            Node * deleteNode = nextNode;
            nextNode = nextNode->next;
            delete deleteNode;
        }

        current-> next = nextNode;
        if( nextNode != nullptr){
            nextNode->back = current;
        }
        current = nextNode;
    }
    return head;
}

int main(){
    vector<int> arr = {1,1,2,3,3,4,4,4,5};
    Node * head = convertToDoublyLinkedList(arr);
    head = removeDuplicates(head);
    printDoublyLinklist(head);
    return 0;
}