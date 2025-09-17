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

Node * insertHead(Node * head , int value){ //function to insert a new node at the head of the doubly linked list
    Node * newNode = new Node(value , head , nullptr);  // Create a new node with value, next as head, and back as nullptr
    if (head != nullptr){
        head->back = newNode; // Update the back pointer of the original head to point to the new node
    }

    return newNode;
}

Node * insertTail(Node * head , int value){
    Node * newNode = new Node(value); //here we create a new node with value and next & back as nullptr 

    if(head == nullptr){  //if list is empty then we return the new node as the head 
        return newNode;
    }

    Node * tail = head;  //we will use tail pointer to tranverse the list to find the last node 
    while(tail->next != nullptr){  //transverse till we reach the last node 
        tail = tail->next;
    }
    tail->next= newNode;  //link the last node to the new node
    newNode->back = tail; //set the back pointer of the new node to the last node

    return head;
}
Node * insertBeforeTail(Node * head , int value){ //insert before the tail of the linked list 
    if(head == nullptr || head->next == nullptr){
        return insertHead(head , value);  //just call the inserHead function if list is empty or has only one node 
    }
    Node * tail  = head ;
    while(tail->next != nullptr){
        tail = tail->next;
    }
    Node * prev = tail->back;
    Node * newNode = new Node(value , tail , prev);
    prev->next = newNode;
    tail->back = newNode;

    return head;
    
}

Node * InserBeforeKthElement(Node * head , int k , int value){
    if(k == 1){
        return insertHead(head  , value);
    }
    Node * KNode = head;
    int cnt = 0;
    while(KNode != nullptr){
        cnt++;
        if(cnt == k) break;
        KNode = KNode->next;
    }
    Node * prev = KNode->back;
    Node * newNode = new Node(value , KNode , prev);
    prev->next = newNode;
    KNode->back = newNode;

    return head;
}

void insertBeforeNode(Node * node , int value){
    Node * prev = node->back;
    Node * newNode = new Node(value , node, prev);
    prev->next = newNode;
    node->back = newNode;
}

int main(){
    vector<int> arr = {1,2,3,4,5};
    Node * head = convertToDoublyLinkedList(arr);
    printDoublyLinklist(head);
    cout<<endl;

    cout<<"After inserting 0 at the head"<<endl;
    head = insertHead(head , 0 );
    printDoublyLinklist(head);
    cout<<endl;

    cout<<"After inserting 6 at the tail"<<endl;
    head = insertTail(head , 6 );
    printDoublyLinklist(head);
    cout<<endl; 

    cout<<"After inserting 7 before the tail"<<endl;
    head = insertBeforeTail(head , 7);
    printDoublyLinklist(head);
    cout<<endl;

    cout<<"After inserting 10 before the kth element"<<endl;
    head = InserBeforeKthElement(head , 2 , 10);
    printDoublyLinklist(head);
    cout<<endl;
    
    
    cout<<"After inserting 11 before the node element"<<endl;
    insertBeforeNode(head->next->next ,11);
    printDoublyLinklist(head);
    cout<<endl;
    return 0;
} 