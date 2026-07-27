#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    // Store the complete Pascal Triangle.
    vector<vector<long long>> pascal(n);

    // Generate every row.
    for (int i = 0; i < n; i++)
    {
        // ith row contains (i+1) elements.
        pascal[i].resize(i + 1);

        // First and last element are always 1.
        pascal[i][0] = pascal[i][i] = 1;

        // Compute only the middle elements.
        for (int j = 1; j < i; j++)
        {
            /*
                Current element =
                Upper Left + Upper Right

                Example

                     1   2   1
                       \ /
                        3
            */
            pascal[i][j] = pascal[i - 1][j - 1] + pascal[i - 1][j];
        }
    }

    // Print Pascal Triangle.
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j <= i; j++)
        {
            cout << pascal[i][j] << " ";
        }
        cout << "\n";
    }

    return 0;
}