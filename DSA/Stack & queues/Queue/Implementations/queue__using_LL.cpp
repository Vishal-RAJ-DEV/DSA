#include <iostream>
using namespace std;

class Node {
public:
    int data;
    Node* next;
    Node(int data){
        this->data = data;
        next = nullptr;
    }
};

class Queue {
    Node* start; // front of the queue
    Node* end;   // rear of the queue
    int currSize;
public:
    Queue(){
        start = end = nullptr;
        currSize = 0;
    }

    // Enqueue operation
    void push(int val) {
        Node* newNode = new Node(val);
        if (end == nullptr) { // If queue is empty
            start = end = newNode; // both start and end point to the new node
        } else {
            end->next = newNode; //or 
            end = newNode;
        }
        currSize++;
    }

    // Dequeue operation
    int pop() {
        if (start == nullptr) {
            cout << "Queue is empty\n";
            return -1;
        }
        int val = start->data;
        Node* temp = start;
        start = start->next;
        if (start == nullptr) end = nullptr;
        delete temp;
        currSize--;
        return val;
    }

    // Get front element
    int front() {
        if (start == nullptr) {
            cout << "Queue is empty\n";
            return -1;
        }
        return start->data;
    }

    // Get rear element
    int back() {
        if (end == nullptr) {
            cout << "Queue is empty\n";
            return -1;
        }
        return end->data;
    }

    // Get current size
    int size() {
        return currSize;
    }

    // Check if queue is empty
    bool empty() {
        return currSize == 0;
    }
};

int main() {
    Queue q;
    q.push(10);              // Queue: [10]
    q.push(20);             // Queue: [10, 20]  
    q.push(30);         // Queue: [10, 20, 30]

    cout << "Front: " << q.front() << endl; // 10
    cout << "Back: " << q.back() << endl;   // 30
    cout << "Size: " << q.size() << endl;   // 3

    cout << "Popped: " << q.pop() << endl;  // 10
    cout << "Front after pop: " << q.front() << endl; // 20

    return 0;
}