#include <iostream>
using namespace std;

bool isPalindrome(long long A[], int left, int right) {
    // Base case: reached or crossed the middle
    if (left >= right) {
        return true;
    }

    // If elements are different, not a palindrome
    if (A[left] != A[right]) {
        return false;
    }

    // Move toward the center
    return isPalindrome(A, left + 1, right - 1);
}

int main() {
    int N;
    cin >> N;

    long long A[N];

    for (int i = 0; i < N; i++) {
        cin >> A[i];
    }

    if (isPalindrome(A, 0, N - 1))
        cout << "YES" << endl;
    else
        cout << "NO" << endl;

    return 0;
}