/*
The adjencency list representation of a graph is a collection of unordered lists used to represent a finite graph. Each list describes the set of neighbors of a vertex in the graph.

Input:
5 6
1 2  and for undirected graph 2 is also connected to 1 and similarly for other edges
1 3
2 4
3 4
3 5
4 5
Explanation:
Number of nodes, n = 5
Number of edges, m = 6
Next m lines represent the edges.

here we will store the graph using adjacency list representation 
--like 1 -> 2,3     here 1 is connected to 2 and 3
       2 -> 1,4     here 2 is connected to 1 and 4
       3 -> 1,4,5   here 3 is connected to 1,4 and 5
       4 -> 2,3,5   here 4 is connected to 2,3 and 5
       5 -> 3,4     here 5 is connected to 3 and 4
*/

#include <iostream>
#include <bits/stdc++.h>
using namespace std;

void undirected_Graph(vector<vector<int>> &adj_Undirected, int u, int v){
    adj_Undirected[u].push_back(v);
    adj_Undirected[v].push_back(u); // for undirected graph like eg 1 2 then 2 is also connected to 1 and similarly for other edges
}
void directed_Graph(vector<vector<int>> &adj_Directed, int u, int v){
    adj_Directed[u].push_back(v); //only one direction for directed graph
}

void print_List(vector<vector<int>> &adj_List){ //this is normal list printing function
    int n = adj_List.size();
    for( int i = 1; i < n ; i++){
        if( adj_List[i].size() == 0 ) continue; // skip nodes with no connections
        cout << '{' << i << " -> ";
        for( int j = 0 ; j < adj_List[i].size() ; j++){
            cout<< adj_List[i][j];
            if ( j != adj_List[i].size() - 1 ) cout << ", ";
        }
        cout << '}' << endl;
    }
}
int main(){
    int n , m ;
    cout<<"Enter number of nodes and edges: ";
    cin >> n >> m;

    vector<vector<int>> adj_ListUndirected(n+1); // adjacency list of size (n+1) and n + 1 because nodes are starting from 1 to n
    vector<vector<int>> adj_ListDirected(n+1); // adjacency list of size (n+1) and n + 1 because nodes are starting from 1 to n


    cout<<"Enter the edges (u v): "<<endl;
    for(int i = 0; i < m; i++){
        int u , v ;
        cin>> u >> v ;
        undirected_Graph(adj_ListUndirected, u, v);
        directed_Graph(adj_ListDirected, u, v);
    }

    // Print adjacency list for undirected graph
    cout<<"Adjacency List for Undirected Graph: "<<endl;
    print_List(adj_ListUndirected);
    // Print adjacency list for directed graph
    cout<<"Adjacency List for Directed Graph: "<<endl;
    print_List(adj_ListDirected);

    return 0;
}
