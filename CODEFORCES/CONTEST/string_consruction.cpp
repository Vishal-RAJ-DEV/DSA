#include <bits/stdc++.h>
using namespace std;

void solve(){
    int n,k;
    cin>>n>>k;
     
    int runs = n - k;
    int zero = n /2;
    int ones = n - zero;

    bool ok = false;
    string ans;

    for(int start = 0 ; start <= 1 && !ok; start++){
        int run0 ,  run1;
        if(start == 0){
            run0 = (runs + 1 ) / 2;
            run1 = runs / 2;
        }else{
            run1 = (runs + 1) / 2;
            run0 = runs/ 2;

        }

        if(run0 > zero || run1 > ones)continue;

        int extra0 = zero - run0;
        int extra1 = ones - run1;

        bool first0 =  true;
        bool first1 = true;
        int curr = start;
        string s;

        for(int i = 0 ; i < runs; i++){
            if( curr == 0){
                int len = 1;
                if(first0){
                    len += extra0;
                    first0 = false;
                }
                s.append(len , '0');
            }else{
                int len = 1;
                if(first1){
                    len += extra1;
                    first1 = false;
                }
                s.append(len , '1');
            }
            curr ^= 1;
        }

        if((int)s.size() == 1){
            ans = s;
            ok = true;
        }
    }

    if(ok){
        cout<<ans<<endl;
    }else{
        cout<<-1<<endl;
    }
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