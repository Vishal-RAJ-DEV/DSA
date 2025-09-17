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

Node * reverseLinkList(Node * head){ 
    if(head == nullptr ||  head->next == nullptr) return head;
    Node * temp = head;
    Node * prev = nullptr;
    while(temp!= nullptr){
        Node * front = temp->next;
        temp->next = prev;
        prev = temp;
        temp = front;
    }

    Node * newHead = prev;
    return newHead;
}
Node * reverseLinkList1(Node * head){ 
    if(head == nullptr || head->next == nullptr) return head;

    Node * newHead = reverseLinkList1(head->next);
    Node  * front = head->next;
    front->next = head;
    head->next = nullptr;
    return newHead;

}




int main(){
    vector<int> arr = {1,2,3,4,5,6,7};
    Node * head = convertArr2All(arr);
    print(head);

    cout<<"After reversing the linklist :  "<<endl;
    head = reverseLinkList1(head);
    print(head);
    return 0;
}