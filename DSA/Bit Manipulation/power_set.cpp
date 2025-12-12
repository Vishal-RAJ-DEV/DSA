#include <iostream>
#include <bits/stdc++.h>
using namespace std;

 // Function to return all subsequences of string s
    vector<string> getSubsequences(string s) {
        // Length of input string
        int n = s.size();

        // Total subsequences = 2^n
        int total = 1 << n;

        // Vector to store all subsequences
        vector<string> subsequences;

        // Iterate over all bit masks from 0 to 2^n - 1
        for (int mask = 0; mask < total; mask++) {
            // Temporary subsequence string
            string subseq = "";

            // Check each bit position in mask
            for (int i = 0; i < n; i++) {
                // If i-th bit of mask is set, include s[i]
                if (mask & (1 << i)) {
                    subseq += s[i];
                }
            }

            // Store the formed subsequence
            subsequences.push_back(subseq);
        }

        // Return all generated subsequences
        return subsequences;
    }


int main(){
    string s;
    cin>>s;
    vector<string> subsequences = getSubsequences(s);
    for(auto &it : subsequences){
        cout<<it<<endl;
    }
    return 0;
}

/*

🌟 FULL DRY RUN FOR s = "abc"
mask = 0 → (000)

Binary: 000

Check bits:

i	1<<i	mask & (1<<i)	Take?	Char
0	001	000 & 001 = 0	No	-
1	010	000 & 010 = 0	No	-
2	100	000 & 100 = 0	No	-

➡ subseq = "" (empty)

mask = 1 → (001)

Binary: 001

i	1<<i	mask & (1<<i)	Take?	Char
0	001	001 & 001 = 1	Yes	'a'
1	010	001 & 010 = 0	No	-
2	100	001 & 100 = 0	No	-

➡ subseq = "a"

mask = 2 → (010)

Binary: 010

i	1<<i	mask & (1<<i)	Take?	Char
0	001	010 & 001 = 0	No	-
1	010	010 & 010 = 1	Yes	'b'
2	100	010 & 100 = 0	No	-

➡ subseq = "b"

mask = 3 → (011)

Binary: 011

i	1<<i	mask & (1<<i)	Take?	Char
0	001	011 & 001 = 1	Yes	'a'
1	010	011 & 010 = 1	Yes	'b'
2	100	011 & 100 = 0	No	-

➡ subseq = "ab"

mask = 4 → (100)

Binary: 100

i	1<<i	mask & (1<<i)	Take?	Char
0	001	100 & 001 = 0	No	-
1	010	100 & 010 = 0	No	-
2	100	100 & 100 = 1	Yes	'c'

➡ subseq = "c"

mask = 5 → (101)

Binary: 101

i	1<<i	mask & (1<<i)	Take?	Char
0	001	101 & 001 = 1	Yes	'a'
1	010	101 & 010 = 0	No	-
2	100	101 & 100 = 1	Yes	'c'

➡ subseq = "ac"

mask = 6 → (110)

Binary: 110

i	1<<i	mask & (1<<i)	Take?	Char
0	001	110 & 001 = 0	No	-
1	010	110 & 010 = 1	Yes	'b'
2	100	110 & 100 = 1	Yes	'c'

➡ subseq = "bc"

mask = 7 → (111)

Binary: 111

i	1<<i	mask & (1<<i)	Take?	Char
0	001	111 & 001 = 1	Yes	'a'
1	010	111 & 010 = 1	Yes	'b'
2	100	111 & 100 = 1	Yes	'c'

➡ subseq = "abc"

🌸 Final Output

All subsequences:

"", "a", "b", "ab", "c", "ac", "bc", "abc"

💡 How bits actually work here

Every number from 0 to 2ⁿ−1 represents a unique combination.

Each bit position maps to one character.

1 means include, 0 means exclude.

This produces ALL subsets because binary covers all possible include/exclude patterns.

If you want babe, I can also explain:
🌸 why 1 << i works
🌸 why total subsets = 1 << n
🌸 time complexity
🌸 space complexity
🌸 difference vs recursion

Just say “yes babe” ❤️😊


*/