#include <bits/stdc++.h>
using namespace std;

bool canMake( long long time , vector<long long>& machines , long long t){
    long long total = 0;
    for(int i = 0 ; i < machines.size(); i++){
        total += time / machines[i];

        if( total >= t){
            return true;
        }
    }

    return false;
}
void solve(){
    long long n ;
    long long t;
    cin >> n >> t;

    vector<long long> machines(n);
    long long  min_time = LLONG_MAX;
    for(int i = 0; i < n; i++){
        cin>> machines[i];
        min_time = min(min_time , (long long)machines[i]);
    }

    long long low = 1;
    long long high = (long long)min_time * t;

    while( low <= high){
        long long mid = low + (high - low) / 2;

        if((canMake(mid , machines , t))){
            high = mid - 1;
        }
        else{
            low = mid + 1;
        }
    }
    cout << low << endl;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    while(t--){
        solve();
    }

    return 0;
}