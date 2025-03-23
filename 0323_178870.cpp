/* 연속된 부분 수열의 합 - 178870 */

#include <vector>
#include <algorithm>

using namespace std;

vector<int> solution(vector<int> sequence, int k) {
    vector<int> result = {0, 0};
    
	/* make_reverse_iterator: c++14 or later */
    auto it_r = make_reverse_iterator(
        upper_bound(sequence.begin(), sequence.end(), k));
    
    int sum = 0;
    for (auto it_l = it_r; it_l != sequence.rend(); ++it_l) {
        sum += *it_l;
        
        if (sum == k) {
            result[0] = distance(sequence.begin(), it_l.base()) - 1;
            result[1] = distance(sequence.begin(), it_r.base()) - 1;
            break;
        }
        
        if (sum > k) {
            sum -= *it_r++;
        }
    }
    
    if (sequence[result[0]] == sequence[result[1]]) {
        auto i = result[0], n = sequence[result[0]];
        while (i > 0 && sequence[i - 1] == n) {
            --i;
        }
        
        result[1] -= (result[0] - i);
        result[0] -= (result[0] - i);
    }
    
    return result;
}