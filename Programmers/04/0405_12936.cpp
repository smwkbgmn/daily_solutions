/* 줄 서는 방법 - 12936 */

#include <string>
#include <vector>
#include <deque>

using namespace std;

vector<int> solution(int n, long long k) {
    long long cases = n - 1;
    for (auto i = 2; i < n; ++i) {
        cases *= (n - i);
    }
    
    deque<int> number;
    for (auto i = 1; i <= n; ++i) {
        number.push_back(i);
    }
    
    --k;
    vector<int> rst;
    for (auto i = 1; i < n; ++i) {
        size_t div = k / cases;
        rst.push_back(number[div]);
        number.erase(number.begin() + div);
        
        k %= cases;
        cases /= (n - i);
    }
    
    rst.push_back(number.front());
    
    return rst;
}