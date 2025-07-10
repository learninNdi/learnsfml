#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

int main()
{
    double initialHeight = 2.0; // Initial drop height in meters
    double restitution = 0.8;   // Coefficient of restitution (0 < e < 1)
    double g = 9.8;             // Acceleration due to gravity (m/s^2)
    double height = initialHeight;
    int bounce = 0;
    double minHeight = 0.01; // Stop when bounce height is less than this

    cout << fixed << setprecision(2);
    cout << "Simulating bouncing ball:\n";
    cout << "Initial height: " << initialHeight << " m\n";
    cout << "Coefficient of restitution: " << restitution << "\n\n";

    while (height > minHeight)
    {
        double vImpact = sqrt(2 * g * height);             // Velocity before impact
        double vBounce = restitution * vImpact;            // Velocity after bounce
        double nextHeight = (vBounce * vBounce) / (2 * g); // Height after bounce

        cout << "Bounce #" << ++bounce << ":\n";
        cout << "  Impact velocity: " << vImpact << " m/s\n";
        cout << "  Bounce velocity: " << vBounce << " m/s\n";
        cout << "  New height: " << nextHeight << " m\n\n";

        height = nextHeight; // Update height for next bounce
    }

    cout << "Ball has essentially stopped bouncing.\n";
    return 0;
}
