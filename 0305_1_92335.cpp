/* K진수에서 소수 개수 구하기 - 92335 */

#include <string>
#include <sstream>
#include <cmath>
#include <algorithm>

using namespace std;

bool is_prime(long long n) {
    int n_sqrtd = sqrt(n) + 1;
    
    for (auto divider = 2; divider < n_sqrtd; ++divider) {
        if (n % divider == 0) {
            return false;
        }
    }
    return true;
}

int solution(int n, int k) {
    string s_n_base;
    while (n != 0) {
        int mod = n % k;
        
        if (mod == 0) {
            s_n_base += ' ';
        } else {
            s_n_base += (mod + '0');
        }
        n /= k;
    }
    
    reverse(s_n_base.begin(), s_n_base.end());
    
    stringstream ss(s_n_base);
    
    long long part, count = 0;
    while (ss >> part) {
        if (part > 1 && is_prime(part)) {
            ++count;
        }
    }
    
    return count;
}