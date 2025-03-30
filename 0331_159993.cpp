/* 미로 탈출 - 159993 */

#include <string>
#include <vector>
#include <queue>
#include <unordered_set>

using namespace std;

const int dir[4] = { +100, +1, -100, -1 };

int solution(vector<string> maps) {
    size_t max_r = maps.size(), max_c = maps[0].length();
    
	int begin = -1;
    for (auto r = 0; r < max_r && begin == -1; ++r) {
        for (auto c = 0; c < max_c && begin == -1; ++c) {
            if (maps[r][c] == 'S') {
                begin = r * 100 + c;
            }
        }
    }
    
	int distance = 0;
    auto bfs = [&](char target) -> bool {
        queue<int> q;
        unordered_set<int> visit;

		q.push(begin);
		visit.insert(begin);

		auto assign_adj = [&](int cur) -> void {
			for (auto i = 0; i < 4; ++i) {
				int adj = cur + dir[i], r = adj / 100, c = adj % 100;

				if (r < max_r && c < max_c && maps[r][c] != 'X' &&
					visit.insert(adj).second) {
					q.push(adj);
				}
			}
		};

		while (!q.empty()) {
			for (auto i = q.size(); i > 0; --i) {
				int cur = q.front();
				q.pop();

				if (maps[cur / 100][cur % 100] == target) {
					begin = cur;
					return true;
				}
				assign_adj(cur);
			}
			++distance;
		}
		return false;
    };
    
    if (!bfs('L') || !bfs('E')) {
        return -1;
    }
	
	return distance;
}