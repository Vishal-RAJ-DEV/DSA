#include <bits/stdc++.h>
using namespace std;

// Function to rotate the matrix by 90 degrees clockwise
void rotate90(vector<vector<int>>& mat) {
    int n = mat.size();

    // Initialize the result matrix with zeros
    vector<vector<int>> res(n, vector<int>(n));

    // Flip the matrix clockwise using nested loops
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            res[j][n - i - 1] = mat[i][j];
        }
    }

    mat = res;
}



// Function to rotate a square matrix by 90 degrees in clockwise direction
void rotate90(vector<vector<int>>& mat) {
    int n = mat.size();

    // Consider all cycles one by one
    for (int i = 0; i < n / 2; i++) {

        // Consider elements in group of 4 as P1, P2, P3 & P4 in current square
        for (int j = i; j < n - i - 1; j++) {

            // Swap elements in clockwise order
            int temp = mat[i][j];
            mat[i][j] = mat[n - 1 - j][i];                 // Move P4 to P1
            mat[n - 1 - j][i] = mat[n - 1 - i][n - 1 - j]; // Move P3 to P4
            mat[n - 1 - i][n - 1 - j] = mat[j][n - 1 - i]; // Move P2 to P3
            mat[j][n - 1 - i] = temp;                      // Move P1 to P2
        }
    }
}

// Function to rotate a square matrix by 90 
// degrees in clockwise direction
void rotate90(vector<vector<int>> &mat){ 
  	int n = mat.size();
  	
    // Perform Transpose
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            swap(mat[i][j], mat[j][i]);
        }
    }

    // Reverse each row
    for (int i = 0; i < n; i++)
        reverse(mat[i].begin(), mat[i].end());
}

// Function to rotate a square matrix by 90 degrees
// in clockwise direction
void rotate90(vector<vector<int>> &mat){ 
  	int n = mat.size();
  	
  	// Reverse Columns
    for (int i = 0; i < n/2; i++)
    {
        for (int j = 0; j < n; j++)
        {
            swap(mat[i][j], mat[n - i - 1][j]);
        }
    }
        
    // Perform Transpose
    for (int i = 0; i < n; i++) {
        for (int j = i+1; j < n; j++) {
            swap(mat[i][j], mat[j][i]);
        }
    }    

}
int main() {
    vector<vector<int>> mat = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12},
        {13, 14, 15, 16}
    };
    rotate90(mat);
    for (auto& row : mat) {
        for (int x : row) {
            cout << x << ' ';
        }
        cout << endl;
    }

    return 0;
}