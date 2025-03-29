/* 미로 탈출 - */

#include <string>
#include <vector>
#include <queue>
#include <unordered_set>

using namespace std;

const int dir[4] = { +100, +1, -100, -1 };

int to_id(const pair<int, int>& rc) {
    return rc.first * 100 + rc.second;
}

int solution(vector<string> maps) {
    size_t max_r = maps.size(), max_c = maps[0].length();
    
    int start = -1;
    for (auto r = 0; r < max_r && start == -1; ++r) {
        for (auto c = 0; c < max_c && start == -1; ++c) {
            if (maps[r][c] == 'S') {
                start = to_id({r, c});
            }
        }
    }
    
    auto bfs = [&](char target) -> int {
        queue<int> q;
        unordered_set<int> visit;
        
        auto assign_adj = [&](int cur) -> void {
            for (auto i = 0; i < 4; ++i) {
                int adj = cur + dir[i], r = adj / 100, c = adj % 100;

                if (r < max_r && c < max_c && maps[r][c] != 'X' &&
                    visit.insert(adj).second) {
                    q.push(adj);
                }
            }
        };
        
        q.push(start);
		visit.insert(start);
        
        int d = 0;
        bool found = false;
        
        while (!q.empty()) {
            for (auto i = q.size(); i > 0; --i) {
                int cur = q.front();
                q.pop();

                if (maps[cur / 100][cur % 100] == target) {
                    start = cur;
                    found = true;
                    break;
                }
                assign_adj(cur);
            }
            
            if (found) {
                break;
            }
            ++d;
        }
        
        return found == true? d : -1;
    };
    
    
    int dl = bfs('L');
    if (dl == -1) {
        return -1;
    }
    
    int de = bfs('E');
    if (de == -1) {
        return -1;
    }
    
    return dl + de;
}