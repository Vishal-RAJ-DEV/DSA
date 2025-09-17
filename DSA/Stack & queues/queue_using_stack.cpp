#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class MyQueue {
    stack<int> stack1, stack2;

public:
    // Enqueue (push to queue)
    void PUSH(int x) {
        stack1.push(x);
    }

    // Dequeue (remove from front)
    int POP() {
        if (stack2.empty()) {
            while (!stack1.empty()) {
                stack2.push(stack1.top());
                stack1.pop();
            }
        }
        int front = stack2.top();
        stack2.pop();
        return front;
    }

    // Peek front element
    int peek() {
        if (stack2.empty()) {
            while (!stack1.empty()) {
                stack2.push(stack1.top());
                stack1.pop();
            }
        }
        return stack2.top();
    }

    // Check if queue is empty
    bool empty() {
        return stack1.empty() && stack2.empty();
    }
};
int main(){
    MyQueue q;
    q.PUSH(1);
    q.PUSH(2);
    q.PUSH(3);
    cout << "Front element: " << q.peek() << endl; // Should print 1
    cout << "Dequeue: " << q.POP() << endl; // Should remove and print 1
    cout << "Front element after dequeue: " << q.peek() << endl; // Should print 2
    cout << "Is queue empty? " << (q.empty() ? "Yes" : "No") << endl; // Should print No
    cout << "Dequeue: " << q.POP() << endl; // Should remove and print 2
    cout << "Dequeue: " << q.POP() << endl; // Should remove and print 3
    return 0;
}
