#include <bits/stdc++.h>
using namespace std;
long long factorial(int n)
{
    long long ans = 1;
    for (int i = 2; i <= n; i++)
        ans *= i;
    return ans;
}

void UsingFactorial(){
    int n, r;
    cin >> n >> r;

    if (r > n)
    {
        cout << "Invalid\n";
        return ;
    }

    long long nPr = factorial(n) / factorial(n - r);
    long long nCr = factorial(n) / (factorial(r) * factorial(n - r));

    cout << "Permutation = " << nPr << "\n";
    cout << "Combination = " << nCr << "\n";
}


long long calNPr(int n, int r)
{
    if (r > n) return 0;

    long long ans = 1;
    for (int i = 0; i < r; i++)
    {
        ans *= (n - i);
    }

    return ans;
}

long long calNCr(int n, int r)
{
    if (r > n) return 0;

    r = min(r, n - r);

    long long ans = 1;
    for (int i = 1; i <= r; i++)
    {
        ans = ans * (n - r + i) / i;
    }

    return ans;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int A, B;
    cin >> A >> B;

    cout << calNCr(A, B) << " " << calNPr(A, B) << "\n";

    return 0;
}