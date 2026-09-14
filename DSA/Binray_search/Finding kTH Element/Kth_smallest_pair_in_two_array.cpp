

/*
Description
Given two arrays A of size N and B of size M and an integer K. Create a new array C of size N*M consisting of A[i]+B[j] for 1≤i≤N, 1≤j≤M. Find the Kth smallest element in the array C.


Input Format
The first line contains T, the number of test cases (1<=T<=10000).
The first line contains 3 space-separated integer N, M, K where 1<=N<=10^6, 1<=M<=10^6, 1<=K<=N*M.
Next line contains N space-separated integers (0<=Ai<=1e4).
Next line contains M space-separated integers (0<=Bi<=1e4).
Sum of min(N, M) across all test cases<=10^5.

Output Format
For each test case print the Kth smallest element in the array C.

Sample Input 1 
1
3 3 6
1 2 3
4 5 6
Sample Output 1 
7


Note
Array C -> [1+4,1+5,1+6,2+4,2+5,2+6,3+4,3+5,3+6] -> [5,6,7,6,7,8,7,8,9]
Array C after sorting - [5,6,6,7,7,7,8,8,9]
6th element is 7.

*/
#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) {
        int N, M;
        ll K;

        cin >> N >> M >> K;

        vector<int> A(N);
        vector<int> B(M);

        for (int &x : A) cin >> x;
        for (int &x : B) cin >> x;

        // We want to iterate over the smaller array.
        if (A.size() > B.size()) {
            swap(A, B);
        }

        // Sort both arrays.
        sort(A.begin(), A.end());
        sort(B.begin(), B.end());

        int low = 0;
        int high = 20000;

        while (low < high) {
            int mid = low + (high - low) / 2;

            ll count = 0;

            for (int x : A) {
                int need = mid - x;

                // Number of elements in B <= need
                count += upper_bound(B.begin(), B.end(), need)
                         - B.begin();

                // No need to count further if we already reached K.
                if (count >= K)
                    break;
            }

            if (count >= K) {
                // mid can be the answer.
                high = mid;
            } else {
                // mid is too small.
                low = mid + 1;
            }
        }

        cout << low << '\n';
    }

    return 0;
}