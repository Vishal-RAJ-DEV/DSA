#include <iostream>
#include <bits/stdc++.h>
using namespace std;

/*
 * ================================================================
 *  DESIGN: Circular Double-Ended Queue (Deque)
 * ================================================================
 *  This implements MyCircularDeque — a circular array-based deque
 *  with fixed maximum capacity.
 *
 *  OPERATIONS:
 *    insertFront(val)  → Insert at front.   Returns true if successful.
 *    insertLast(val)   → Insert at rear.    Returns true if successful.
 *    deleteFront()     → Remove from front. Returns true if successful.
 *    deleteLast()      → Remove from rear.  Returns true if successful.
 *    getFront()        → Get front element. Returns -1 if empty.
 *    getRear()         → Get rear element.  Returns -1 if empty.
 *    isEmpty()         → True if empty.
 *    isFull()          → True if full.
 *
 * ----------------------------------------------------------------
 *  KEY CHANGES FROM THE ORIGINAL LINEAR QUEUE:
 * ----------------------------------------------------------------
 *  1. ORIGINAL had only push (insertLast) and pop (deleteFront).
 *     NOW: insertFront + insertLast + deleteFront + deleteLast.
 *
 *  2. ORIGINAL had a linear enqueue/dequeue with circular wrap.
 *     NOW: Both ends wrap circularly.
 *       - insertFront: start = (start - 1 + k) % k  (circular left)
 *       - deleteFront: start = (start + 1) % k       (circular right)
 *       - insertLast:  end   = (end + 1) % k          (circular right)
 *       - deleteLast:  end   = (end - 1 + k) % k      (circular left)
 *
 *  3. ORIGINAL used start=-1, end=-1 as empty sentinel.
 *     NOW: Same empty representation, with proper wraparound for
 *     both front and rear insertions/deletions.
 *
 *  4. ORIGINAL exited program on full/empty.
 *     NOW: Returns bool/false as per LeetCode spec.
 *
 *  5. ORIGINAL used start and end names.
 *     NOW: Same, but with front/rear terminology in methods.
 * ================================================================
 */

class MyCircularDeque {
private:
    int* arr;           // Dynamic circular array
    int front;          // Index of the front element
    int rear;           // Index of the rear element
    int size;           // Current number of elements
    int capacity;       // Maximum capacity

public:
    // Constructor: Initialize deque with max size k
    MyCircularDeque(int k) {
        capacity = k;
        arr = new int[k];
        front = -1;     // Empty state
        rear = -1;
        size = 0;
    }

    /*
     * insertFront(val)
     * ---------------------------
     * Inserts at the FRONT of the deque.
     *
     * Algorithm:
     *   1. If full → return false.
     *   2. If empty → set front = rear = 0.
     *   3. Else → move front BACKWARD circularly:
     *        front = (front - 1 + capacity) % capacity
     *      (+ capacity ensures positive modulo for negative values)
     *   4. Place val at arr[front].
     *   5. Increment size, return true.
     *
     * WHY (front - 1 + k) % k?
     *   In a circular array, the front grows LEFT when inserting.
     *   If front=0, new front should be k-1 (wrap to end).
     *   (0 - 1 + k) % k = (k-1) % k = k-1 ✓
     *
     * COMPARED TO ORIGINAL:
     *   Original had NO insertFront. This is a NEW operation.
     *   It's the mirror of insertLast but moving backwards.
     */
    bool insertFront(int value) {
        if (isFull())
            return false;

        if (isEmpty()) {
            // First element: front and rear both point to 0
            front = 0;
            rear = 0;
        } else {
            // Move front one step LEFT (circular)
            front = (front - 1 + capacity) % capacity;
        }

        arr[front] = value;
        size++;
        return true;
    }

    /*
     * insertLast(val)
     * ---------------------------
     * Inserts at the REAR of the deque.
     *
     * Algorithm:
     *   1. If full → return false.
     *   2. If empty → set front = rear = 0.
     *   3. Else → move rear FORWARD circularly:
     *        rear = (rear + 1) % capacity
     *   4. Place val at arr[rear].
     *   5. Increment size, return true.
     *
     * COMPARED TO ORIGINAL push():
     *   - Original used exit(1) on full → now returns false.
     *   - Original printed messages → removed (silent operation).
     *   - Same circular logic, just renamed end → rear.
     */
    bool insertLast(int value) {
        if (isFull())
            return false;

        if (isEmpty()) {
            front = 0;
            rear = 0;
        } else {
            rear = (rear + 1) % capacity;
        }

        arr[rear] = value;
        size++;
        return true;
    }

    /*
     * deleteFront()
     * ---------------------------
     * Removes from the FRONT of the deque.
     *
     * Algorithm:
     *   1. If empty → return false.
     *   2. If only one element → reset to empty (front=rear=-1).
     *   3. Else → move front FORWARD circularly:
     *        front = (front + 1) % capacity
     *   4. Decrement size, return true.
     *
     * COMPARED TO ORIGINAL pop():
     *   - Original used exit(1) on empty → now returns false.
     *   - Original returned the popped value → now returns bool.
     *   - Same circular front advancement logic.
     */
    bool deleteFront() {
        if (isEmpty())
            return false;

        if (front == rear) {
            // Last element being removed → deque becomes empty
            front = -1;
            rear = -1;
        } else {
            // Move front one step RIGHT (circular)
            front = (front + 1) % capacity;
        }

        size--;
        return true;
    }

    /*
     * deleteLast()
     * ---------------------------
     * Removes from the REAR of the deque.
     *
     * Algorithm:
     *   1. If empty → return false.
     *   2. If only one element → reset to empty.
     *   3. Else → move rear BACKWARD circularly:
     *        rear = (rear - 1 + capacity) % capacity
     *   4. Decrement size, return true.
     *
     * COMPARED TO ORIGINAL:
     *   Original had NO way to remove from rear. This is a
     *   completely NEW operation — the mirror of deleteFront.
     *
     * WHY (rear - 1 + k) % k?
     *   Same circular wrap logic as insertFront.
     *   If rear=0, new rear should be k-1.
     *   (0 - 1 + k) % k = k-1 ✓
     */
    bool deleteLast() {
        if (isEmpty())
            return false;

        if (front == rear) {
            // Last element being removed
            front = -1;
            rear = -1;
        } else {
            // Move rear one step LEFT (circular)
            rear = (rear - 1 + capacity) % capacity;
        }

        size--;
        return true;
    }

    /*
     * getFront()
     * ---------------------------
     * Returns the front element without removing it.
     * Returns -1 if deque is empty.
     *
     * COMPARED TO ORIGINAL top():
     *   Original exited on empty → now returns -1.
     *   Same logic otherwise.
     */
    int getFront() {
        if (isEmpty())
            return -1;
        return arr[front];
    }

    /*
     * getRear()
     * ---------------------------
     * Returns the rear element without removing it.
     * Returns -1 if deque is empty.
     *
     * COMPARED TO ORIGINAL:
     *   Original had NO way to peek rear. NEW operation.
     */
    int getRear() {
        if (isEmpty())
            return -1;
        return arr[rear];
    }

    // Returns true if deque is empty
    bool isEmpty() {
        return front == -1;
    }

    // Returns true if deque is full
    bool isFull() {
        return size == capacity;
    }

    /*
     * Destructor: Free allocated memory
     * (NEW — original didn't have one, which is a memory leak)
     */
    ~MyCircularDeque() {
        delete[] arr;
    }
};

/*
 * ================================================================
 *  DRY RUN
 * ================================================================
 *  MyCircularDeque dq(5);   // capacity=5, front=-1, rear=-1, size=0
 *
 *  insertLast(1):  empty → front=0, rear=0, arr[0]=1      → [1]
 *  insertLast(2):  rear=(0+1)%5=1, arr[1]=2             → [1,2]
 *  insertFront(3): front=(0-1+5)%5=4, arr[4]=3          → [3,1,2]
 *  insertFront(4): front=(4-1+5)%5=3, arr[3]=4          → [4,3,1,2]
 *  getRear():      arr[rear]=arr[1]=2                    → 2
 *  isFull():       size=4, capacity=5                    → false
 *  deleteLast():   rear=(1-1+5)%5=0                      → [4,3,1]
 *  insertFront(5): front=(3-1+5)%5=2, arr[2]=5          → [4,3,5,1]
 *  getFront():     arr[front]=arr[2]=5                   → 5
 *
 *  Visual array state:
 *    idx:  0    1    2    3    4
 *         [1]  [2]  [5]  [4]  [3]
 *              rear      front
 *
 *    Circular traversal: 3→4→1→2→5  → front=2(5) rear=1(2)
 * ================================================================
 */

int main() {
    MyCircularDeque dq(5);

    cout << "insertLast(1): " << dq.insertLast(1) << endl;
    cout << "insertLast(2): " << dq.insertLast(2) << endl;
    cout << "insertFront(3): " << dq.insertFront(3) << endl;
    cout << "insertFront(4): " << dq.insertFront(4) << endl;
    cout << "getRear(): " << dq.getRear() << endl;
    cout << "isFull(): " << dq.isFull() << endl;
    cout << "deleteLast(): " << dq.deleteLast() << endl;
    cout << "insertFront(5): " << dq.insertFront(5) << endl;
    cout << "getFront(): " << dq.getFront() << endl;

    return 0;
}
