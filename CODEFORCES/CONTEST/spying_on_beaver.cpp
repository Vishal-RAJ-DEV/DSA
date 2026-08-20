#include <bits/stdc++.h>
using namespace std;

void solve(){
    int n;
    cin>>n;

    vector<vector<int>>c(n + 1);

    for(int i = 2; i <= n ; i++){
        int p;
        cin>>p;
        c[p].push_back(i);
    }

    int m;
    cin>>m;

    vector<bool>dam(n + 1 , false);

    for(int i = 0 ; i < m ; i++){
        int x ;
        cin>>x;
        dam[x] = true;
    }

    vector<bool>p( n + 1, false);
    vector<int>cam;

    for(int v = n ; v >= 1 ; v--){
        if(dam[v]){
            for(int u : c[v]){
                if(p[u]){
                    cam.push_back(u);
                }
            }
            p[v] = true;
        }
        else{
            int keep = -1;

            for(int u : c[v]){
                if(!p[u]){
                    continue;
                }

                if(keep == -1){
                    keep = u;
                }

                else{
                    cam.push_back(u);
                }
            }
            p[v] = ( keep != -1);
        }
    }

    cout<<cam.size();
    for(int u : cam){
        cout<<' '<<u;
    }

    cout<<endl;

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