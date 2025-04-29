#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

int solution(vector<vector<int>> land) {
	const int width = land.front().size(), height = land.size();
    const pair<int, int> dir[4] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

    auto bfs = [&](const pair<int, int>& begin, int& pipe) -> int {
        queue<pair<int, int>> q;
        q.push(begin);
		
		land[begin.first][begin.second] = 0;
    
        int oil = 0;
        while (!q.empty()) {
            auto [r, c] = q.front();
            q.pop();
            
            for (auto i = 0; i < 4; ++i) {
                int rn = r + dir[i].first;
                int cn = c + dir[i].second;
                
                if ((i < 2 && land[min(rn, height - 1)][min(cn, width - 1)]) ||
					(i > 1 && land[max(rn, 0)][max(cn, 0)])) {
					land[rn][cn] = 0;
					q.push({rn, cn});
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
            if (land[r][c] == 0) continue;
            
            int pipe = c, oil = bfs({r, c}, pipe);
            for (int i = c; i <= pipe; ++i) {
                pipes[i] += oil;
            }
        }
    }
    
    return *max_element(pipes.begin(), pipes.end());
}
