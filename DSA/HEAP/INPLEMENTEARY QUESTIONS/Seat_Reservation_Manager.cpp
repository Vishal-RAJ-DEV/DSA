#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class SeatManager {
private:
    priority_queue<int , vector<int> , greater<int>>seats;
public:

    SeatManager(int n) {
        for(int i =1 ; i <= n ; i++){
            seats.push(i);
        }
    }
    
    int reserve() {
        if(!seats.empty()){
            int x = seats.top();
            seats.pop();
            return x;
        }else{
            return -1;
        }
    }
    
    void unreserve(int seatNumber) {
        seats.push(seatNumber);
    }
};

/**
 * Your SeatManager object will be instantiated and called as such:
 * SeatManager* obj = new SeatManager(n);
 * int param_1 = obj->reserve();
 * obj->unreserve(seatNumber);
 */


int main(){
    SeatManager* obj = new SeatManager(5);

    cout << "Reserved: " << obj->reserve() << endl;   // 1
    cout << "Reserved: " << obj->reserve() << endl;   // 2

    obj->unreserve(1);                                // seat 1 freed
    obj->unreserve(2);                                // seat 2 freed

    cout << "Reserved: " << obj->reserve() << endl;   // 1 (smallest available)
    cout << "Reserved: " << obj->reserve() << endl;   // 2
    cout << "Reserved: " << obj->reserve() << endl;   // 3
    cout << "Reserved: " << obj->reserve() << endl;   // 4
    cout << "Reserved: " << obj->reserve() << endl;   // 5
    cout << "Reserved: " << obj->reserve() << endl;   // -1 (no seats left)

    delete obj;
    return 0;
}
