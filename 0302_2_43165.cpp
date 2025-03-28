/* 타겟 넘버 - 43165 */

#include <vector>

using namespace std;

int dfs(vector<int>::iterator pos, vector<int>::iterator end, int target) {
    if (pos == end) {
		return static_cast<int>(target == 0);
	}
	return dfs(pos + 1, end, target + *pos) + dfs(pos + 1, end, target - *pos);
}

int solution(vector<int> numbers, int target) {
    return dfs(numbers.begin(), numbers.end(), target);
}