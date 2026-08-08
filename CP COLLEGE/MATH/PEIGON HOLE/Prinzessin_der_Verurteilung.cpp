#include <bits/stdc++.h>
using namespace std;

void solve(){
    int n;
    cin>>n;
    string s;
    cin>>s;

    vector<bool>has1(26 , false);
    for(int i = 0 ; i < n ; i++){
        has1[s[i] - 'a'] = true;
    }

    for(int i = 0 ; i < 26 ; i++){
        if(!has1[i]){
            return cout<<char('a' + i)<<'\n', void();
        }
    }


    vector<vector<int>>has2(26 , vector<int>(26 , false));
    for(int i = 0 ; i + 1 < n ; i++){
        has2[s[i] - 'a'][s[i+1] - 'a'] = true;
    }

    for(int i = 0 ; i < 26 ; i++){
        for(int j = 0 ; j < 26 ; j++){
            if(!has2[i][j]){
                return cout<<char('a' + i)<<char('a' + j)<<'\n', void();
            }
        }
    }


    vector<vector<vector<int>>>has3(26 , vector<vector<int>>(26 , vector<int>(26 , false)));
    for(int i = 0 ; i + 2 < n ; i++){
        has3[s[i] - 'a'][s[i+1] - 'a'][s[i+2] - 'a'] = true;
    }

    for(int i = 0 ; i < 26 ; i++){
        for(int j = 0 ; j < 26 ; j++){
            for( int k = 0 ; k < 26 ; k++){
                if(!has3[i][j][k]){
                    return cout<<char('a' + i)<<char('a' + j)<<char('a' + k)<<'\n', void();
                }
            }
        }
    }

    cout<<""<<endl;
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