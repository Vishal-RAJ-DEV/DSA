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

bool isPalidrome(Node * head){ 
    if(head == nullptr || head->next == nullptr) return true;
    Node * slow = head;
    Node * fast = head;
    while(fast->next != nullptr && fast->next->next != nullptr){ //to find the middle of the linklist 
        slow = slow->next; // slow will point to the middle of the linklist
        fast = fast->next->next; // fast will point to the end of the linklist
    }

    Node * newhead = reverseLinkList(slow->next); //first reverse the secoond half of the linklist 

    Node * first = head; //first will point to the first half of the linklist
    Node * second = newhead;// second will point to the second half of the linklist
    while(second!= nullptr){ //loop through the second half of the linklist
        if(first->data != second->data) {    //if the data of the first half and second half are not equal then return false
            reverseLinkList(newhead);// reverse the second half of the linklist back to its original form
            return false;
        }
        first = first->next;  // move to the next node in the first half
        second = second->next; // move to the next node in the second half
    }

    slow->next = reverseLinkList(newhead); // reverse the second half of the linklist back to its original form
    return true;
}







int main(){
    vector<int> arr = {1,2,3,3,2,1};
    Node * head = convertArr2All(arr);
    print(head);

    cout<<"After reversing the linklist :  "<<endl;
    bool result = isPalidrome(head);
    cout<<(result ? "The linked list is a palindrome." : "The linked list is not a palindrome.")<<endl;
    return 0;
}