/* 타겟 넘버 - 43165 */

#include <vector>

using namespace std;

int bfs(vector<int>::iterator pos, vector<int>::iterator end, int target) {
    if (pos == end) {
        return static_cast<int>(target == 0);
	} else {
        return bfs(pos + 1, end, target + *pos) + bfs(pos + 1, end, target - *pos);
    }
}

int solution(vector<int> numbers, int target) {
    return bfs(numbers.begin(), numbers.end(), target);
}