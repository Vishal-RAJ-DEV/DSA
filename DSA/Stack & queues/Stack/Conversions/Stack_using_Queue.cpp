#include<bits/stdc++.h>
using namespace std;


//using the two queues to implement the stack
//algorithm :-
//1. Push operation: When we push an element, we enqueue it to the empty queue (q2) and then dequeue all elements from the other queue (q1) and enqueue them to q2. Finally, we swap the names of the two queues.
//2. Pop operation: We simply dequeue from the non-empty queue (q1).
//3. Top operation: We return the front element of the non-empty queue (q1).
//4. Empty operation: We check if the non-empty queue (q1) is empty.
//Time Complexity: O(n) for push operation, O(1) for pop, top and empty operations.
class MyStack {
public:
    queue<int> q1, q2;

    MyStack() {

    }

    void push(int x) {

        // Insert new element into q2
        q2.push(x);

        // Move all existing elements to q2
        while (!q1.empty()) {
            q2.push(q1.front());
            q1.pop();
        }

        // Swap q1 and q2
        swap(q1, q2);
    }

    int pop() {

        int val = q1.front();
        q1.pop();

        return val;
    }

    int top() {

        return q1.front();
    }

    bool empty() {

        return q1.empty();
    }
};

//after pushing a element we will rotate the queue to make the last added element at the front of the queue
//here we are repusing the x queue again and again to simuate the stack behaviour
class Stack {
  queue < int > q; //it is inbuilt function of the queue 
  public:
    void Push(int x) {
      int s = q.size();
      q.push(x);
      for (int i = 0; i < s; i++) {

        q.push(q.front());
        q.pop();
      }
    }
  int Pop() {
    int n = q.front();// Get the front element
    q.pop(); // Remove the front element
    return n;//
  }
  int Top() {
    return q.front();
  }
  int Size() {
    return q.size();
  }
};

int main() {
  Stack s;
  s.Push(3);
  s.Push(2);
  s.Push(4);
  s.Push(1);
  cout << "Top of the stack: " << s.Top() << endl;
  cout << "Size of the stack before removing element: " << s.Size() << endl;
  cout << "The deleted element is: " << s.Pop() << endl;
  cout << "Top of the stack after removing element: " << s.Top() << endl;
  cout << "Size of the stack after removing element: " << s.Size();

}