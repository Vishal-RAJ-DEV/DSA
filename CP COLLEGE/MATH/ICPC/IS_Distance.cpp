#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

int main() {
    // Using long long to prevent overflow since coordinates can be up to 10^9, 
    // and squaring them can result in values up to 10^18.
    long long x1, y1, x2, y2;
    
    // Read the coordinates of the two points
    cin >> x1 >> y1 >> x2 >> y2;
    
    // Calculate the squared differences
    long long dx = x2 - x1;
    long long dy = y2 - y1;
    
    // Calculate the Euclidean distance using long double for precision
    long double distance = sqrt(dx * dx + dy * dy);
    
    // Output the distance with sufficient precision (at least 6 decimal places)
    cout << fixed << setprecision(9) << distance << endl;
    
    return 0;
}