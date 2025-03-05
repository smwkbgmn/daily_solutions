/* K진수에서 소수 개수 구하기 - 92335 */

#include <string>
#include <sstream>
#include <cmath>
#include <algorithm>

using namespace std;

string itos_base(int n, int b) {
	string s;

    while (n != 0) {
        int mod = n % b;
        
        if (mod == 0) {
            s += ' ';
        } else {
            s += (mod + '0');
        }
        n /= b;
    }
    
    reverse(s.begin(), s.end());

	return s;
}

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
    stringstream ss(itos_base(n, k));
    
    long long part, count = 0;
    while (ss >> part) {
        if (part > 1 && is_prime(part)) {
            ++count;
        }
    }
    
    return count;
}