#include <iostream>
#include <bits/stdc++.h>
using namespace std;

// Helper recursive function to generate subsequences
void helper(string &s, int index, string &current, vector<string> &result)
{
    // Original string length = n
    // Valid indices = 0, 1, 2, ..., n-1
    // When index = n → We've gone beyond all valid indices
    //                 → All decisions made
    //                 → Base case reached
    // Base case: If index reaches string length, add current subsequence to result
    if (index == s.size())
    {
        result.push_back(current);
        return;
    }

    // Exclude current character and recurse
    helper(s, index + 1, current, result);

    // Include current character and recurse
    current.push_back(s[index]);
    helper(s, index + 1, current, result);

    // Backtrack: remove last character before returning to previous call
    current.pop_back();
}

// Function to return all subsequences of string s
vector<string> getSubsequences(string s)
{
    // Vector to store all subsequences
    vector<string> result;
    // Current subsequence being built
    string current = "";
    helper(s, 0, current, result);
    return result;
}

int main()
{

    string s;
    cin >> s;
    vector<string> subsequences = getSubsequences(s);
    for (auto &it : subsequences)
    {
        cout << it << endl;
    }

    return 0;
}
/*
🌳 Complete Recursion Tree for String "AB"

helper("AB", 0, "", result)
|
┌─────────┴─────────┐
│                   │
🚫 Exclude 'A'        ✅ Include 'A'
          (current = "")        (current = "A")
                    │                   │
                    helper("AB", 1, "", result)  helper("AB", 1, "A", result)
                    │                   │
                    ┌───────┴───────┐    ┌─────┴─────┐
            │               │    │           │
    🚫 Exclude 'B'   ✅ Include 'B'  🚫 Exclude 'B'  ✅ Include 'B'
    (current = "")   (current = "B") (current = "A") (current = "AB")
    │               │          │             │
    BASE CASE        BASE CASE    BASE CASE     BASE CASE
    result.add("")   result.add("B") result.add("A") result.add("AB")
*/

/*

Step-by-Step Execution with Call Stack
🎯 Call 1: helper("AB", 0, "", result)
Call Stack: [helper("AB", 0, "", result)]
- index = 0, current = "", s[0] = 'A'
- index < s.size() → Continue
- First: Exclude 'A' → Call helper("AB", 1, "", result)

🎯 Call 2: helper("AB", 1, "", result)
Call Stack: [helper("AB", 0, "", result)]
            [helper("AB", 1, "", result)]
- index = 1, current = "", s[1] = 'B'
- index < s.size() → Continue
- First: Exclude 'B' → Call helper("AB", 2, "", result)

🎯 Call 3: helper("AB", 2, "", result) ✅ BASE CASECall Stack: [helper("AB", 0, "", result)]
            [helper("AB", 1, "", result)]
            [helper("AB", 2, "", result)]
- index = 2, current = ""
- index == s.size() → BASE CASE
- result.push_back("") → result = [""]
- RETURN ↑

🔄 Back to Call 2: Include 'B'
Call Stack: [helper("AB", 0, "", result)]
            [helper("AB", 1, "", result)]
- After exclude call returns
- Include 'B': current.push_back('B') → current = "B"
- Call helper("AB", 2, "B", result)

🎯 Call 4: helper("AB", 2, "B", result) ✅ BASE CASE
Call Stack: [helper("AB", 0, "", result)]
            [helper("AB", 1, "", result)]
            [helper("AB", 2, "B", result)]
- index = 2, current = "B"
- index == s.size() → BASE CASE
- result.push_back("B") → result = ["", "B"]
- RETURN ↑

🔄 Back to Call 2: Backtrack
Call Stack: [helper("AB", 0, "", result)]
            [helper("AB", 1, "", result)]
- After include call returns
- Backtrack: current.pop_back() → current = ""
- RETURN ↑ to Call 1

🔄 Back to Call 1: Include 'A'
Call Stack: [helper("AB", 0, "", result)]
- After exclude call returns
- Include 'A': current.push_back('A') → current = "A"
- Call helper("AB", 1, "A", result)

🎯 Call 5: helper("AB", 1, "A", result)
Call Stack: [helper("AB", 0, "", result)]
            [helper("AB", 1, "A", result)]
- index = 1, current = "A", s[1] = 'B'
- First: Exclude 'B' → Call helper("AB", 2, "A", result)

🎯 Call 6: helper("AB", 2, "A", result) ✅ BASE CASE
Call Stack: [helper("AB", 0, "", result)]
            [helper("AB", 1, "A", result)]
            [helper("AB", 2, "A", result)]
- index = 2, current = "A"
- index == s.size() → BASE CASE
- result.push_back("A") → result = ["", "B", "A"]
- RETURN ↑

🔄 Back to Call 5: Include 'B'
Call Stack: [helper("AB", 0, "", result)]
            [helper("AB", 1, "A", result)]
- After exclude call returns
- Include 'B': current.push_back('B') → current = "AB"
- Call helper("AB", 2, "AB", result)

🎯 Call 7: helper("AB", 2, "AB", result) ✅ BASE CASE
Call Stack: [helper("AB", 0, "", result)]
            [helper("AB", 1, "A", result)]
            [helper("AB", 2, "AB", result)]
- index = 2, current = "AB"
- index == s.size() → BASE CASE
- result.push_back("AB") → result = ["", "B", "A", "AB"]
- RETURN ↑

 Final Backtrack Chain
Call 5: current.pop_back() → current = "A", RETURN ↑
Call 1: current.pop_back() → current = "", RETURN ↑
Program ends

*/