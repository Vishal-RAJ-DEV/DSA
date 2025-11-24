#include <iostream>
#include <bits/stdc++.h>

using namespace std;
int fruitIntoBasket(vector<int> &fruits)
{
    int n = fruits.size();
    int maxLen = 0;
    for (int i = 0; i < n; i++)
    {
        set<int> basket;
        for (int j = i; j < n; j++)
        {
            if(basket.size() > 2 ) break;
            basket.insert(fruits[j]);
            maxLen  = max(maxLen , j - i + 1);
        }
        
    }
    return maxLen;
}
int main()
{
    vector<int> fruits = {1, 2, 3, 2, 2};
    cout << fruitIntoBasket(fruits) << endl;

    return 0;
}
