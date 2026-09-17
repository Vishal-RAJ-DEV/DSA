#include <iostream>
#include <vector>
using namespace std;

bool isSafe(int node,
            vector<vector<int>>& graph,
            vector<int>& color,
            int n,
            int col)
{
    for(int k=0; k<n; k++)
    {
        if(graph[node][k] == 1 && color[k] == col)
            return false;
    }

    return true;
}

bool solve(int node,
           vector<vector<int>>& graph,
           vector<int>& color,
           int n,
           int m)
{
    // All vertices colored
    if(node == n)
        return true;

    // Try all colors
    for(int col=1; col<=m; col++)
    {
        if(isSafe(node, graph, color, n, col))
        {
            color[node] = col;

            if(solve(node+1, graph, color, n, m))
                return true;

            // Backtracking
            color[node] = 0;
        }
    }

    return false;
}

bool graphColoring(vector<vector<int>>& graph,
                   int m,
                   int n)
{
    vector<int> color(n,0);

    return solve(0, graph, color, n, m);
}

int main()
{
    vector<vector<int>> graph =
    {
        {0,1,1,1},
        {1,0,1,0},
        {1,1,0,1},
        {1,0,1,0}
    };

    int m = 3;
    int n = 4;

    if(graphColoring(graph,m,n))
        cout<<"Coloring possible";
    else
        cout<<"Coloring not possible";

    return 0;
}