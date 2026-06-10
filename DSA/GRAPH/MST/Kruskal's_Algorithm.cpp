#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

class DSU {

public:

    vector<int> parent;

    DSU(int n) {

        parent.resize(n);

        for(int i=0;i<n;i++)
            parent[i]=i;
    }

    int find(int x) {

        if(parent[x]==x)
            return x;

        return parent[x]=find(parent[x]);
    }

    void unite(int x,int y) {

        int px=find(x);
        int py=find(y);

        if(px!=py)
            parent[px]=py;
    }
};

int main() {

    vector<vector<int>> edges = {

        {2,0,2}, // AC
        {3,2,3}, // CD
        {4,0,1}, // AB
        {5,0,3}, // AD
        {6,1,3}  // BD
    };

    sort(edges.begin(),edges.end());

    DSU dsu(4);

    int mstWeight=0;

    for(auto edge:edges) {

        int weight=edge[0];
        int u=edge[1];
        int v=edge[2];

        if(dsu.find(u)!=dsu.find(v)) {

            dsu.unite(u,v);

            mstWeight+=weight;
        }
    }

    cout<<mstWeight;
}