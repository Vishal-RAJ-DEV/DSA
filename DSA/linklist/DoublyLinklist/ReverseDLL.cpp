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

Node * reverseDoublyLinklist(Node * head){
    if(head == nullptr || head->next == nullptr) return head;

    Node * current = head; // start from the head of the list
    Node * last = nullptr;  // to keep track of the last node processed
    
    while(current != nullptr){
        last = current->back; // store the back pointer
        current->back = current->next;  //swap next and back pointers
        current->next = last; // set next to the previous back pointer which is now stored in last
        current = current->back;  // move to the next node which is now the back pointer
    }
    head = last->back;  // at the end of the loop, last's back pointer will be pointing to the new head of the reversed list

    return head;
}

int main(){
    vector<int> arr = {1,2,3,4,5};
    Node * head = convertToDoublyLinkedList(arr);
    printDoublyLinklist(head);


    cout << endl << "Reversed Doubly Linked List: " << endl;
    // Reverse the doubly linked list
    head = reverseDoublyLinklist(head);
    printDoublyLinklist(head);
    return 0;
}