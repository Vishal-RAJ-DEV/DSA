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

Node * sortingNumbers(Node * head){
    if(head == nullptr && head->next == nullptr) return head;

    Node * zeroHead = new Node(-1), * zero = zeroHead;
    Node * oneHead = new Node(-1), * one = oneHead;
    Node * TwoHead = new Node(-1), * Two = TwoHead;

    Node * temp = head;

    while(temp != nullptr){
        if(temp -> data == 0){
            zero->next = temp;  //link the zero node to the current node
            zero = temp; //move the zero pointer to the current node
        }
        else if (temp ->data == 1){
            one->next = temp; //or link the one node to the current node 
            one = temp;  //move the one pointer to the current node 
        }    
        else{
            Two-> next = temp ;
            Two = temp;
        }

        temp = temp->next;
    }

    zero->next = (oneHead->next) ? oneHead ->next : TwoHead->next;  //link the zero node to the 1s node if its available, otherwise link it to the 2s node 
    one->next = TwoHead ->next ;  //link the one node to the 2s node if its available , otherwise it will be null 
    Two->next = nullptr;  //the last node of the 2s will point to null

    Node *NewHead = zeroHead->next;  //newhead will point to the next of the zerohead which is the first node of the sorted linklist

    delete(zeroHead);
    delete(oneHead);
    delete(TwoHead);

    return NewHead;

}


int main(){
    vector<int> arr = {1,0,1,2,0,2,1};
    Node * head = convertArr2All(arr);
    print(head);

    cout<<"After sorting 0,1 and 2 in the order"<<endl;
    head = sortingNumbers(head);
    print(head);
    return 0;
}