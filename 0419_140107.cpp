#include <cmath>

using namespace std;

long long square(long long n) {
    return n * n;
}

long long solution(int k, int d) {
    long long dots = 0;
    
    for (auto x = 0; x <= d; x += k) {
        /* (x^2 + y^2) = d^2 */
        int y = sqrt(square(d) - square(x));
        dots += (y / k) + 1;
    }
    
    return dots;
}
