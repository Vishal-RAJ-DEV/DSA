#include <iostream>
#include <bits/stdc++.h>
using namespace std;
void printdivisor(int n) {
    vector<int> list;
    for (int i = 1; i * i <= n; i++) {
        if (n % i == 0) {          
            list.push_back(i);      

            if ((n / i) != i) {
                list.push_back(n / i);
            }
        }
    }


    sort(list.begin(), list.end());
    for (auto it : list) cout << it << endl;

}

int main() {
    int n;
    cout << "Enter your number: ";
    cin >> n;
    printdivisor(n);
    return 0;
}

