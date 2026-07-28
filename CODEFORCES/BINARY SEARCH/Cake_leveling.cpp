#include <bits/stdc++.h>
using namespace std;
using int64 = long long;

bool check(int64 h , int n , const vector<int64>& a){
    int64 carry = 0;
    for(int i = 0 ; i < n ; i++){
        int64 sum = carry + a[i];

        if(sum < h)return false;

        carry = sum - h;
    }

    return true;
}
void solve1(){
    int n;
    cin>>n;
    vector<int64> a(n);
    for(int i = 0 ; i < n ; i++){
        cin>>a[i];
    }

    int64 mx = 0;

    for(int i = 0 ; i < n ; i++){
        mx = max(mx , a[i]);

        int64 low = 1;
        int64 high = mx;
        int64 ans = 1;

        while( low <= high){
            int64 mid = low + (high - low) / 2;

            if(check(mid , i + 1, a)){
                ans = mid;
                low = mid + 1;
            }else{
                high = mid - 1;
            }
        }

        cout<<ans<<" ";
    }
    

    cout<<endl;


}
//optimization


void solve() {
    int n;
    cin >> n;

    int64 sum = 0;
    int64 best = LLONG_MAX;

    for (int i = 0; i < n; i++) {
        int64 x;
        cin >> x;
        sum += x;

        int64 avg_h = sum / (i + 1);
        best = min(best, avg_h);

        cout<<best << " ";
        
    }

    cout << '\n';
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while(t--){
        solve();
    }

    return 0;
}