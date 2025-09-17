#include <iostream>  // For input/output operations
using namespace std;

// Define a class named Queue
class Queue {
  int* arr;           // Pointer to dynamic array for storing elements
  int start, end;     // Indices to track the front and rear of the queue
  int currSize;       // Current number of elements in the queue
  int maxSize;        // Maximum capacity of the queue

public:
  // Default constructor (not used in main here, but available)
  Queue() {
    arr = new int[16];  // Allocate default size
    start = -1;         // Indicates queue is initially empty
    end = -1;
    currSize = 0;
    maxSize = 16;
  }

  // Constructor with a given max size
  Queue(int maxSize) {
    this->maxSize = maxSize;         // Set max size
    arr = new int[maxSize];          // Allocate memory for array
    start = -1;                      // Initialize as empty
    end = -1;
    currSize = 0;
  }

  // Function to add (enqueue) a new element into the queue
  void push(int newElement) {
    if (currSize == maxSize) {      // If the queue is full
      cout << "Queue is full\nExiting..." << endl;
      exit(1);                      // Exit the program
    }

    if (end == -1) {                // If this is the first element
      start = 0;
      end = 0;
    } else {
      end = (end + 1) % maxSize;    // Circular increment of rear index
    }

    arr[end] = newElement;          // Insert element at rear
    cout << "The element pushed is " << newElement << endl;
    currSize++;                     // Increase size
  }

  // Function to remove (dequeue) element from the queue
  int pop() {
    if (start == -1) {              // If the queue is empty
      cout << "Queue Empty\nExiting..." << endl;
      exit(1);
    }

    int popped = arr[start];        // Get front element

    if (currSize == 1) {            // If it was the last element
      start = -1;
      end = -1;
    } else {
      start = (start + 1) % maxSize; // Move front forward (circular)
    }

    currSize--;                     // Decrease size
    return popped;                  // Return popped element
  }

  // Function to get the front element without removing it
  int top() {
    if (start == -1) {              // Check for empty queue
      cout << "Queue is Empty" << endl;
      exit(1);
    }
    return arr[start];              // Return front element
  }

  // Function to return current queue size
  int size() {
    return currSize;
  }
};

// Main function to test the Queue
int main() {
  Queue q(6);                // Create a queue of size 6

  q.push(4);                 // Add 4 → Queue: [4]
  q.push(14);                // Add 14 → Queue: [4, 14]
  q.push(24);                // Add 24 → Queue: [4, 14, 24]
  q.push(34);                // Add 34 → Queue: [4, 14, 24, 34]

  // Show the front element without removing it
  cout << "The peek of the queue before deleting any element " << q.top() << endl;

  // Show the size of the queue
  cout << "The size of the queue before deletion " << q.size() << endl;

  // Remove the front element
  cout << "The first element to be deleted " << q.pop() << endl;

  // Show the new front element
  cout << "The peek of the queue after deleting an element " << q.top() << endl;

  // Show the size after deletion
  cout << "The size of the queue after deleting an element " << q.size() << endl;

  return 0;
}
