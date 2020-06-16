#include <neural-network/util.hpp>
#include <random>

double mutate(double x) {
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_real_distribution<> dist(0.0, 1.0);

    if (dist(rng) < 0.1f) {
        double offset = randomZero_One() * 0.5;
        double newx = x + offset;
        return newx;
    } else {
        return x;
    }
}

double randomZero_One() {
    const double PI = 3.14159265358979323846;
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_real_distribution<> dist(0.0, 1.0);

    double u = 0;
    double v = 0;
    while (u == 0) u = dist(rng); //Converting [0,1) to (0,1)
    while (v == 0) v = dist(rng);
    return sqrt(-2.0 * log(u)) * cos(2.0 * PI * v);
}

double map(double value, double low1, double high1, double low2, double high2) {
    return low2 + (high2 - low2) * (value - low1) / (high1 - low1);
}