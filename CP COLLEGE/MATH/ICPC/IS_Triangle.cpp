#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

int main() {
    // Using double to prevent precision loss during area calculation
    double a, b, c;
    
    // Read the three sides
    cin >> a >> b >> c;
    
    // Check the Triangle Inequality Theorem
    if (a + b > c && a + c > b && b + c > a) {
        cout << "Valid" << endl;
        
        // Calculate the semi-perimeter
        double s = (a + b + c) / 2.0;
        
        // Calculate the area using Heron's formula
        double area = sqrt(s * (s - a) * (s - b) * (s - c));
        
        // Output the area with sufficient precision
        cout << fixed << setprecision(6) << area << endl;
    } else {
        // If it doesn't satisfy the theorem, it's invalid
        cout << "Invalid" << endl;
    }
    
    return 0;
}