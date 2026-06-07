#include <iostream>
#include <bits/stdc++.h>
using namespace std;

string largestOddNumber(string num)
{
    int n = num.size();
    for (int i = n - 1; i >= 0; i--)   //loop through the string in reverse so we can find the last odd digit
    {
        if ((num[i] - '0') % 2 != 0)  //here data is minus by the '0' to convert char to int 
        {
            return num.substr(0, i + 1); // here 0 is the index where it is staring and another is the number its going to print
            break;
        }
    }
    return "";
}

int main()
{
    string num;
    cin >> num;
    cout << largestOddNumber(num) << endl;
    return 0;
}