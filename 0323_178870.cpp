/* 연속된 부분 수열의 합 - 178870 */

#include <vector>
#include <algorithm>

using namespace std;

vector<int> solution(vector<int> sequence, int k) {
    vector<int> result = {0, 0};
    
	/* make_reverse_iterator: c++14 or later */
    auto r = make_reverse_iterator(
        upper_bound(sequence.begin(), sequence.end(), k));
    
    int sum = 0;
    for (auto l = r; l != sequence.rend(); ++l) {
        sum += *l;
        
        if (sum == k) {
            result[0] = distance(sequence.begin(), l.base()) - 1;
            result[1] = distance(sequence.begin(), r.base()) - 1;
            break;
        }
        
        if (sum > k) {
            sum -= *r++;
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