/*Adjacency Matrix
An adjacency matrix of a graph is a two-dimensional array of size n x n, where n is the number of nodes in the graph, with the property that a[ i ][ j ] = 1 if the edge (vᵢ, vⱼ) is in the set of edges, and a[ i ][ j ] = 0 if there is no such edge.

Consider the example of the following undirected graph,

Input:
5 6
1 2
1 3
2 4
3 4 
3 5 
4 5

Explanation:
Number of nodes, n = 5
Number of edges, m = 6
Next m lines represent the edges.
*/

#include <iostream>
#include <bits/stdc++.h>
using namespace std;
void undirected_Graph(vector<vector<int>> &adj_Undirected, int u, int v){
    adj_Undirected[u][v] = 1;
    adj_Undirected[v][u] = 1; // for undirected graph like eg 1 2 then 2 is also connected to 1 and similarly for other edges
}
void directed_Graph(vector<vector<int>> &adj_Directed, int u, int v){
    adj_Directed[u][v] = 1; //only one direction for directed graph
}

void print_Matrix(vector<vector<int>> &adj_Matrix){ //this is normal matrix printing function
    int n = adj_Matrix.size();
    for(int i = 1; i < n; i++){
        for(int j = 1; j < n; j++){
            cout << adj_Matrix[i][j] << " ";
        }
        cout << endl;
    }
}
int main(){
    int n , m ;
    cout<<"Enter number of nodes and edges: ";
    cin >> n >> m;

    vector<vector<int>> adj_Undirected(n+1, vector<int>(n+1, 0)); // adjacency matrix of size (n+1) x (n+1) and n + 1 because nodes are starting from 1 to n
    vector<vector<int>> adj_Directed(n+1, vector<int>(n+1, 0)); // adjacency matrix of size (n+1) x (n+1) and n + 1 because nodes are starting from 1 to n

    cout<<"Enter the edges (u v): "<<endl;
    for(int i = 0; i < m; i++){
        int u , v ;
        cin >> u >> v ;
        undirected_Graph(adj_Undirected, u, v);
        directed_Graph(adj_Directed, u, v);
    }

    // Print adjacency matrix for undirected graph
    cout<<"Adjacency Matrix for Undirected Graph: "<<endl;
    print_Matrix(adj_Undirected);
    // Print adjacency matrix for directed graph
    cout<<"Adjacency Matrix for Directed Graph: "<<endl;
    print_Matrix(adj_Directed);

    return 0;
}

