#include <iostream>
using namespace std;
void explainpair(){
    pair<int ,int >p={1,2};
    cout<<p.first<<" "<<p.second<<endl;
    pair<int,pair<int,int>>r={2,{3,4}};
    cout<<p.first<<" "<<r.second.first<<" "<<r.second.second;

}

int main(){
    explainpair();
    return 0;

}