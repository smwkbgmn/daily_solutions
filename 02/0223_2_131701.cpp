/* 연속 부분 수열 합의 개수_131701 */

#include <vector>
#include <unordered_set>

using namespace std;

int solution(vector<int> elements) {
    unordered_set<int> sums;
    
    int size = elements.size();

	/* Using previous sum results can significantly reduce runtime */
    vector<int> sum_prev(size, 0);
    
	for (auto it = elements.begin(); it + 1 != elements.end(); ++it) {
		auto it_add = it;
		
		for (int i = 0; i < size; ++i) {
			sum_prev[i] += *it_add;
			sums.insert(sum_prev[i]);

			if (++it_add == elements.end()) {
				it_add = elements.begin();
			}
		}
    } 

    return sums.size() + 1;
}