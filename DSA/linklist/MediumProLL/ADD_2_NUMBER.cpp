#include <iostream>
#include <bits/stdc++.h>
using namespace std;


// num1  = 243, num2 = 564

// l1 = [2,4,3]
// l2 = [5,6,4]

// Result: sum = 807; L = [7,0,8]

// Explanation: Since the digits are stored in reverse order, reverse the numbers first to get the or  original number and then add them as → 342 + 465 = 807. Refer to the image below.
  

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

Node * Adding2Numbers(Node * head1 , Node * head2){
    Node * temp1 = head1;
    Node * temp2 = head2;
    Node * dummy = new Node(-1); //dummy node to help in the additionNOde
    Node * current = dummy; //current will point to the last node of the result linklist
    int carry = 0 ; //carry to handle the sum greater than 9
    while(temp1 !=nullptr || temp2 != nullptr ){
        int sum = carry;   //initalize sum with carry
        if(temp1) sum += temp1->data;
        if(temp2) sum += temp2->data;

        Node * newNode = new Node(sum % 10); //create a new node with the sum of the two nodes
        carry = sum / 10; //update the carry for the next iteration
        current->next = newNode; //link the new node to the current node
        current = newNode; //move the current pointer to the new node

        if(temp1) temp1 = temp1->next; //move to the next node in the first linklist
        if(temp2) temp2 = temp2->next; //move to the next node in the second linklist
    }
    if(carry > 0) {
        Node * newNode = new Node(carry); //if there is a carry left, create a new node with the carry
        current->next = newNode; //link the new node to the current node
    }

    return  dummy->next; //the head of the result linklist will be the next of the dummy node
    delete dummy; //delete the dummy node to avoid memory leak
}

int main(){
    vector<int> arr1 = {1,2,3,4,5,6};
    vector<int> arr2 = {7,8,9,10,11,12};
    Node * head1 = convertArr2All(arr1);
    Node * head2 = convertArr2All(arr2);
    print(head1);
    print(head2);

    Node *result = Adding2Numbers(head1 , head2);
    cout<<"after adding the two linklist"<<endl;
    print(result);

    
    return 0;
}