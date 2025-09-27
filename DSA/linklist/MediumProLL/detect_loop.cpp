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

bool detectCycle(Node* head) { //using Floyd's Cycle-Finding Algorithm (Tortoise and Hare)
    // Step 1: Check if the linked list is empty    
    // Initialize two pointers, slow and fast,
    // to the head of the linked list
    if (head == nullptr) {
        return false;  // No loop in an empty list
    }
    Node* slow = head;
    Node* fast = head;

    // Step 2: Traverse the linked list with
    // the slow and fast pointers
    while (fast != nullptr && fast->next != nullptr) {
        // Move slow one step
        slow = slow->next;
        // Move fast two steps
        fast = fast->next->next;

        // Check if slow and fast pointers meet
        if (slow == fast) {
            return true;  // Loop detected
        }
    }

    // If fast reaches the end of the list,
    // there is no loop
    return false;
}

bool detectLoop(Node* head) {
    
    // Initialize a pointer 'temp'
    // at the head of the linked list
    if (head == nullptr) {
        return false;  // No loop in an empty list
    }
    Node* temp = head;  
    
    // Create a map to keep track of
    // encountered nodes
    std::unordered_map<Node*, int> nodeMap;  

    // Step 2: Traverse the linked list
    while (temp != nullptr) {
        // If the node is already in the
        // map, there is a loop
        if (nodeMap.find(temp) != nodeMap.end()) {
            return true;
        }
        // Store the current node
        // in the map
        nodeMap[temp] = 1;
        
        // Move to the next node
        temp = temp->next;  
    }

    // Step 3: If the list is successfully traversed 
    // without a loop, return false
    return false;
}
Node * startingPointOfLoop(Node* head) {
    if (head == nullptr) {
        return nullptr;  // No loop in an empty list
    }
    Node* slow = head;
    Node* fast = head;

    // Step 1: Detect if a loop exists using Floyd's Cycle-Finding Algorithm
    while (fast != nullptr && fast->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;

        if (slow == fast) {
            // Loop detected, now find the starting point of the loop
            Node* entry = head;
            while (entry != slow) {
                entry = entry->next;
                slow = slow->next;
            }
            return entry;  // Starting point of the loop
        }
    }

    return nullptr;  // No loop detected
}



int main(){
    vector<int> arr = {1, 2, 3, 4, 5};
    Node* head = convertArr2All(arr);
    // Create a loop by connecting the last node to the second node (index 1)
    Node* temp = head;
    while (temp->next != nullptr) {
        temp = temp->next;
    }
    // Get the node at index 1
    Node* secondNode = head->next;
    // Connect last node to second node
    temp->next = secondNode;  // This creates a loop in the linked list
    

    cout<<"Checking for loop in the linked list using Floyd's Cycle-Finding Algorithm (Tortoise and Hare):"<<endl;
    if(detectCycle(head)){
        cout<<"Cycle detected"<<endl;
    }else{
        cout<<"No cycle detected"<<endl;
    }
    cout<<"starting point of the loop is :"<<startingPointOfLoop(head)->data<<endl;

    return 0;
}