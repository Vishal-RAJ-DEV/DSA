#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k) {
        //convert the flights matrix into adjencey list 
        vector<pair<int,int>>adj[n];
        for(auto num : flights){
            adj[num[0]].push_back({num[1],num[2]});
        }
        //distance matrix that will store the minimum price
        vector<int>dist(n , 1e9);
        //priority queue to get the minimun price first 
        //here {k, {node , price}}
        queue<pair<int , pair<int , int >>>q;

        q.push({0,{src,0}});
        dist[src] = 0;

        while(!q.empty()){
            auto it = q.front();
            q.pop();    
            int stop = it.first;
            int node = it.second.first;
            int price = it.second.second;

            if( stop > k)continue;

            for ( auto it : adj[node]){
                int dis = it.first;
                int newprice = it.second;

                if( price + newprice  < dist[dis]  && stop <= k ){
                    dist[dis] = price + newprice;
                    q.push({stop+1 , {dis , price + newprice}});
                }

            }


        }

        //now return the preice to reach the distination 
        //if it still infinity 
        if( dist[dst]  == 1e9) return -1;

        return dist[dst];
    }
};


int main(){
    Solution sol;
    int n = 3; // Number of cities
    vector<vector<int>> flights = {{0, 1, 100}, {1, 2, 100}, {0, 2, 500}}; // Flight data: [source, destination, price]
    int src = 0; // Source city
    int dst = 2; // Destination city
    int k = 1; // Maximum number of stops
    cout << sol.findCheapestPrice(n, flights, src, dst, k) << endl; // Output the cheapest price from src to dst with at most k stops
    
    return 0;
}
