#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    // Function to check if the i-th bit of number n is set (1)
    bool checkIthBit(int n, int i) {
        string binary = "";
        // Convert the number into its binary representation
        while (n > 0) {
            binary += (n % 2 == 0 ? '0' : '1');  // Append '0' or '1' depending on the least significant bit
            n /= 2;  // Move to the next higher bit
        }

        // If the bit index is greater than the length of the binary string, the bit is 0
        if (i >= binary.size()) return false;

        // Return true if the i-th bit is 1, otherwise false
        return binary[i] == '1';
    }
};


class Solution {
public:
    // Function to check if the i-th bit of number n is set (1)
    bool checkIthBit(int n, int i) {
        // Check if the i-th bit is set using bitwise AND operation
        return (n & (1 << i)) != 0;  // If the i-th bit is 1, the result will be non-zero
    }
};


// Main function to test the solution
int main() {
    Solution sol;
    int num = 5;  // Binary: 101
    int bitIndex = 2;  // Check the 2nd bit (0-based index)

    if (sol.checkIthBit(num, bitIndex)) {
        cout << "The " << bitIndex << "-th bit of " << num << " is set (1)." << endl;
    } else {
        cout << "The " << bitIndex << "-th bit of " << num << " is not set (0)." << endl;
    }

    return 0;
}
