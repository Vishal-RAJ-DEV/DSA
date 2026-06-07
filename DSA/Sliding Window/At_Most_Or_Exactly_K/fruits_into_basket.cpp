#include <iostream>
#include <bits/stdc++.h>
/*
Problem Statement: There is only one row of fruit trees on the farm, oriented left to right. An integer array called fruits represents the trees, where fruits[i] denotes the kind of fruit produced by the ith tree.
The goal is to gather as much fruit as possible, adhering to the owner's stringent rules :

There are two baskets available, and each basket can only contain one kind of fruit. The quantity of fruit each basket can contain is unlimited.
Start at any tree, but as you proceed to the right, select exactly one fruit from each tree, including the starting tree. One of the baskets must hold the harvested fruits.
Once reaching a tree with fruit that cannot fit into any basket, stop.

Input :fruits = [1, 2, 1]
Output :3
Explanation : We will start from first tree.
The first tree produces the fruit of kind '1' and we will put that in the first basket.
The second tree produces the fruit of kind '2' and we will put that in the second basket.
The third tree produces the fruit of kind '1' and we have first basket that is already holding fruit of kind '1'. So we will put it in first basket.
Hence we were able to collect total of 3 fruits.

Input : fruits = [1, 2, 3, 2, 2]
Output : 4
Explanation : we will start from second tree.
The first basket contains fruits from second , fourth and fifth.
The second basket will contain fruit from third tree.
Hence we collected total of 4 fruits.
*/
using namespace std;

//brute force approach
// time complexity is o(n^2) because of nested loops
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

//appproch sliding window
// worst case time complexity is o(n + n) = o(2n) = o(n) because in while loop left and right pointer will traverse the array only once
int fruitIntoBasket1(vector<int> &fruits){
    int n = fruits.size();
    int left = 0;
    int right = 0;
    int maxLen = 0;
    set<int>basket;
    while(right < n ){
        basket.insert(fruits[right]);
        if(basket.size() > 2  ){  //use while loop here because after removing one fruit we may still have more than 2 fruits in the basket
            basket.erase(fruits[left]); //so here we are not breaking the loop instead we are removing the left most fruit from the basket
            left++;
        }
        maxLen = max(maxLen , right - left + 1);
        right++;
    }
    return maxLen;
}

//optimized approch 
int main()
{
    vector<int> fruits = {1, 2, 3, 2, 2};
    cout << fruitIntoBasket(fruits) << endl;
    cout << fruitIntoBasket1(fruits) << endl;
    return 0;
}
