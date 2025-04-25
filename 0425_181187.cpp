/* 두 원 사이의 정수 쌍 - 181187 */

#include <cmath>

using namespace std;

long long sq(long long n) {
    return n * n;
}

long long solution(int r1, int r2) {
    long long dot1 = 0;
    for (auto x = 0; x <= r1; ++x) {
        auto y = sqrt(sq(r1) - sq(x));
        dot1 += (y > 0? ceil(y) - 1 : 0); 
    }
    
    long long dot2 = 0;
    for (auto x = 0; x <= r2; ++x) {
        auto y = sqrt(sq(r2) - sq(x));
        dot2 += static_cast<long long>(y);
    }
    
    return (dot2 - dot1) * 4;
}