#include <bits/stdc++.h>
using namespace std;

/*
QUESTION:
You want to bake some cookies. There are n ingredients.
- a[i] = grams of ingredient i needed per cookie
- b[i] = grams of ingredient i you already have
- k    = grams of "magic powder" that can substitute ANY missing ingredient

Find the MAXIMUM number of cookies you can bake.

You can use magic powder to fill the shortage of any ingredient.
Total magic powder used across all ingredients cannot exceed k.

EXAMPLE:
n=2, k=1
a = [1, 2]   (need 1g of ingr0, 2g of ingr1 per cookie)
b = [4, 3]   (have 4g of ingr0, 3g of ingr1)

Can we make 3 cookies?
  ingr0: need 3*1=3, have 4 -> enough
  ingr1: need 3*2=6, have 3 -> need 3g powder
  Total powder needed = 3 > k=1 -> NO

Can we make 2 cookies?
  ingr0: need 2*1=2, have 4 -> enough
  ingr1: need 2*2=4, have 3 -> need 1g powder
  Total powder needed = 1 <= k=1 -> YES

So answer = 2.
*/

bool canMake(long long cookies,
             vector<int>& a,
             vector<int>& b,
             int k) {

    long long powderNeeded = 0;

    for (int i = 0; i < a.size(); i++) {
        // Total grams of ingredient i needed for 'cookies' cookies
        long long required = 1LL * cookies * a[i];

        // If we don't have enough, use magic powder to fill the gap
        if (required > b[i]) {
            powderNeeded += required - b[i];
        }

        // Early exit: if powder needed already exceeds k, impossible
        if (powderNeeded > k)
            return false;
    }

    return true;
}

/*
DRY RUN of canMake:

Example:
n = 2, k = 1
a = [1, 2]   (need per cookie)
b = [4, 3]   (have in stock)

--- canMake(cookies=2) ---
i=0: required = 2 * 1 = 2, have b[0]=4, 2 <= 4 -> no powder needed
i=1: required = 2 * 2 = 4, have b[1]=3, 4 > 3 -> powderNeeded += 4-3 = 1
powderNeeded=1 <= k=1 -> return true

--- canMake(cookies=3) ---
i=0: required = 3 * 1 = 3, have 4, 3 <= 4 -> no powder
i=1: required = 3 * 2 = 6, have 3, 6 > 3 -> powderNeeded += 6-3 = 3
powderNeeded=3 > k=1 -> return false

So max cookies = 2.
*/

int main() {

    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;

    vector<int> a(n), b(n);

    for (int i = 0; i < n; i++)
        cin >> a[i];

    for (int i = 0; i < n; i++)
        cin >> b[i];

    // Binary search for max cookies
    // low = 0 (always possible), high = 2e9 (upper bound)
    long long low = 0;
    long long high = 2e9;
    long long ans = 0;

    while (low <= high) {

        long long mid = low + (high - low) / 2;

        if (canMake(mid, a, b, k)) {
            ans = mid;        // feasible, try for more
            low = mid + 1;
        } else {
            high = mid - 1;   // not feasible, reduce
        }
    }

    cout << ans << '\n';

    return 0;
}
