#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool isPalindrome(string s)
    {
        int left = 0;
        int right = s.size() - 1;

        while(left < right)
        {
            if(s[left] != s[right])
                return false;

            left++;
            right--;
        }

        return true;
    }

    bool checkAsciiPalindrome(string s)
    {
        string bits = "";

        for(char c : s)
        {
            int x = c;   // ASCII value

            // Exactly 8 bits
            for(int i = 7; i >= 0; i--)
            {
                if(x & (1 << i))
                    bits += '1';
                else
                    bits += '0';
            }
        }

        return isPalindrome(bits);
    }
};



int main(){
    return 0;
}