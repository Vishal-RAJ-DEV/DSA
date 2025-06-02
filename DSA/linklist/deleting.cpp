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

Node * deleteHead(Node * head){  // delete the head of the linklist
    if(head == nullptr) return head;
    Node * temp = head;
    head = head->next;
    delete temp;
    return head;
}
Node * deleteTail(Node * head){   //deleting the  tail of the linklist
    if(head == nullptr || head->next == nullptr) return nullptr;

    Node * temp = head;
    while(temp->next->next != nullptr){
        temp = temp->next;
    }
    delete temp->next;
    temp->next = nullptr;
    return head;
}
Node * deleteNodeK(Node * head , int k){  //delete the node at position k 
    if(head == nullptr) return head;
    if (k == 1){
        return deleteHead(head);
    }
    int cnt = 0;
    Node * temp = head;
    Node * prev = nullptr;
    while(temp != nullptr ){
        cnt++;
        if(cnt == k){
            prev->next = prev->next->next;  //link the previous node to the node after the current node 
            delete temp;
            break;
        }
        prev = temp;
        temp = temp->next;
    }
    return head;
}
int main(){
    vector<int> arr = {1,2,3,4,5,6};
    Node * head = convertArr2All(arr);
    print(head);

    
    cout<<"after deleting the 3rd elenment"<<endl;
    head = deleteNodeK(head , 3);
    print(head);


    cout<<"aftrer deleting the head"<<endl;
    head = deleteHead(head);
    print(head);
    

    cout<<"after the deleting the tail"<<endl;
    head = deleteTail(head);
    print(head);



    return 0;
}