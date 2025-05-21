/* 숫자 카드 나누기 - 135807 */

#include <vector>

using namespace std;

int euclid(int a, int b) {
    return a % b == 0? b : euclid(b, a % b);
}

int solution(vector<int> pair1, vector<int> pair2) {
    int gcd = pair1.front();
    for (auto& n: pair1) {
        gcd = euclid(gcd, n);
    }
    
    int case1 = gcd;
    for (auto& n: pair2) {
        if (n % gcd == 0) {
            case1 = 0;
            break;
        }
    }
    
    gcd = pair2.front();
    for (auto& n: pair2) {
        gcd = euclid(gcd, n);
    }
    
    int case2 = gcd;
    for (auto& n: pair1) {
        if (n % gcd == 0) {
            case2 = 0;
            break;
        }
    }
    
    return max(case1, case2);
}

