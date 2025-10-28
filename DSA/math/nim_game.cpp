#include <iostream>
#include <bits/stdc++.h>
using namespace std;

/*
You are playing the following Nim Game with your friend:

Initially, there is a heap of stones on the table.
You and your friend will alternate taking turns, and you go first.
On each turn, the person whose turn it is will remove 1 to 3 stones from the heap.
The one who removes the last stone is the winner.
Given n, the number of stones in the heap, return true if you can win the game assuming both you and your friend play optimally, otherwise return false.

 

Example 1:

Input: n = 4
Output: false
Explanation: These are the possible outcomes:
1. You remove 1 stone. Your friend removes 3 stones, including the last stone. Your friend wins.
2. You remove 2 stones. Your friend removes 2 stones, including the last stone. Your friend wins.
3. You remove 3 stones. Your friend removes the last stone. Your friend wins.
In all outcomes, your friend wins.
Example 2:

Input: n = 1
Output: true*/

bool canWinNim(int n) {
    // If n is a multiple of 4, you will lose if your friend plays optimally
    return n % 4 != 0;
}

//here the instition is if there are 4 stone you will lose the game because whatever you take 1,2,3 your friend will take the rest and win the game
//if there are 5 stone you will win the game because whatever you take 1,2,3 your friend will take the rest and you will win the game
//if there are 6 stone you will win the game because whatever you take 1,2,3 your friend will take the rest and you will win the game
//if there are 7 stone you will win the game because whatever you take 1,2,3 your friend will take the rest and you will win the game
//if there are 8 stone you will lose the game because whatever you take 1,2,3 your friend will take the rest and win the game
//so the pattern is if there are multiple of 4 you will lose the game otherwise you will win the game
//time complexity is O(1) and space complexity is O(1)
//point is always leave the multiple of 4 to your friend so you can win the game
int main(){
    int n;
    cin >> n;
    cout << canWinNim(n) << endl;
    return 0;
}