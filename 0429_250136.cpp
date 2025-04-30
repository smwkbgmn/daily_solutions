#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

int solution(vector<vector<int>> land) {
	const int width = land.front().size(), height = land.size();

    auto bfs = [&](const pair<int, int>& pos, int& pipe) -> int {
		const pair<int, int> dir[4] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
		
		auto valid = [&](int r, int c, int i) -> bool {
			if (i < 2) {
				return land[min(r, height - 1)][min(c, width - 1)];
			} else {
				return land[max(r, 0)][max(c, 0)];
			}
		};
		
        queue<pair<int, int>> q;

		land[pos.first][pos.second] = 0;
        q.push(pos);
		
        int oil = 0;
        while (!q.empty()) {
            auto [r, c] = q.front();
            q.pop();
            
            for (auto i = 0; i < 4; ++i) {
                int nr = r + dir[i].first;
                int nc = c + dir[i].second;
                
                if (valid(nr, nc, i)) {
					land[nr][nc] = 0;
					q.push({nr, nc});
                }
            }

            pipe = max((int)pipe, c);
            ++oil;
        }

        return oil;
    };
    
    vector<int> pipes(width);

    for (int c = 0; c < width; ++c) {
        for (int r = 0; r < height; ++r) {
            if (!land[r][c]) continue;
            
            int pipe = c, oil = bfs({r, c}, pipe);
            for (int i = c; i <= pipe; ++i) {
                pipes[i] += oil;
            }
        }
    }
    
    return *max_element(pipes.begin(), pipes.end());
}
