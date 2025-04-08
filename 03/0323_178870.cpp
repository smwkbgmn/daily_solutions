/* 연속된 부분 수열의 합 - 178870 */

#include <vector>
#include <algorithm>

using namespace std;

vector<int> solution(vector<int> seq, int k) {
    vector<int> rst = {0, 0};
    
    auto r = make_reverse_iterator(
        upper_bound(seq.begin(), seq.end(), k));
    
    int sum = 0;
    for (auto l = r; l != seq.rend(); ++l) {
        sum += *l;
        
        if (sum == k) {
            rst[0] = distance(l, seq.rend()) - 1;
            rst[1] = distance(r, seq.rend()) - 1;
            break;
        }
        
        if (sum > k) {
            sum -= *r++;
        }
    }
    
    if (seq[rst[0]] == seq[rst[1]]) {
        auto diff = rst[0] - distance(seq.begin(),
            lower_bound(seq.begin(), seq.end(), seq[rst[0]]));
        
        rst[0] -= diff;
        rst[1] -= diff;
    }
    
    return rst;
}