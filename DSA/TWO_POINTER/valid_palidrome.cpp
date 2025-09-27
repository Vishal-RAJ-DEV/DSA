#include <iostream>
#include <bits/stdc++.h>
using namespace std;

bool isPalindrome(string s)
{
    int left = 0;
    int right = s.size() - 1;

    while (left <= right)
    {
        while (left < right && !isalnum(s[left])) left++; // skip non-alphanumeric characters using isalnum function that checks if the character is alphanumeric or not for  eg ' ' , '!' etc will be skipped
        while (left < right && !isalnum(s[right])) right--;

        if (tolower(s[left]) != tolower(s[right]))  // here tolower function is used to convert the character to lowercase so that we can compare the characters in a case insensitive manner
            return false;
        left++;
        right--;
    }
    return true;
}
int main()
{
    string s = "A man, a plan, a canal: Panama";
    string s1  = "race a car";
    if (isPalindrome(s1))
    {
        cout << "The string is a palindrome";
    }
    else
    {
        cout << "The string is not a palindrome";
    }
    cout<<endl;
    if (isPalindrome(s))
    {
        cout << "The string is a palindrome";
    }
    else
    {
        cout << "The string is not a palindrome";
    }
    return 0;
}
