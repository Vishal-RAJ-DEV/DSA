#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    /*
        Floyd Warshall Algorithm

        Purpose:
        - Find the shortest distance between every pair of vertices.
        - This is an "all pairs shortest path" algorithm.

        Main idea:
        - Try every node as an intermediate node.
        - Suppose we are finding shortest path from i to j.
        - For every possible intermediate node k, check:
              i -> k -> j
          If this path is shorter than current i -> j, update it.

        Formula:
            matrix[i][j] = min(matrix[i][j],
                               matrix[i][k] + matrix[k][j])

        Here this Solution class is needed when:
        - The input matrix uses -1 to mean "no direct path".
        - Example:
              matrix[i][j] = -1 means i cannot directly reach j.
              matrix[i][i] = 0 means distance from a node to itself is 0.

        Because -1 is used for no path, we cannot directly apply min().
        We first check if i -> k and k -> j are possible.

        Time Complexity: O(n^3)
        Space Complexity: O(1), because we update the matrix itself.
    */
    void shortest_distance(vector<vector<int>> &matrix){
        
        // Getting the number of nodes
	    int n = matrix.size();
	    
	    // For each intermediate node k.
        // k means: can using this node in between improve path i -> j?
	    for(int k=0; k<n; k++) {
	        
	        // Check for every (i, j) pair of nodes
	        for(int i=0; i<n; i++) {
	            for(int j=0; j<n; j++) {
	                
	                /* If k is not an intermediate 
	                node, skip the iteration */
                    // If i cannot reach k OR k cannot reach j,
                    // then path i -> k -> j is not possible.
	                if(matrix[i][k] == -1 || 
	                   matrix[k][j] == -1) 
	                        continue;
	                
	                /* If no direct edge from 
	                i to v is present */
                    // If i cannot directly reach j, but i -> k -> j is possible,
                    // then this becomes the first known path from i to j.
	                if(matrix[i][j] == -1) {
	                    
	                    // Update the distance
	                    matrix[i][j] = 
	                        matrix[i][k] + matrix[k][j];
	                }
	                
	                /* Else update the distance to 
	                minimum of both paths */
                    // If i already has a path to j, keep the shorter one:
                    // old i -> j OR new i -> k -> j.
	                else {
	                    matrix[i][j] = 
	                        min(matrix[i][j] , 
	                             matrix[i][k] + matrix[k][j]
	                            );
	                }
	            }
	        }
	    }
	}
};
// User function template for C++

class Solution1 {
  public:
    /*
        Floyd Warshall Algorithm using INF

        This version is needed when:
        - The matrix already uses a very large value like INF to represent
          "no path" instead of -1.
        - Or when you convert every -1 into INF before calling this function.

        Why use INF?
        - min() works cleanly with INF.
        - If there is no path from i to j, dist[i][j] remains INF.

        Difference from Solution class:
        - Solution class handles -1 directly.
        - Solution1 expects unreachable distances to be INF.

        Important:
        - If your input has -1, convert it before this algorithm:
              if(dist[i][j] == -1) dist[i][j] = INF;
        - After the algorithm, if required by the platform, convert INF back:
              if(dist[i][j] == INF) dist[i][j] = -1;

        Algorithm:
        - via is the intermediate node.
        - i is the source node.
        - j is the destination node.
        - If i -> via and via -> j are possible, try to improve i -> j.

        Time Complexity: O(n^3)
        Space Complexity: O(1)
    */
    void floydWarshall(vector<vector<int>> &dist) {
        // Code here
        //now replace all the -1 dist to the 100000 so we get the minimum 
        //distance later 
        
        // INF means no path / unreachable.
        int INF = 100000000;
        
        // via is the intermediate node we are trying between i and j.
        for( int via = 0 ; via < dist.size() ; via++){
            
            // i is the starting/source node.
            for( int i = 0 ; i < dist.size() ; i++){

                // j is the ending/destination node.
                for( int j = 0 ; j < dist.size() ; j++){
                    
                    // If i cannot reach via OR via cannot reach j,
                    // then this route cannot improve dist[i][j].
                    if( dist[i][via] == INF || dist[via][j] == INF)continue;
                    
                    // Try path i -> via -> j and keep the minimum distance.
                    dist[i][j] = min( dist[i][j] , dist[i][via]  +  dist[via][j]);
                }
            }
        }
    }
};


int main() {

    vector<vector<int>> matrix ={
        {0, 2, -1, -1},
        {1, 0, 3, -1},
        {-1, -1, 0, -1},
        {3, 5, 4, 0}
    };
    
    /* Creating an instance of 
    Solution class */
    Solution sol; 
    
    /* Function to find the shortest distance 
    between every pair of vertices. */
    sol.shortest_distance(matrix);
    
    // Output
    int n = matrix.size();
    cout << "The shortest distance matrix is:\n";
    for(int i=0; i < n; i++) {
        for(int j=0; j < n; j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
    
    return 0;
}
