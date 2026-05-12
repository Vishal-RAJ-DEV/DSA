#include <iostream>
#include <vector>
using namespace std;

// Function to count 0s and 1s in the array
vector<int> countZerosOnes(vector<int> &arr)
{
    int count0 = 0;
    int count1 = 0;
    int n = arr.size();

    for (int i = 0; i < n; i++)
    {
        if (arr[i] == 0)
            count0++;
        else if (arr[i] == 1)
            count1++;
    }
    vector<int> result = {count0, count1};
    return result;
}
// Optimal solution: Dutch National Flag algorithm for sorting 0s and 1s
void sort(vector<int> &arr) {
    int n = arr.size();
    int zero = 0;
    for (int i = 0; i < n; i++) {
        if (arr[i] == 0) {   // If current element is 0
            swap(arr[i], arr[zero]);  //swap the current element with the element at the zero index by that zero will to zero 
            zero++;// then increase the the zero index
        }
    }
}

int main()
{
    vector<int> arr = {0, 1, 0, 1, 1, 0, 0, 1, 1, 0};
    vector<int> counts = countZerosOnes(arr);
    
    cout << "Number of 0s: " << counts[0] << endl;
    cout << "Number of 1s: " << counts[1] << endl;

    cout<<endl;

    sort(arr);
    for(auto &it : arr){   
        cout<<it<<" ";
    }

    return 0;
}
