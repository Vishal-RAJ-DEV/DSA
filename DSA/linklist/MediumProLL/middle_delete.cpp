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
Node * MiddleNodeDelete1(Node * head){ //brute force approch to find the middle node and delete it 
    if(head == nullptr || head->next == nullptr) return NULL; //if the linklist is empty or has only one node , return NULL

    Node * temp = head ;
    int count = 0 ;
    while (temp->next != nullptr ){  //first count the number of nodes in the linklist
        count++;
        temp  = temp->next ;
    }

    int mid = count/2; //find the middle node by dividing the count by 2

    temp = head;
    while(temp != nullptr){  //now traverse the linklist to find the middle node
        mid --;
        if(mid == 0){
            Node * deleteNode = temp->next;
            temp->next = temp->next->next; //link the current node to the next of the next node to remove the middle node
            delete deleteNode; //delete the middle node
            break;
        }

        temp = temp->next; //move to the next node
    }
    return head; //return the head of the linklist

}


Node * MiddleNodeDelete(Node * head){  //optimized approch using fast and slow pointer 
    if(head == nullptr ||  head->next == nullptr) return NULL; //if the linklist is empty or has only one node , return NULL

    Node * slow = head;
    Node * fast = head->next->next; //fast pointer will move two steps at a time and slow pointer will move one step at a time
    //this will make the fast pointer reach the end of the linklist when the slow pointer reaches the middle of the linklist
    //so we can delete the middle node by linking the slow pointer to the next of the next node  

    while(fast != nullptr && fast->next != nullptr){
        slow = slow->next;  //this will make the slow pointer point to the middle node of the linklist
        fast = fast->next->next;
        //this will make the slow pointer point to the middle node of the linklist 
    }

    Node * deleteNode = slow->next; //the node to be deleted is the next of the slow pointer
    slow->next =  slow->next->next;
    delete deleteNode;

    return head;

}


int main(){
    vector<int> arr = {1,2,3,4,5};
    Node * head = convertArr2All(arr);
    print(head);

    cout<<"After removing middle node :"<<endl;
    head = MiddleNodeDelete(head);
    print(head);
    return 0;
}