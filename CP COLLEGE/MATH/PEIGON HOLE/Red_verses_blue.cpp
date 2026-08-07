#include <bits/stdc++.h>
using namespace std;

int main()
{
	int t;
	cin >> t; // Read the number of test cases
	while (t--)
	{
		int n, r, b;
		cin >> n >> r >> b; // Read n, r, b for each test case
		string s; // Initialize the result string

		// Calculate the number of 'R's to be placed between each 'B'
		int length_of_red = r / (b + 1);
		// Calculate the extra 'R's that need to be distributed
		int extra_red = r % (b + 1);

		// Loop to construct the string with minimum consecutive wins
		for (int times = 1; times <= b + 1; times++)
		{
			// Add the calculated number of 'R's
			for (int i = 0; i < length_of_red; i++)
				s += 'R';

			// Distribute the extra 'R's
			if (extra_red > 0)
			{
				s += 'R';
				extra_red--;
			}

			// Add 'B' except for the last segment
			if (times != b + 1)
				s += 'B';
		}

		// Output the constructed string
		cout << s << endl;
	}
	return 0;
}

// Time Complexity (TC): O(100)
// Space Complexity (SC): O(100)
