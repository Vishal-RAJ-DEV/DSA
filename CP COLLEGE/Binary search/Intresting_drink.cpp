#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

/*
 * PROBLEM: Interesting Drink (from CP College - Binary Search)
 * ---------------------------------------------------------------
 * Vanja has n drinks, each with a price.
 * She has q friends. Each friend has some amount of money.
 * For each friend, count how many drinks they can afford to buy.
 *
 * A friend can buy a drink if: drink_price <= friend's_money
 *
 * INPUT:
 *   n = number of different drinks
 *   prices = price of each drink
 *   q = number of friends (queries)
 *   For each friend: their money
 *
 * OUTPUT:
 *   For each friend, print how many drinks they can afford
 *
 * EXAMPLE:
 *   Input:
 *     5
 *     6 4 8 2 5
 *     4
 *     3
 *     7
 *     10
 *     1
 *
 *   Sorted prices: {2, 4, 5, 6, 8}
 *
 *   Friend 1 (money=3):  can afford {2}         → count = 1
 *   Friend 2 (money=7):  can afford {2,4,5,6}  → count = 4
 *   Friend 3 (money=10): can afford {2,4,5,6,8} → count = 5
 *   Friend 4 (money=1):  can afford {}          → count = 0
 *
 *   Output: 1 4 5 0
 *
 * HOW LOWER_BOUND / UPPER_BOUND GIVES THE ANSWER:
 * ---------------------------------------------------------------
 * After sorting prices, the array looks like:
 *   prices = {2, 4, 5, 6, 8}
 *            ↑  ↑  ↑  ↑  ↑
 *           [0][1][2][3][4]   ← indices
 *
 * For a friend with money = 7:
 *   We need to count how many prices <= 7
 *
 *   upper_bound(7) returns iterator to first element > 7
 *   In sorted array: {2, 4, 5, 6, 8}
 *                            ↑
 *                      upper_bound points here (index 4, value 8)
 *
 *   The iterator points to index 4.
 *   This means: elements at indices 0,1,2,3 are <= 7
 *   Count = 4 (which is the index itself!)
 *
 * WHY DOES ITERATOR - begin() GIVE THE COUNT?
 * ---------------------------------------------------------------
 * In C++, subtracting two iterators gives the number of elements
 * between them.
 *
 *   upper_bound(money) - prices.begin()
 *   = (iterator to first element > money) - (iterator to first element)
 *   = number of elements before that position
 *   = count of elements <= money
 *
 * This is because the array is SORTED, so all elements <= money
 * are grouped at the beginning.
 *
 * VISUAL:
 *   money = 7
 *
 *   Sorted prices: {2, 4, 5, 6, 8}
 *   Can buy?        ✓  ✓  ✓  ✓  ✗
 *                   ← count = 4 →  ↑ upper_bound points here
 *
 *   upper_bound returns iterator at index 4
 *   4 - begin = 4 elements that are <= 7
 *
 * WHY NOT lower_bound?
 * ---------------------------------------------------------------
 *   lower_bound(7) → first element >= 7 → would give index 4 (value 8)
 *   But 8 > 7, so friend can't afford it!
 *
 *   upper_bound(7) → first element > 7 → also gives index 4 (value 8)
 *   Wait, same result? Let's check with money = 6:
 *
 *   money = 6:
 *     lower_bound(6) → first >= 6 → index 3 (value 6) → count would be 3
 *     upper_bound(6) → first > 6 → index 4 (value 8) → count = 4 ✓
 *
 *   Friend with 6 coins CAN buy drink priced 6!
 *   So upper_bound is correct: it includes elements EQUAL to money.
 *
 * KEY DIFFERENCE:
 *   lower_bound(x) → first element >= x (doesn't include x if present)
 *   upper_bound(x) → first element > x  (INCLUDES x if present)
 *
 *   Since we want "price <= money" (inclusive), upper_bound is correct.
 */

int main() {
    int n;
    cin >> n;

    vector<int> prices(n);

    // Input drink prices
    for (int i = 0; i < n; i++) {
        cin >> prices[i];
    }

    // SORT is essential — binary search only works on sorted arrays
    // After sorting, all affordable drinks group at the beginning
    sort(prices.begin(), prices.end());

    int q;
    cin >> q;

    // Process each friend's query
    while (q--) {
        int money;
        cin >> money;

        // upper_bound(money) returns iterator to first price > money
        // Subtracting prices.begin() converts iterator to INDEX
        // That index = count of prices <= money = drinks they can afford
        //
        // Example: money = 7, sorted = {2,4,5,6,8}
        //   upper_bound(7) → iterator to 8 (index 4)
        //   4 - begin = 4 drinks affordable
        int answer = upper_bound(
            prices.begin(),
            prices.end(),
            money
        ) - prices.begin();

        cout << answer << '\n';
    }

    return 0;
}