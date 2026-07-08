#include <iostream>
#include <bits/stdc++.h>
using namespace std;

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
struct ListNode {
    int val;
    ListNode *next;
    ListNode(): val(0), next(nullptr) {}
    ListNode(int x): val(x), next(nullptr) {}
    ListNode(int x, ListNode *next): val(x), next(next) {}
};
class Solution {
public:
    int getDecimalValue(ListNode* head) {
        ListNode * temp = head;
        int ans = 0 ;
        while( temp != nullptr){
            ans = ans << 1;
            ans  |= temp->val;
            temp = temp->next;
        }

        return ans;
    }
};




int main(){
    // Read a line of input representing binary digits for the linked list.
    // Accept either: "1 0 1 1" (space separated) or "1011" (contiguous).
    string line;
    if(!getline(cin, line)) return 0;
    // trim
    auto l = line.find_first_not_of(" \t\r\n");
    if(l==string::npos) return 0;
    auto r = line.find_last_not_of(" \t\r\n");
    string s = line.substr(l, r-l+1);

    vector<int> bits;
    // detect space separated tokens
    bool hasSpace = false;
    for(char c: s) if(isspace((unsigned char)c)) { hasSpace = true; break; }
    if(hasSpace){
        stringstream ss(s);
        string tok;
        while(ss >> tok){
            for(char c: tok){
                if(c=='0' || c=='1') { bits.push_back(c - '0'); break; }
            }
        }
    } else {
        for(char c: s){
            if(c=='0' || c=='1') bits.push_back(c - '0');
        }
    }

    // build linked list
    if(bits.empty()) return 0;
    ListNode* head = new ListNode(bits[0]);
    ListNode* cur = head;
    for(size_t i=1;i<bits.size();++i){
        cur->next = new ListNode(bits[i]);
        cur = cur->next;
    }

    Solution sol;
    int result = sol.getDecimalValue(head);
    cout << result << '\n';

    // free list
    while(head){
        ListNode* tmp = head->next;
        delete head;
        head = tmp;
    }
    return 0;
}


