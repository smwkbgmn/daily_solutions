/* 연속 부분 수열 합의 개수_131701 */

#include <vector>
#include <unordered_set>

using namespace std;

int solution(vector<int> elements) {
    unordered_set<int> sums;
    
    int size = elements.size();

	/* Using previous sum results can significantly reduce runtime */
    vector<int> sum_prev(size, 0);
    
    for (int i = 0; i < size - 1; ++i) {
        for (int cnt = 0; cnt < size; ++cnt) {
            sum_prev[cnt] += elements[(i + cnt) % size];
            sums.insert(sum_prev[cnt]);
        }
    } 
    
    return sums.size() + 1;
}