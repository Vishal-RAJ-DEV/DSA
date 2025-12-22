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
Node * findTail( Node * head ){
    Node * tail = head;
    while( tail->next != nullptr){
        tail = tail->next;
    }
    return tail;
}
vector<vector<int>>findPairSum( Node * head , int sum ){
    vector<vector<int>> ans;
    Node * left = head;
    Node * right = findTail( head);
    while( left != nullptr && right != nullptr && left->data < right->data){
        int pairSum = left->data + right->data;
        if( pairSum == sum){
            ans.push_back({left->data , right->data});
            left = left->next;
            right = right->back;
        }
        else if ( pairSum < sum ) left = left->next; //move the left pointer forward to increase the sum
        else right = right->back;   //move the right pointer backward to decrease the sum
    }
    return ans;
}

int main(){
    vector<int> arr = {1,2,3,4,5,9};
    Node * head = convertToDoublyLinkedList(arr);
    printDoublyLinklist(head);
    int sum = 5;
    vector<vector<int>>ans = findPairSum(head , sum);
    cout<<"\nPairs with sum "<<sum<<" are : \n";
    for( auto &pair : ans){
        cout<<"("<<pair[0]<<","<<pair[1]<<") ";
    }


    return 0;
}
