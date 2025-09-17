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
// Function to delete the head of the doubly linked list
Node * deleteHead(Node * head){
    if (head == nullptr  || head->next == nullptr){
        return nullptr; //if the list is empty or has only one node return nullptr 
    }
    Node * prev = head;
    head = head ->next;
    head->back = nullptr;
    prev->next = nullptr;
    delete prev;

    return head;
}


// Function to delete the tail of the doubly linked list
Node * deleteTail(Node * head){
    if (head == nullptr || head->next == nullptr){
        return nullptr;
    }
    Node * tail= head ;
    while(tail->next != nullptr){
        tail = tail->next;
    }
    Node * prev = tail->back;
    prev->next = nullptr;
    tail->back = nullptr;
    delete tail;

    return head;
}

Node * deleteNodeK(Node * head , int k){
    if(head == NULL ){
        return nullptr;
    }
    int cnt = 0;
    Node * KNode = head;
    while(KNode != nullptr){
        cnt++;
        if(cnt== k) break;
        KNode = KNode->next;
    }

    Node * prev = KNode->back;
    Node * front = KNode->next;

    if(prev == nullptr || front == nullptr){
        return nullptr;
    }
    else if(prev == nullptr){
        return deleteHead(head);
    }
    else if(front == nullptr){
        return deleteTail(head);
    }
        prev->next = front;
        front->back = prev;

        KNode->next = nullptr;
        KNode->back = nullptr;
        delete KNode;
        return head;

}

void  deleteNode(Node * Knode){
    Node * prev = Knode->back;
    Node * front = Knode->next;

    if(front == NULL){
        prev->next = nullptr;
        Knode->back = nullptr;
        free(Knode);
        return;
        
    }
    prev->next = front;
    front->back = prev;

    Knode->next= Knode->back = nullptr;
    free(Knode);
}


int main(){
    vector<int> arr = {1,2,3,4,5};
    Node * head = convertToDoublyLinkedList(arr);
    printDoublyLinklist(head);
    cout<<endl;

    cout<<"after deleting the head"<<endl;
    head = deleteHead(head);
    printDoublyLinklist(head);
    cout<<endl;

    cout<<"after deleting the tail"<<endl;
    head = deleteTail(head);
    printDoublyLinklist(head);
    cout<<endl;

    cout<<"after deleting the node at  position 2nd "<<endl;
    head= deleteNodeK(head , 2);
    printDoublyLinklist(head);
    cout<<endl;

    cout<<"after deleting the node with value 4"<<endl;
    deleteNode(head->next);
    printDoublyLinklist(head);
    return 0;

}